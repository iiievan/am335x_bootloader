#!/usr/bin/env python3
"""
Парсер пинов AM335x из PDF даташита
Использует извлечение таблиц через pdfplumber
необходим пакет:
pip install pdfplumber

Использование: python3 parse_pins.py am3359_datasheet.pdf [page_number]
или python3 parse_pins.py am3359_datasheet.pdf  для всех страниц

в одной папке с проектом должен лежать фаил CONTROL_MODULE_offsets.hpp для нахождения offsets пинов.
"""

import re
import sys
from pathlib import Path
from typing import Dict, List, Optional
import pdfplumber


def parse_header_for_offsets(header_path: str = None) -> Dict[str, int]:
    """Парсит CONTROL_MODULE (copy).hpp и вычисляет смещения"""

    if header_path is None:
        header_path = Path(__file__).parent / "CONTROL_MODULE_offsets.hpp"

    with open(header_path, 'r', encoding='utf-8') as f:
        content = f.read()

    struct_pattern = r'struct AM335x_CTRL_MODULE_Type\s*\{([^}]+(?:[^{}]*\{[^}]*\}[^{}]*)*)\};'
    struct_match = re.search(struct_pattern, content, re.DOTALL)

    if not struct_match:
        raise ValueError("Не удалось найти структуру AM335x_CTRL_MODULE_Type")

    struct_body = struct_match.group(1)
    current_offset = 0
    offsets = {}

    lines = struct_body.split('\n')

    for line in lines:
        line = line.strip()

        offset_comment = re.search(r'//\s*\(0x([0-9A-Fa-f]+)\)', line)
        if offset_comment:
            current_offset = int(offset_comment.group(1), 16)

        if not line or line.startswith('//'):
            continue

        reserved_match = re.search(r'__R\s+uint32_t\s+RESERVED\d*\s*\[\s*(\d+)\s*\]\s*;', line)
        if reserved_match:
            count = int(reserved_match.group(1))
            current_offset += count * 4
            continue

        field_match = re.search(r'(\w+_reg_t)\s+(\w+)\s*;', line)
        if field_match:
            field_name = field_match.group(2)

            if field_name.startswith('conf_'):
                pin_name = field_name[5:].upper()

                if pin_name.startswith('ONF_'):
                    pin_name = pin_name[4:]

                offsets[pin_name] = current_offset

                # Варианты с 'n' вместо 'N'
                variants = {
                    'ADVN': 'ADVn', 'BEN0': 'BEn0', 'BEN1': 'BEn1',
                    'CSN0': 'CSn0', 'CSN1': 'CSn1', 'CSN2': 'CSn2', 'CSN3': 'CSn3',
                    'OEN': 'OEn', 'WPN': 'WPn'
                }
                for upper, lower_n in variants.items():
                    if upper in pin_name:
                        offsets[pin_name.replace(upper, lower_n)] = current_offset

            current_offset += 4

    print(f"[INFO] Найдено {len(offsets)} conf_ регистров")
    return offsets


def clean_pin_name(name: str) -> str:
    """Очищает имя пина от сносок в скобках, например 'LCD_DATA12(5)' -> 'LCD_DATA12'"""
    # Удаляем скобки и цифры в них: (5), (6), (7), (10) и т.д.
    cleaned = re.sub(r'\(\d+\)$', '', name.strip())
    return cleaned


