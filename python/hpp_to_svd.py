#!/usr/bin/env python3

import re
import sys
import os
from xml.dom.minidom import parseString
from xml.etree.ElementTree import Element, SubElement, tostring

# --- Настройки ---
VENDOR = "Texas Instruments"
DEVICE_NAME = "AM335x"
SERIES = "Sitara AM335x"
VERSION = "1.1"
DESCRIPTION = "AM335x peripherals generated from REGS.hpp"
CPU_NAME = "Cortex-A8"
CPU_REVISION = "r0p0"
CPU_ENDIAN = "little"
ADDRESS_UNIT_BITS = "8"
WIDTH = "32"
SIZE = "32"
RESET_VALUE = "0x00000000"
RESET_MASK = "0xFFFFFFFF"

# --- Конфигурация периферии ---
# Задаём маппинг: имя периферии в SVD -> ожидаемое имя структуры или базовый адрес
PERIPHERAL_CONFIG = {
    # EMIF
    'EMIF0': {
        'struct_pattern': 'AM335x_EMIF4D_Type',
        'base_address': '0x4C000000',
        'description': 'External Memory Interface 4D (EMIF) - DDR Controller'
    },
    'DDR23mPHY': {
        'struct_pattern': 'AM335x_DDR23mPHY_Type',
        'base_address': '0x44E12000',
        'description': 'DDR PHY Control Registers'
    },

    # PRCM модули - добавь свои по необходимости
    'CM_PER': {
        'struct_pattern': 'AM335x_CM_PER_Type',
        'base_address': '0x44E00000',
        'description': 'Clock Module - Peripheral'
    },
    'CM_WKUP': {
        'struct_pattern': 'AM335x_CM_WKUP_Type',
        'base_address': '0x44E00400',
        'description': 'Clock Module - Wakeup'
    },
    'CM_DPLL': {
        'struct_pattern': 'AM335x_CM_DPLL_Type',
        'base_address': '0x44E00500',
        'description': 'Clock Module - DPLL'
    },
    'CM_MPU': {
        'struct_pattern': 'AM335x_CM_MPU_Type',
        'base_address': '0x44E00600',
        'description': 'Clock Module - MPU'
    },
    'CM_DEVICE': {
        'struct_pattern': 'AM335x_CM_DEVICE_Type',
        'base_address': '0x44E00700',
        'description': 'Clock Module - Device'
    },
    'CM_RTC': {
        'struct_pattern': 'AM335x_CM_RTC_Type',
        'base_address': '0x44E00800',
        'description': 'Clock Module - RTC'
    },
    'CM_GFX': {
        'struct_pattern': 'AM335x_CM_GFX_Type',
        'base_address': '0x44E00900',
        'description': 'Clock Module - GFX'
    },
    'CM_CEFUSE': {
        'struct_pattern': 'AM335x_CM_CEFUSE_Type',
        'base_address': '0x44E00A00',
        'description': 'Clock Module - CEFUSE'
    },

    'PRM_IRQ': {
        'struct_pattern': 'AM335x_PRM_IRQ_Type',
        'base_address': '0x44E00B00',
        'description': 'Power Reset Module - IRQ'
    },
    'PRM_PER': {
        'struct_pattern': 'AM335x_PRM_PER_Type',
        'base_address': '0x44E00C00',
        'description': 'Power Reset Module - Peripheral'
    },
    'PRM_WKUP': {
        'struct_pattern': 'AM335x_PRM_WKUP_Type',
        'base_address': '0x44E00D00',
        'description': 'Power Reset Module - Wakeup'
    },
    'PRM_MPU': {
        'struct_pattern': 'AM335x_PRM_MPU_Type',
        'base_address': '0x44E00E00',
        'description': 'Power Reset Module - MPU'
    },
    'PRM_DEVICE': {
        'struct_pattern': 'AM335x_PRM_DEVICE_Type',
        'base_address': '0x44E00F00',
        'description': 'Power Reset Module - Device'
    },
    'PRM_RTC': {
        'struct_pattern': 'AM335x_PRM_RTC_Type',
        'base_address': '0x44E01000',
        'description': 'Power Reset Module - RTC'
    },
    'PRM_GFX': {
        'struct_pattern': 'AM335x_PRM_GFX_Type',
        'base_address': '0x44E01100',
        'description': 'Power Reset Module - GFX'
    },
    'PRM_CEFUSE': {
        'struct_pattern': 'AM335x_PRM_CEFUSE_Type',
        'base_address': '0x44E01200',
        'description': 'Power Reset Module - CEFUSE'
    },
    'UART': {
        'struct_pattern': 'AM335x_UART_Type',
        'base_address': '0x44E09000',
        'description': 'UART0 module'
    },
}

# Если True - парсить все найденные структуры, даже если их нет в PERIPHERAL_CONFIG
PARSE_ALL_STRUCTURES = True


