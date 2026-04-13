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

                # Извлекаем поля
                fields = self._extract_fields(page, text, reg_name)

                # Постобработка полей
                fields = self._postprocess_fields(fields)

                return {
                    'name': reg_name,
                    'offset': offset,
                    'reset': reset,
                    'fields': fields,
                    'page': page_num + 1
                }

        return None

    def _extract_fields(self, page, text: str, reg_name: str):
        """Извлекает поля регистра"""
        fields = []

        # Ищем секцию Table или Field Descriptions
        lines = text.split('\n')
        table_start = -1

        for i, line in enumerate(lines):
            if 'Field Descriptions' in line or re.search(r'Table\s+[\d\-]+\.', line):
                table_start = i
                break

        if table_start != -1:
            # Парсим строки таблицы Field Descriptions
            for i in range(table_start + 1, min(table_start + 50, len(lines))):
                line = lines[i].strip()
                if not line:
                    continue

                # Останавливаемся при следующем заголовке регистра
                if re.match(r'^\d+\.\d+\.\d+\s+\w+\s+Register', line, re.IGNORECASE):
                    break

                # Останавливаемся при Figure
                if 'Figure' in line:
                    break

                # Пропускаем строки с колонтитулами
                if 'Copyright' in line or 'www.ti.com' in line:
                    continue

                # Пропускаем легенду
                if 'LEGEND' in line:
                    continue

                field = self._parse_table_line(line)
                if field:
                    fields.append(field)

        # Если нашли поля, возвращаем их
        if fields:
            return fields

        # Если не нашли поля через таблицу, пробуем через битовую маску
        return self._extract_from_bitmask(text, reg_name)

    def _parse_table_line(self, line: str):
        """Парсит строку таблицы Field Descriptions"""
        # Нормализуем пробелы
        line = re.sub(r'\s+', ' ', line).strip()

        # Паттерн для строки таблицы
        pattern = r'^(\d+(?:-\d+)?)\s+([A-Za-z_][A-Za-z0-9_]*)\s+(R/W|R|W1toCl)\s+([0-9a-fA-F]+h?)\s+(.*?)$'

        match = re.match(pattern, line, re.IGNORECASE)
        if not match:
            return None

        bits = match.group(1)
        name = match.group(2)
        access = match.group(3)
        reset_val = match.group(4)
        description = match.group(5).strip()

        # Валидация битов
        try:
            if '-' in bits:
                high, low = map(int, bits.split('-'))
                if high < low or high > 31 or low < 0:
                    return None
            else:
                bit = int(bits)
                if bit < 0 or bit > 31:
                    return None
        except (ValueError, TypeError):
            return None

        # Очищаем описание
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

    def _extract_from_bitmask(self, text: str, reg_name: str):
        """Извлекает поля из битовой маски (для регистров без Field Descriptions)"""
        fields = []

        # Ищем Figure с битовой маской
        bit_pattern = r'(\d+(?:-\d+)?)\s+([A-Za-z_][A-Za-z0-9_]*)'
        matches = re.finditer(bit_pattern, text)

        for match in matches:
            bits = match.group(1)
            name = match.group(2)

            # Пропускаем очевидный мусор
            if name.lower() in ['figure', 'table', 'legend', 'register', 'shown',
                                'described', 'and', 'to', 'of', 'for', 'the',
                                'copyright', 'ti', 'incorporated', 'submit', 'feedback']:
                continue

            # Валидация битов
            try:
                if '-' in bits:
                    high, low = map(int, bits.split('-'))
                    if high < low or high > 31 or low < 0:
                        continue
                else:
                    bit = int(bits)
                    if bit < 0 or bit > 31:
                        continue
            except (ValueError, TypeError):
                continue

            # Пропускаем, если имя поля содержит номер страницы
            if re.search(r'\d', name) and len(name) < 4:
                continue

            fields.append({
                'bits': bits,
                'name': name,
                'access': 'R/W',
                'reset': '0h',
                'description': f'Field {name}'
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

    def _postprocess_fields(self, fields):
        """Постобработка полей: объединение дубликатов и соседних reserved"""
        if not fields:
            return fields

        # Шаг 1: Объединяем пересекающиеся/дублирующиеся поля
        fields = self._merge_overlapping_fields(fields)

        # Шаг 2: Объединяем соседние зарезервированные поля
        fields = self._merge_adjacent_reserved(fields)

        return fields

    def _merge_overlapping_fields(self, fields):
        """Объединяет поля, которые пересекаются или дублируются"""
        if not fields:
            return fields

        def get_low_bit(bits_str: str) -> int:
            if '-' in bits_str:
                return int(bits_str.split('-')[1])
            return int(bits_str)

        def get_high_bit(bits_str: str) -> int:
            if '-' in bits_str:
                return int(bits_str.split('-')[0])
            return int(bits_str)

        # Сортируем по младшему биту
        sorted_fields = sorted(fields, key=lambda x: get_low_bit(x['bits']))
        merged = []

        for field in sorted_fields:
            if not merged:
                merged.append(field)
                continue

            last = merged[-1]
            last_low = get_low_bit(last['bits'])
            last_high = get_high_bit(last['bits'])
            curr_low = get_low_bit(field['bits'])
            curr_high = get_high_bit(field['bits'])

            # Проверяем пересечение или дублирование
            if curr_low <= last_high:
                # Поля пересекаются - объединяем
                new_low = min(last_low, curr_low)
                new_high = max(last_high, curr_high)

                # Берём имя от первого поля (или не-reserved)
                if last['name'].lower() != 'reserved':
                    name = last['name']
                else:
                    name = field['name']

                merged[-1] = {
                    'bits': f"{new_high}-{new_low}",
                    'name': name,
                    'access': last['access'] if last['access'] != 'R' else field['access'],
                    'reset': last['reset'],
                    'description': last['description'][:100]
                }
            else:
                merged.append(field)

        return merged

    def _merge_adjacent_reserved(self, fields):
        """Объединяет соседние зарезервированные поля"""
        if not fields:
            return fields

        def get_low_bit(bits_str: str) -> int:
            if '-' in bits_str:
                return int(bits_str.split('-')[1])
            return int(bits_str)

        def get_high_bit(bits_str: str) -> int:
            if '-' in bits_str:
                return int(bits_str.split('-')[0])
            return int(bits_str)

        sorted_fields = sorted(fields, key=lambda x: get_low_bit(x['bits']))
        merged = []
        i = 0

        while i < len(sorted_fields):
            current = sorted_fields[i]

            if current['name'].lower() != 'reserved':
                merged.append(current)
                i += 1
                continue

            # Начинаем группу зарезервированных полей
            reserved_start = get_low_bit(current['bits'])
            reserved_end = get_high_bit(current['bits'])
            j = i + 1

            while j < len(sorted_fields):
                next_field = sorted_fields[j]
                if next_field['name'].lower() != 'reserved':
                    break

                next_low = get_low_bit(next_field['bits'])
                if next_low == reserved_end + 1:
                    reserved_end = get_high_bit(next_field['bits'])
                    j += 1
                else:
                    break

            merged.append({
                'bits': f"{reserved_end}-{reserved_start}",
                'name': 'Reserved',
                'access': 'R',
                'reset': '0h',
                'description': 'Reserved'
            })
            i = j

        return merged

    def _convert_hex_format(self, hex_str: str) -> str:
        """Конвертирует формат '6A4h' в '0x6A4'"""
        hex_val = hex_str.rstrip('h').rstrip('H')
        return f"0x{hex_val}"

    def generate_c_code(self, reg_info: dict) -> str:
        """Генерирует C union для регистра"""
        lines = []

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
            def get_low_bit(bits_str: str) -> int:
                if '-' in bits_str:
                    return int(bits_str.split('-')[1])
                return int(bits_str)

            sorted_fields = sorted(reg_info['fields'], key=lambda x: get_low_bit(x['bits']))
            current_bit = 0

            for field in sorted_fields:
                if '-' in field['bits']:
                    high, low = map(int, field['bits'].split('-'))
                else:
                    low = high = int(field['bits'])

                if current_bit < low:
                    reserved_bits = low - current_bit
                    lines.append(
                        f"        uint32_t                  :{reserved_bits:2d}; // bit: {current_bit:2d}..{low - 1:2d} Reserved.")
                    current_bit = low

                width = high - low + 1

                if field['name'].lower() == 'reserved':
                    lines.append(
                        f"        uint32_t                  :{width:2d}; // bit: {low:2d}..{high:2d} Reserved.")
                else:
                    comment = f"bit: {low:2d}..{high:2d} ({field['access']})"
                    if field['description']:
                        short_desc = field['description'][:60]
                        comment += f" {short_desc}"
                    if len(comment) > 90:
                        comment = comment[:87] + "..."
                    lines.append(f"        uint32_t    {field['name']:25s}:{width:2d}; // {comment}")

                current_bit = high + 1

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
    else:
        print(f"\n[ERROR] Регистр '{reg_name}' не найден")
        sys.exit(1)


if __name__ == "__main__":
    main()