def parse_pins_from_tables(pdf_path: str, page_num: int) -> List[Dict]:
    """
    Парсит пины из таблиц PDF.
    Каждый пин начинается с полной строки (с BGA координатами),
    затем идут строки с режимами 1-7 (первые три колонки пустые).
    """

    pins = []

    with pdfplumber.open(pdf_path) as pdf:
        if page_num > len(pdf.pages):
            print(f"[ERROR] Страница {page_num} не существует")
            return pins

        page = pdf.pages[page_num - 1]
        tables = page.extract_tables()

        for table in tables:
            current_pin = None
            modes = []

            for row in table:
                # Пропускаем пустые строки
                if not row or all(cell is None or cell.strip() == '' for cell in row if cell):
                    continue

                # Проверяем, это заголовок таблицы?
                if row[0] and 'BALL' in str(row[0]).upper():
                    continue

                # Если первые две колонки не пустые - это начало нового пина
                if row[0] and row[1] and row[2]:
                    # Сохраняем предыдущий пин если он был
                    if current_pin and modes:
                        gpio_info = extract_gpio_from_modes(modes)
                        if gpio_info:
                            pins.append({
                                'pin_name': current_pin['pin_name'],
                                'pin_name_clean': clean_pin_name(current_pin['pin_name']),
                                'zce_ball': current_pin['zce_ball'],
                                'zcz_ball': current_pin['zcz_ball'],
                                'modes': modes,
                                'gpio_port': gpio_info['port'],
                                'gpio_num': gpio_info['num'],
                                'gpio_full': gpio_info['full']
                            })
                            print(f"[FOUND] {current_pin['pin_name']} -> {gpio_info['full']}")

                    # Начинаем новый пин
                    zce_ball = str(row[0]).strip() if row[0] else ''
                    zcz_ball = str(row[1]).strip() if row[1] else ''
                    pin_name = str(row[2]).strip() if row[2] else ''
                    signal_name = str(row[3]).strip() if row[3] else ''
                    mode_str = str(row[4]).strip() if row[4] else ''
                    io_type = str(row[5]).strip() if row[5] else ''

                    current_pin = {
                        'pin_name': pin_name,
                        'zce_ball': zce_ball,
                        'zcz_ball': zcz_ball
                    }

                    modes = []

                    # Добавляем MODE 0
                    if mode_str and io_type:
                        try:
                            modes.append({
                                'signal': signal_name,
                                'mode': int(mode_str),
                                'type': io_type
                            })
                        except ValueError:
                            pass

                # Если первые три колонки пустые - это продолжение пина (дополнительные режимы)
                elif row[3] and len(row) > 5:
                    signal_name = str(row[3]).strip()
                    mode_str = str(row[4]).strip() if row[4] else ''
                    io_type = str(row[5]).strip() if row[5] else ''

                    if mode_str and io_type:
                        try:
                            modes.append({
                                'signal': signal_name,
                                'mode': int(mode_str),
                                'type': io_type
                            })
                        except ValueError:
                            pass

            # Сохраняем последний пин на странице
            if current_pin and modes:
                gpio_info = extract_gpio_from_modes(modes)
                if gpio_info:
                    pins.append({
                        'pin_name': current_pin['pin_name'],
                        'pin_name_clean': clean_pin_name(current_pin['pin_name']),
                        'zce_ball': current_pin['zce_ball'],
                        'zcz_ball': current_pin['zcz_ball'],
                        'modes': modes,
                        'gpio_port': gpio_info['port'],
                        'gpio_num': gpio_info['num'],
                        'gpio_full': gpio_info['full']
                    })
                    print(f"[FOUND] {current_pin['pin_name']} -> {gpio_info['full']}")

    return pins


def extract_gpio_from_modes(modes: List[Dict]) -> Optional[Dict]:
    """Извлекает GPIO информацию из списка режимов"""
    for mode in modes:
        if mode['mode'] == 7 and mode['type'].upper() == 'I/O':
            signal = mode['signal'].lower()
            if signal.startswith('gpio'):
                gpio_match = re.match(r'gpio(\d+)_(\d+)', signal)
                if gpio_match:
                    return {
                        'port': int(gpio_match.group(1)),
                        'num': int(gpio_match.group(2)),
                        'full': mode['signal']
                    }
    return None