def clean_comment(text):
    """Убирает лишние пробелы и звездочки из комментариев."""
    if not text:
        return ""
    text = text.strip()
    if text.startswith('*'):
        text = text[1:].strip()
    if text.startswith('/'):
        text = text[1:].strip()
    text = re.sub(r'\s+', ' ', text)
    return text.strip()


def determine_access(rw_string, field_name, description):
    """Определяет уровень доступа на основе (R), (RW), (W) в комментарии."""
    if rw_string:
        rw_upper = rw_string.upper()
        if 'W' in rw_upper and 'R' in rw_upper:
            return 'read-write'
        elif 'W' in rw_upper:
            return 'write-only'
        elif 'R' in rw_upper:
            return 'read-only'

    if 'reserved' in description.lower() or 'reserved' in field_name.lower():
        return 'read-only'

    return 'read-write'


def extract_reset_value(text_block):
    """Извлекает значение сброса из блока текста."""
    patterns = [
        r'\[reset\s+state\s*=\s*(0x[0-9A-Fa-f]+)\]',
        r'\[reset\s*=\s*(0x[0-9A-Fa-f]+)\]',
        r'reset\s+state\s*=\s*(0x[0-9A-Fa-f]+)',
        r'reset\s*=\s*(0x[0-9A-Fa-f]+)'
    ]

    for pattern in patterns:
        match = re.search(pattern, text_block, re.IGNORECASE)
        if match:
            return match.group(1)
    return "0x00000000"


def parse_fields(struct_body):
    """Извлекает список полей из тела структуры."""
    fields = []
    current_offset = 0

    lines = struct_body.split('\n')

    for line in lines:
        if not line.strip():
            continue

        match = re.search(
            r'uint32_t\s+(\w+)\s*:\s*(\d+)\s*;\s*(?://\s*(?:bit[:\s]*\d+\.\.\d+\s*)?(?:\(([RW]+)\)\s*)?(.*?))?$',
            line,
            re.IGNORECASE
        )

        if match:
            name = match.group(1)
            width = int(match.group(2))
            rw = match.group(3) if match.group(3) else None
            desc = match.group(4).strip() if match.group(4) else ""

            if name == "" or 'reserved' in name.lower() or 'Reserved' in desc.lower():
                current_offset += width
                continue

            fields.append({
                'name': name,
                'offset': current_offset,
                'width': width,
                'access': determine_access(rw, name, desc),
                'description': clean_comment(desc) if desc else f"Field {name}"
            })
            current_offset += width

        elif 'uint32_t' in line and ':' in line:
            parts = line.split(';')
            for part in parts:
                if 'uint32_t' in part and ':' in part:
                    field_match = re.search(r'uint32_t\s+(\w*)\s*:\s*(\d+)', part)
                    if field_match and field_match.group(1):
                        name = field_match.group(1)
                        width = int(field_match.group(2))

                        if name and 'reserved' not in name.lower():
                            rw_match = re.search(r'\(([RW]+)\)', part, re.IGNORECASE)
                            rw = rw_match.group(1) if rw_match else None

                            desc_match = re.search(r'//\s*(.*?)$', part)
                            desc = desc_match.group(1).strip() if desc_match else ""

                            fields.append({
                                'name': name,
                                'offset': current_offset,
                                'width': width,
                                'access': determine_access(rw, name, desc),
                                'description': clean_comment(desc) if desc else f"Field {name}"
                            })
                        current_offset += width

    return fields


def parse_register_types(content):
    """Парсит все определения регистровых типов."""
    registers = {}
    lines = content.split('\n')

    i = 0
    while i < len(lines):
        line = lines[i]

        if 'typedef union' in line:
            block_lines = [line]
            j = i + 1

            reset_val = "0x00000000"
            while j < len(lines) and not ('_reg_t' in lines[j] and '}' in lines[j]):
                block_lines.append(lines[j])
                if '[reset' in lines[j]:
                    reset_val = extract_reset_value(lines[j])
                j += 1

            if j < len(lines):
                block_lines.append(lines[j])

                type_match = re.search(r'}\s*(\w+_reg_t)\s*;', lines[j])
                if type_match:
                    reg_type = type_match.group(1).replace('_reg_t', '')

                    block_text = '\n'.join(block_lines)
                    struct_match = re.search(r'struct\s*{\s*(.*?)\s*}\s*b\s*;', block_text, re.DOTALL)

                    if struct_match:
                        struct_body = struct_match.group(1)
                        fields = parse_fields(struct_body)

                        registers[reg_type] = {
                            'reset_value': reset_val,
                            'fields': fields,
                            'description': f"{reg_type} Register"
                        }
                        print(f"  Найден регистр: {reg_type} (полей: {len(fields)}, reset: {reset_val})")

            i = j
        i += 1

    return registers


