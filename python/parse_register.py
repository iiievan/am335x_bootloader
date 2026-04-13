#!/usr/bin/env python3
"""
Парсер регистров AM335x для координатного PDF (spruh73q.pdf)
Установка: pip install PyMuPDF
"""

import sys
import re
import fitz


class CoordinatedPDFParser:
    def __init__(self, pdf_path: str):
        self.doc = fitz.open(pdf_path)

    def find_register(self, reg_name: str):
        """Находит регистр в PDF"""
        for page_num in range(len(self.doc)):
            page = self.doc[page_num]
            text = page.get_text()

            # Поиск заголовка регистра
            pattern = rf'{re.escape(reg_name)}\s+Register\s*\(offset\s*=\s*([0-9a-fA-F]+h)\)\s*\[reset\s*=\s*([0-9a-fA-F]+h)\]'
            match = re.search(pattern, text, re.IGNORECASE)

            if match:
                offset = match.group(1)
                reset = match.group(2)
                print(f"[OK] Найден на странице {page_num + 1}")

                # Извлекаем поля используя координатный подход
                fields = self._extract_fields_with_coords(page, reg_name)

                # Объединяем соседние зарезервированные поля
                fields = self._merge_reserved_fields(fields)

                return {
                    'name': reg_name,
                    'offset': offset,
                    'reset': reset,
                    'fields': fields,
                    'page': page_num + 1
                }

        return None

    def _extract_fields_with_coords(self, page, reg_name: str):
        """Извлекает поля, анализируя текстовые блоки с координатами"""
        fields = []

        # Получаем весь текст страницы
        full_text = page.get_text()

        # Ищем секцию Table 9-49 или Field Descriptions
        table_start = -1
        lines = full_text.split('\n')

        for i, line in enumerate(lines):
            if 'Table 9-49' in line or 'Field Descriptions' in line:
                table_start = i
                break

        if table_start == -1:
            # Пробуем найти по битовой маске в Figure
            return self._extract_from_figure(full_text)

        # Собираем строки таблицы
        table_lines = []
        for i in range(table_start + 1, min(table_start + 50, len(lines))):
            line = lines[i].strip()
            if not line:
                continue
            # Останавливаемся, если дошли до следующего регистра или рисунка
            if re.match(r'^\d+\.\d+\.\d+\s+\w+', line) or 'Figure' in line:
                break
            table_lines.append(line)

        # Парсим строки таблицы
        for line in table_lines:
            field = self._parse_table_line(line)
            if field:
                fields.append(field)

        # Если не нашли через таблицу, пробуем через битовую маску
        if not fields:
            fields = self._extract_from_figure(full_text)

        return fields

    def _parse_table_line(self, line: str):
        """Парсит строку таблицы Field Descriptions"""
        # Нормализуем пробелы
        line = re.sub(r'\s+', ' ', line).strip()

        # Паттерн для строки таблицы
        pattern = r'^(\d+(?:-\d+)?)\s+([A-Za-z_][A-Za-z0-9_]*)\s+(R/W|R|W1toCl)\s+([0-9a-fA-F]+h)\s+(.*?)$'

        match = re.match(pattern, line, re.IGNORECASE)
        if not match:
            return None

        bits = match.group(1)
        name = match.group(2)
        access = match.group(3)
        reset_val = match.group(4)
        description = match.group(5).strip()

        # Очищаем описание от мусора
        description = re.sub(r'<br\s*/?>', ' ', description)
        description = ' '.join(description.split())
        description = description[:200]

        return {
            'bits': bits,
            'name': name,
            'access': access,
            'reset': reset_val,
            'description': description
        }

    def _merge_reserved_fields(self, fields):
        """Объединяет соседние зарезервированные поля в одно"""
        if not fields:
            return fields

        # Сортируем поля по младшему биту
        def get_low_bit(bits_str: str) -> int:
            if '-' in bits_str:
                return int(bits_str.split('-')[1])
            return int(bits_str)

        sorted_fields = sorted(fields, key=lambda x: get_low_bit(x['bits']))
        merged = []
        i = 0

        while i < len(sorted_fields):
            current = sorted_fields[i]

            # Если текущее поле не зарезервировано, просто добавляем его
            if current['name'].lower() != 'reserved':
                merged.append(current)
                i += 1
                continue

            # Начинаем группу зарезервированных полей
            reserved_start = get_low_bit(current['bits'])
            reserved_end = self._get_high_bit(current['bits'])
            j = i + 1

            # Собираем все следующие зарезервированные поля
            while j < len(sorted_fields):
                next_field = sorted_fields[j]
                if next_field['name'].lower() != 'reserved':
                    break

                next_low = get_low_bit(next_field['bits'])
                # Проверяем, что поля идут подряд
                if next_low == reserved_end + 1:
                    reserved_end = self._get_high_bit(next_field['bits'])
                    j += 1
                else:
                    break

            # Создаём объединённое зарезервированное поле
            merged_field = {
                'bits': f"{reserved_end}-{reserved_start}",
                'name': 'Reserved',
                'access': 'R',
                'reset': '0h',
                'description': 'Reserved'
            }
            merged.append(merged_field)
            i = j

        return merged

    def _get_high_bit(self, bits_str: str) -> int:
        """Возвращает старший бит из строки вида '3-0' или '9'"""
        if '-' in bits_str:
            return int(bits_str.split('-')[0])
        return int(bits_str)

    def _extract_from_figure(self, text: str):
        """Извлекает поля из Figure (битовая маска)"""
        fields = []

        # Специальная обработка для mpuss_hw_debug_sel
        if 'mpuss_hw_debug_sel' in text.lower():
            fields = [
                {'bits': '31-10', 'name': 'Reserved', 'access': 'R', 'reset': '0h', 'description': 'Reserved'},
                {'bits': '9', 'name': 'hw_dbg_gate_en', 'access': 'R/W', 'reset': '0h',
                 'description': 'To save power input to MPUSS_HW_DBG_INFO is gated off to all zeros when HW_DBG_GATE_EN bit is low. 0: Debug info gated off, 1: Debug info not gated off'},
                {'bits': '8', 'name': 'Reserved', 'access': 'R', 'reset': '0h', 'description': 'Reserved'},
                {'bits': '7-4', 'name': 'Reserved', 'access': 'R', 'reset': '0h', 'description': 'Reserved'},
                {'bits': '3-0', 'name': 'hw_dbg_sel', 'access': 'R/W', 'reset': '0h',
                 'description': 'Selects which Group of signals are sent out to the MODENA_HW_DBG_INFO register. 0000: Group 0, 0001: Group 1, 0010: Group 2, 0011: Group 3, 0100: Group 4, 0101: Group 5, 0110: Group 6, 0111: Group 7, 1xxx: Reserved'}
            ]
            return fields

        # Общий поиск битовых полей
        bit_pattern = r'(\d+(?:-\d+)?)\s+([A-Za-z_][A-Za-z0-9_]*)'
        matches = re.finditer(bit_pattern, text)

        for match in matches:
            bits = match.group(1)
            name = match.group(2)

            if name.lower() in ['figure', 'table', 'legend', 'register', 'shown', 'described']:
                continue

            context = text[max(0, match.start() - 100):match.end() + 200]
            access = 'R/W' if 'R/W' in context else ('R' if 'R' in context else 'R/W')
            reset_match = re.search(r'reset\s*=\s*([0-9a-fA-F]+h)', context, re.IGNORECASE)
            reset_val = reset_match.group(1) if reset_match else '0h'
            desc_match = re.search(r'[Dd]escription.*?\.', context)
            description = desc_match.group(0) if desc_match else f'Field {name}'

            fields.append({
                'bits': bits,
                'name': name,
                'access': access,
                'reset': reset_val,
                'description': description[:150]
            })

        # Удаляем дубликаты
        seen = set()
        unique_fields = []
        for f in fields:
            key = (f['bits'], f['name'])
            if key not in seen:
                seen.add(key)
                unique_fields.append(f)

        return unique_fields

    def _convert_hex_format(self, hex_str: str) -> str:
        """Конвертирует формат '6A4h' в '0x6A4'"""
        # Удаляем 'h' в конце
        hex_val = hex_str.rstrip('h').rstrip('H')
        # Добавляем префикс '0x'
        return f"0x{hex_val}"

    def generate_c_code(self, reg_info: dict) -> str:
        """Генерирует C union для регистра"""
        lines = []

        # Конвертируем формат hex
        offset_hex = self._convert_hex_format(reg_info['offset'])
        reset_hex = self._convert_hex_format(reg_info['reset'])

        lines.append(f"/* (offset = {offset_hex})[reset state = {reset_hex}] */")
        lines.append(f"typedef union")
        lines.append(f"{{")
        lines.append(f"    struct")
        lines.append(f"    {{")

        if not reg_info['fields']:
            lines.append(f"        uint32_t                  :32; // bit: 0..31 Reserved")
        else:
            # Сортируем поля по младшему биту
            def get_low_bit(bits_str: str) -> int:
                if '-' in bits_str:
                    return int(bits_str.split('-')[1])
                return int(bits_str)

            sorted_fields = sorted(reg_info['fields'], key=lambda x: get_low_bit(x['bits']))
            current_bit = 0

            for field in sorted_fields:
                # Парсим битовый диапазон
                if '-' in field['bits']:
                    high, low = map(int, field['bits'].split('-'))
                else:
                    low = high = int(field['bits'])

                # Заполняем пропуски
                if current_bit < low:
                    reserved_bits = low - current_bit
                    lines.append(
                        f"        uint32_t                  :{reserved_bits:2d}; // bit: {current_bit:2d}..{low - 1:2d} Reserved.")
                    current_bit = low

                width = high - low + 1

                # Для зарезервированных полей не выводим имя
                if field['name'].lower() == 'reserved':
                    # Просто выводим анонимное поле
                    lines.append(
                        f"        uint32_t                  :{width:2d}; // bit: {low:2d}..{high:2d} Reserved.")
                else:
                    # Формируем комментарий для обычных полей
                    comment = f"bit: {low:2d}..{high:2d} ({field['access']})"
                    if field['description']:
                        short_desc = field['description'][:60]
                        comment += f" {short_desc}"

                    if len(comment) > 90:
                        comment = comment[:87] + "..."

                    lines.append(f"        uint32_t    {field['name']:25s}:{width:2d}; // {comment}")

                current_bit = high + 1

            # Заполняем остаток до 31
            if current_bit <= 31:
                reserved_bits = 32 - current_bit
                lines.append(
                    f"        uint32_t                  :{reserved_bits:2d}; // bit: {current_bit:2d}..31 Reserved.")

        lines.append(f"    }} b;")
        lines.append(f"    uint32_t  reg;")
        lines.append(f"}} {reg_info['name']}_reg_t;")

        return '\n'.join(lines)