def generate_cpp_code(pins: List[Dict], offsets: Dict[str, int]) -> str:
    """Генерирует C++ header файл"""

    # Удаляем дубликаты по чистому имени пина
    unique_pins = {}
    for pin in pins:
        clean_name = pin['pin_name_clean']
        if clean_name not in unique_pins:
            unique_pins[clean_name] = pin
        else:
            # Если дубликат, оставляем тот, где больше режимов
            if len(pin['modes']) > len(unique_pins[clean_name]['modes']):
                unique_pins[clean_name] = pin

    pins = list(unique_pins.values())

    header = f"""#ifndef _AM335X_PARSED_PINS_HPP_
#define _AM335X_PARSED_PINS_HPP_

/**
 * AUTOMATICALLY GENERATED FILE
 * Generated from AM335x datasheet
 * Total GPIO pins: {len(pins)}
 */

#include <cstdint>
#include "REGS/REGS.hpp"
#include "pins/pin.hpp"

namespace HAL::PINS
{{
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    class pin;

"""

    generated_pins = []
    warnings = []

    for pin in sorted(pins, key=lambda x: (x['gpio_port'], x['gpio_num'])):
        pin_name = pin['pin_name']
        clean_name = pin['pin_name_clean']

        # Получаем offset по ЧИСТОМУ имени
        offset = offsets.get(clean_name)
        if offset is None:
            alt_name = clean_name.replace('n', 'N')
            offset = offsets.get(alt_name)

            if offset is None:
                warnings.append(f"[WARNING] Offset не найден для {pin_name} (clean: {clean_name})")
                continue

        # Генерируем enum значения
        enum_values = []
        seen_modes = set()

        for mode in pin['modes']:
            mode_num = mode['mode']
            if mode_num in seen_modes:
                continue
            seen_modes.add(mode_num)

            signal = mode['signal'].lower()
            if mode_num == 7:
                comment = f"// {mode['type']} (GPIO)"
            else:
                comment = f"// {mode['type']}"

            enum_values.append(f"        {signal:<40} = {mode_num}, {comment}")

        # Используем чистое имя для C++ идентификаторов
        cpp_name = clean_name.replace('-', '_').replace('/', '_')

        enum_code = f"""
    // ========================================================================
    // {pin_name} (ZCZ: {pin['zcz_ball']}, ZCE: {pin['zce_ball']}) -> {pin['gpio_full']}
    // ========================================================================
    enum class e_{cpp_name} : uint8_t
    {{
{chr(10).join(enum_values)}
    }};

    using {cpp_name} = pin<e_{cpp_name}, {pin['gpio_num']}U, 0x{offset:03X}>;
    inline {cpp_name} {cpp_name.lower()}{{REGS::GPIO::AM335x_GPIO_{pin['gpio_port']}}}; // {pin['gpio_full']}
"""
        generated_pins.append(enum_code)

    # Выводим предупреждения
    for w in warnings:
        print(w)

    footer = """
} // namespace HAL::PINS

#endif // _AM335X_PARSED_PINS_HPP_
"""

    return header + '\n'.join(generated_pins) + footer


def main():
    if len(sys.argv) < 2:
        print("Использование: python3 parse_pins.py <pdf_file> [page_number]")
        print("Если page_number не указан, парсятся страницы 19-47")
        sys.exit(1)

    pdf_path = sys.argv[1]

    if len(sys.argv) >= 3:
        page_nums = [int(sys.argv[2])]
    else:
        # Страницы с таблицами пинов (19-47)
        page_nums = list(range(19, 48))

    print(f"=== ПАРСЕР ПИНОВ AM335x ===\n")
    print(f"Страницы: {page_nums}")

    # 1. Парсим offsets из header
    print("\n[STEP 1] Парсинг CONTROL_MODULE (copy).hpp...")
    offsets = parse_header_for_offsets()

    # 2. Парсим все страницы
    all_pins = []
    for page_num in page_nums:
        print(f"\n[STEP 2] Обработка страницы {page_num}...")
        pins = parse_pins_from_tables(pdf_path, page_num)
        all_pins.extend(pins)
        print(f"  Найдено пинов на странице: {len(pins)}")

    print(f"\n[INFO] Всего найдено GPIO пинов: {len(all_pins)}")

    if not all_pins:
        print("[ERROR] Пины не найдены")
        sys.exit(1)

    # 3. Генерируем C++ код
    print("\n[STEP 3] Генерация C++ кода...")
    cpp_code = generate_cpp_code(all_pins, offsets)

    # 4. Сохраняем
    output_file = "am335x_all_pins.hpp"
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(cpp_code)

    print(f"\n[SUCCESS] Файл сохранен: {output_file}")

    # Статистика по портам
    print("\n=== СТАТИСТИКА ПО GPIO ПОРТАМ ===")
    for port in [0, 1, 2, 3]:
        count = sum(1 for p in all_pins if p['gpio_port'] == port)
        if count > 0:
            print(f"  GPIO{port}: {count} pins")


if __name__ == "__main__":
    main()