def parse_peripheral_instances(content, config):
    """Парсит структуры периферии и находит экземпляры регистров."""
    peripherals = {}

    # Создаём обратный маппинг: имя структуры -> конфигурация
    struct_to_config = {}
    for p_name, p_config in config.items():
        if 'struct_pattern' in p_config:
            struct_to_config[p_config['struct_pattern']] = {
                'name': p_name,
                'base_address': p_config.get('base_address'),
                'description': p_config.get('description', p_name)
            }

    # Ищем все структуры вида AM335x_..._Type
    pattern = r'struct\s+(AM335x_\w+_Type)\s*\{([^}]*(?:\{[^}]*\}[^}]*)*)\}\s*;'

    for match in re.finditer(pattern, content, re.DOTALL):
        struct_name = match.group(1)
        struct_body = match.group(2)

        # Определяем конфигурацию для этой структуры
        if struct_name in struct_to_config:
            config_entry = struct_to_config[struct_name]
            p_name = config_entry['name']
            desc = config_entry['description']
            base_addr = config_entry['base_address']
            print(f"  Найдена периферия из конфига: {p_name} (структура: {struct_name})")
        elif PARSE_ALL_STRUCTURES:
            # Автоматическое определение для структур не из конфига
            p_name = struct_name.replace('AM335x_', '').replace('_Type', '')
            desc = p_name
            base_addr = None
            print(f"  Найдена дополнительная периферия: {p_name} (структура: {struct_name})")
        else:
            continue

        # Ищем все экземпляры регистров в структуре
        instances = []
        lines = struct_body.split('\n')

        for line in lines:
            # Паттерн: __RW Type_reg_t name; // (offset)
            inst_match = re.search(
                r'(__[RW]*)\s+(\w+_reg_t)\s+(\w+)\s*;.*?\((0x[0-9A-Fa-f]+)\)',
                line
            )

            if not inst_match:
                # Пробуем без смещения в комментарии
                inst_match = re.search(
                    r'(__[RW]*)\s+(\w+_reg_t)\s+(\w+)\s*;',
                    line
                )
                if inst_match and 'RESERVED' not in line:
                    reg_type = inst_match.group(2).replace('_reg_t', '')
                    reg_name = inst_match.group(3)

                    instances.append({
                        'type': reg_type,
                        'name': reg_name,
                        'offset': None
                    })
                continue

            reg_type = inst_match.group(2).replace('_reg_t', '')
            reg_name = inst_match.group(3)
            offset = inst_match.group(4)

            if 'RESERVED' in reg_name or 'RESERVED' in reg_type:
                continue

            instances.append({
                'type': reg_type,
                'name': reg_name,
                'offset': offset
            })

        peripherals[p_name] = {
            'description': desc,
            'base_address': base_addr,
            'instances': instances,
            'struct_name': struct_name
        }
        print(f"    Регистров: {len(instances)}, базовый адрес: {base_addr or 'не задан'}")

    # Дополнительно ищем базовые адреса через constexpr
    base_pattern = r'constexpr\s+uint32_t\s+(\w+_BASE)\s*=\s*(0x[0-9A-Fa-f]+)\s*;'
    base_addresses = {}
    for match in re.finditer(base_pattern, content):
        name = match.group(1)
        addr = match.group(2)
        base_addresses[name] = addr

    # Применяем найденные адреса к перифериям, у которых они не заданы
    for p_name, p_info in peripherals.items():
        if p_info['base_address'] is None:
            # Пробуем найти по имени периферии
            expected_base = f"AM335x_{p_name}_BASE"
            if expected_base in base_addresses:
                p_info['base_address'] = base_addresses[expected_base]
                print(f"  Найден базовый адрес для {p_name}: {p_info['base_address']}")
            elif 'struct_name' in p_info:
                # Пробуем по имени структуры
                struct_base = p_info['struct_name'].replace('_Type', '_BASE')
                if struct_base in base_addresses:
                    p_info['base_address'] = base_addresses[struct_base]
                    print(f"  Найден базовый адрес для {p_name}: {p_info['base_address']}")

    return peripherals