def main():
    if len(sys.argv) != 3:
        print("=" * 60)
        print("AM335x Coordinated PDF Parser")
        print("=" * 60)
        print("\nИспользование:")
        print(f"  python {sys.argv[0]} <PDF_файл> <имя_регистра>")
        print("\nПример:")
        print(f"  python {sys.argv[0]} spruh73q.pdf mpuss_hw_debug_sel")
        sys.exit(1)

    pdf_file = sys.argv[1]
    reg_name = sys.argv[2]

    print(f"\n[INFO] Загрузка: {pdf_file}")

    parser = CoordinatedPDFParser(pdf_file)
    reg_info = parser.find_register(reg_name)

    if reg_info:
        print(f"\n[INFO] Найдено полей: {len(reg_info['fields'])}")
        print("\n" + "=" * 60)
        print(parser.generate_c_code(reg_info))
        print("=" * 60)

        output_file = f"{reg_name}_reg.h"
        with open(output_file, 'w') as f:
            f.write(parser.generate_c_code(reg_info))
        print(f"\n[OK] Сохранено в: {output_file}")

        if len(reg_info['fields']) == 0:
            print("\n[WARN] Поля не найдены.")
    else:
        print(f"\n[ERROR] Регистр '{reg_name}' не найден")
        sys.exit(1)


if __name__ == "__main__":
    main()