def generate_svd(registers_info, peripherals_info):
    """Собирает XML-дерево SVD."""

    root = Element('device', {
        'schemaVersion': '1.3',
        'xmlns:xs': 'http://www.w3.org/2001/XMLSchema-instance',
        'xs:noNamespaceSchemaLocation': 'CMSIS-SVD_Schema_1_3.xsd'
    })

    SubElement(root, 'vendor').text = VENDOR
    SubElement(root, 'name').text = DEVICE_NAME
    SubElement(root, 'series').text = SERIES
    SubElement(root, 'version').text = VERSION
    SubElement(root, 'description').text = DESCRIPTION

    cpu = SubElement(root, 'cpu')
    SubElement(cpu, 'name').text = CPU_NAME
    SubElement(cpu, 'revision').text = CPU_REVISION
    SubElement(cpu, 'endian').text = CPU_ENDIAN

    SubElement(root, 'addressUnitBits').text = ADDRESS_UNIT_BITS
    SubElement(root, 'width').text = WIDTH
    SubElement(root, 'size').text = SIZE
    SubElement(root, 'resetValue').text = RESET_VALUE
    SubElement(root, 'resetMask').text = RESET_MASK

    peripherals_elem = SubElement(root, 'peripherals')

    for p_name, p_info in sorted(peripherals_info.items()):
        if not p_info['instances']:
            print(f"Предупреждение: Нет экземпляров регистров для {p_name}")
            continue

        if p_info['base_address'] is None:
            print(f"Предупреждение: Нет базового адреса для {p_name}, пропускаем")
            continue

        periph_elem = SubElement(peripherals_elem, 'peripheral')
        SubElement(periph_elem, 'name').text = p_name
        SubElement(periph_elem, 'description').text = p_info['description']
        SubElement(periph_elem, 'baseAddress').text = p_info['base_address']

        # Определяем groupName на основе имени
        if 'EMIF' in p_name or 'DDR' in p_name:
            SubElement(periph_elem, 'groupName').text = 'Memory'
        elif 'CM_' in p_name:
            SubElement(periph_elem, 'groupName').text = 'Clock Modules'
        elif 'PRM_' in p_name:
            SubElement(periph_elem, 'groupName').text = 'Power Reset Modules'
        else:
            SubElement(periph_elem, 'groupName').text = 'Peripherals'

        registers_elem = SubElement(periph_elem, 'registers')

        for inst in p_info['instances']:
            reg_type = inst['type']
            if reg_type not in registers_info:
                print(f"  Предупреждение: Тип регистра {reg_type} не найден для {inst['name']}")
                continue

            reg_data = registers_info[reg_type]

            reg_elem = SubElement(registers_elem, 'register')
            SubElement(reg_elem, 'name').text = inst['name']

            if inst['offset']:
                SubElement(reg_elem, 'addressOffset').text = inst['offset']
            else:
                print(f"  Предупреждение: Смещение для {inst['name']} не найдено, пропускаем")
                continue

            SubElement(reg_elem, 'description').text = reg_data.get('description', inst['name'])
            SubElement(reg_elem, 'size').text = '32'
            SubElement(reg_elem, 'access').text = 'read-write'

            reset_val = reg_data.get('reset_value', '0x00000000')
            SubElement(reg_elem, 'resetValue').text = reset_val

            if reg_data['fields']:
                fields_elem = SubElement(reg_elem, 'fields')
                for field in reg_data['fields']:
                    field_elem = SubElement(fields_elem, 'field')
                    SubElement(field_elem, 'name').text = field['name']
                    SubElement(field_elem, 'description').text = field['description']
                    SubElement(field_elem, 'bitOffset').text = str(field['offset'])
                    SubElement(field_elem, 'bitWidth').text = str(field['width'])
                    SubElement(field_elem, 'access').text = field['access']

    xml_str = tostring(root, 'utf-8')
    dom = parseString(xml_str)
    pretty_xml = dom.toprettyxml(indent="  ")
    return pretty_xml


def main(hpp_filepath):
    if not os.path.exists(hpp_filepath):
        print(f"Ошибка: Файл {hpp_filepath} не найден.")
        return

    print(f"Чтение файла: {hpp_filepath}")
    with open(hpp_filepath, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()

    print(f"Размер файла: {len(content)} байт")

    print("\n=== Парсинг регистровых типов ===")
    registers_info = parse_register_types(content)
    print(f"Всего найдено типов регистров: {len(registers_info)}")

    print("\n=== Парсинг периферийных структур ===")
    peripherals_info = parse_peripheral_instances(content, PERIPHERAL_CONFIG)

    print("\n=== Генерация SVD ===")
    svd_content = generate_svd(registers_info, peripherals_info)

    # Имя выходного файла на основе входного
    base_name = os.path.splitext(os.path.basename(hpp_filepath))[0]
    output_file = f"{base_name}.svd"

    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(svd_content)

    print(f"\n=== Готово! ===")
    print(f"SVD-файл сохранен как: {output_file}")
    print(f"Размер выходного файла: {len(svd_content)} байт")

    # Статистика
    total_registers = sum(len(p['instances']) for p in peripherals_info.values())
    total_with_addr = sum(1 for p in peripherals_info.values() if p['base_address'])
    print(f"Всего периферий: {len(peripherals_info)}")
    print(f"Периферий с адресами: {total_with_addr}")
    print(f"Всего регистров: {total_registers}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Использование: python hpp_to_svd.py <путь_к_заголовочному_файлу.hpp>")
        sys.exit(1)
    main(sys.argv[1])