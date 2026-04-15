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
        """Находит регистр и собирает Field Descriptions даже при переносе на следующие страницы"""
        for page_num in range(len(self.doc)):
            page = self.doc[page_num]
            text = page.get_text()

            pattern = rf'{re.escape(reg_name)}\s+Register\s*\(offset\s*=\s*([0-9a-fA-F]+h)\)\s*\[reset\s*=\s*([0-9a-fA-F]+h)\]'
            match = re.search(pattern, text, re.IGNORECASE)

            if match:
                offset = match.group(1)
                reset = match.group(2)
                print(f"[OK] Найден на странице {page_num + 1}")

                fields = []
                max_extra_pages = 3  # на всякий случай

                for extra in range(max_extra_pages + 1):
                    if page_num + extra >= len(self.doc):
                        break

                    curr_page = self.doc[page_num + extra]
                    curr_html = curr_page.get_text("html")
                    curr_text = curr_page.get_text()

                    # Пропускаем страницу, если на ней уже начался следующий регистр
                    if extra > 0 and re.search(rf'\w+ Register \(offset', curr_text, re.IGNORECASE):
                        print(f"[INFO] Следующий регистр обнаружен на странице {page_num + extra + 1}, останавливаемся")
                        break

                    curr_fields = self._extract_fields(curr_page, reg_name)

                    if curr_fields:
                        print(f"[INFO] Собрано {len(curr_fields)} полей со страницы {page_num + extra + 1}")
                        fields.extend(curr_fields)

                    # Если на странице есть "(continued)", продолжаем
                    if extra > 0 and 'continued' not in curr_html.lower() and 'Field Descriptions' in curr_html:
                        # Если это уже новая таблица — выходим
                        break

                # Убираем дубликаты по битам
                fields = self._remove_duplicate_bits(fields)

                # Постобработка (твоя любимая часть)
                fields = self._postprocess_fields(fields, reg_name)

                return {
                    'name': reg_name,
                    'offset': offset,
                    'reset': reset,
                    'fields': fields,
                    'page': page_num + 1
                }

        return None

    def _remove_duplicate_bits(self, fields):
        """Удаляет дубликаты по диапазону битов"""
        seen = {}
        unique = []
        for f in fields:
            key = f.get('bits', '')
            if key and key not in seen:
                seen[key] = True
                unique.append(f)
        return unique

    def _extract_fields(self, page, reg_name: str):
        """Извлекает поля из HTML-таблицы Field Descriptions"""
        fields = []

        # Получаем HTML-представление страницы
        html = page.get_text("html")

        # Ищем секцию Field Descriptions
        if 'Field Descriptions' not in html:
            return self._extract_from_bitmask(page.get_text(), reg_name)

        # Находим начало таблицы
        start_idx = html.find('Field Descriptions')
        if start_idx == -1:
            return []

        # Ищем строки таблицы в формате <p> с координатами
        lines_pattern = r'<p style="top:([\d.]+)pt;left:([\d.]+)pt[^>]*>(.*?)</p>'

        # Извлекаем все элементы <p> после Field Descriptions
        table_html = html[start_idx:start_idx + 20000]
        matches = list(re.finditer(lines_pattern, table_html, re.DOTALL))

        # Группируем строки по Y-координате (каждая строка таблицы имеет свою Y)
        rows = {}
        for match in matches:
            y = float(match.group(1))
            content = re.sub(r'<[^>]+>', '', match.group(3)).strip()
            if content:
                if y not in rows:
                    rows[y] = []
                rows[y].append(content)

        # Парсим строки таблицы (каждая строка должна иметь 5 колонок)
        for y, cols in sorted(rows.items()):
            if len(cols) >= 4:  # Минимум 4 колонки (Bit, Field, Type, Reset)
                # Очищаем колонки
                bits = cols[0].strip() if len(cols) > 0 else ''
                name = cols[1].strip() if len(cols) > 1 else ''
                access = cols[2].strip() if len(cols) > 2 else ''
                reset_val = cols[3].strip() if len(cols) > 3 else ''
                description = cols[4].strip() if len(cols) > 4 else ''

                # Пропускаем заголовки
                if bits.lower() in ['bit', 'bits'] or name.lower() in ['field']:
                    continue

                # Валидация битов
                if not re.match(r'^\d+(?:-\d+)?$', bits):
                    continue

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

                # Нормализация доступа
                if access == 'W1toCl':
                    access = 'W'
                elif access not in ['R', 'W', 'R/W']:
                    # Пробуем извлечь из формата R-0h
                    if '-' in access:
                        access_part = access.split('-')[0]
                        if access_part in ['R', 'W', 'R/W']:
                            access = access_part
                        else:
                            access = 'R/W'
                    else:
                        access = 'R/W'

                # Нормализация сброса
                reset_val = re.sub(r'[^0-9a-fA-FhxX]', '', reset_val)
                if not reset_val:
                    reset_val = '0h'

                fields.append({
                    'bits': bits,
                    'name': name if name != 'Reserved' else 'Reserved',
                    'access': access,
                    'reset': reset_val,
                    'description': description[:200]
                })

        return fields

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
                'name': name if name != 'Reserved' else 'Reserved',
                'access': 'R',
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

    def _postprocess_fields(self, fields, reg_name: str):
        """Постобработка полей: объединение дубликатов, соседних reserved, нормализация битов"""
        if not fields:
            return fields

        # Шаг 1: Нормализуем отображение битов (5..5 -> 5)
        fields = self._normalize_bit_display(fields)

        # Шаг 2: Объединяем пересекающиеся/дублирующиеся поля
        fields = self._merge_overlapping_fields(fields)

        # Шаг 3: Объединяем соседние зарезервированные поля и убираем их имена
        fields = self._merge_adjacent_reserved(fields)

        # Шаг 4: Проверяем сумму битов
        self._check_bit_sum(fields, reg_name)

        return fields

    def _normalize_bit_display(self, fields):
        """Нормализует отображение битов: 5..5 -> 5, 5-5 -> 5"""
        for field in fields:
            if '..' in field['bits']:
                high, low = map(int, field['bits'].split('..'))
                if high == low:
                    field['bits'] = str(high)
            elif '-' in field['bits']:
                high, low = map(int, field['bits'].split('-'))
                if high == low:
                    field['bits'] = str(high)
        return fields

    def _merge_overlapping_fields(self, fields):
        """Объединяет поля, которые пересекаются или дублируются"""
        if not fields:
            return fields

        def get_low_bit(bits_str: str) -> int:
            if '..' in bits_str:
                return int(bits_str.split('..')[1])
            elif '-' in bits_str:
                return int(bits_str.split('-')[1])
            return int(bits_str)

        def get_high_bit(bits_str: str) -> int:
            if '..' in bits_str:
                return int(bits_str.split('..')[0])
            elif '-' in bits_str:
                return int(bits_str.split('-')[0])
            return int(bits_str)

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

            if curr_low <= last_high:
                new_low = min(last_low, curr_low)
                new_high = max(last_high, curr_high)

                if last['name'].lower() != 'reserved':
                    name = last['name']
                else:
                    name = field['name']

                # Берём доступ с наименьшими ограничениями
                if 'R/W' in [last['access'], field['access']]:
                    access = 'R/W'
                elif 'W' in [last['access'], field['access']]:
                    access = 'W'
                else:
                    access = 'R'

                # Используем дефис для диапазона, а не '..'
                merged[-1] = {
                    'bits': f"{new_high}-{new_low}" if new_high != new_low else str(new_low),
                    'name': name,
                    'access': access,
                    'reset': last['reset'],
                    'description': last['description'][:100]
                }
            else:
                merged.append(field)

        return merged

    def _merge_adjacent_reserved(self, fields):
        """Объединяет соседние зарезервированные поля и убирает их имена"""
        if not fields:
            return fields

        def get_low_bit(bits_str: str) -> int:
            if '..' in bits_str:
                return int(bits_str.split('..')[1])
            elif '-' in bits_str:
                return int(bits_str.split('-')[1])
            return int(bits_str)

        def get_high_bit(bits_str: str) -> int:
            if '..' in bits_str:
                return int(bits_str.split('..')[0])
            elif '-' in bits_str:
                return int(bits_str.split('-')[0])
            return int(bits_str)

        sorted_fields = sorted(fields, key=lambda x: get_low_bit(x['bits']))
        merged = []
        i = 0

        while i < len(sorted_fields):
            current = sorted_fields[i]

            # Если не зарезервировано или уже не Reserved (после объединения)
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

            # Создаём анонимное зарезервированное поле (без имени)
            bits_str = f"{reserved_end}-{reserved_start}" if reserved_end != reserved_start else str(reserved_start)
            merged.append({
                'bits': bits_str,
                'name': 'Reserved',  # Оставляем маркер, но при генерации имени не будет
                'access': 'R',
                'reset': '0h',
                'description': 'Reserved'
            })
            i = j

        return merged

    def _check_bit_sum(self, fields, reg_name: str):
        """Проверяет, что сумма всех битов равна 32"""
        total_bits = 0
        for field in fields:
            if '..' in field['bits']:
                high, low = map(int, field['bits'].split('..'))
                total_bits += high - low + 1
            elif '-' in field['bits']:
                high, low = map(int, field['bits'].split('-'))
                total_bits += high - low + 1
            else:
                total_bits += 1

        if total_bits != 32:
            print(f"[WARN] Регистр '{reg_name}': сумма битов = {total_bits} (должно быть 32)")

    def _convert_hex_format(self, hex_str: str) -> str:
        """Конвертирует формат '6A4h' в '0x6A4'"""
        hex_val = hex_str.rstrip('h').rstrip('H')
        if hex_val.startswith('0x'):
            return hex_val
        return f"0x{hex_val}"

    def _parse_bits_range(self, bits_str: str):
        """Парсит строку битов в формате '5', '5-5', '5..5'"""
        if '..' in bits_str:
            high, low = map(int, bits_str.split('..'))
        elif '-' in bits_str:
            high, low = map(int, bits_str.split('-'))
        else:
            high = low = int(bits_str)
        return high, low

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
                high, low = self._parse_bits_range(bits_str)
                return low

            sorted_fields = sorted(reg_info['fields'], key=lambda x: get_low_bit(x['bits']))
            current_bit = 0

            for field in sorted_fields:
                high, low = self._parse_bits_range(field['bits'])

                if current_bit < low:
                    reserved_bits = low - current_bit
                    if reserved_bits == 1:
                        lines.append(
                            f"        uint32_t                  :{reserved_bits:2d}; // bit: {current_bit} Reserved.")
                    else:
                        lines.append(
                            f"        uint32_t                  :{reserved_bits:2d}; // bit: {current_bit}..{low - 1} Reserved.")
                    current_bit = low

                width = high - low + 1

                # Для зарезервированных полей не выводим имя
                if field['name'].lower() == 'reserved':
                    if width == 1:
                        lines.append(
                            f"        uint32_t                  :{width:2d}; // bit: {low} Reserved.")
                    else:
                        lines.append(
                            f"        uint32_t                  :{width:2d}; // bit: {low}..{high} Reserved.")
                else:
                    if low == high:
                        bit_display = f"{low}"
                    else:
                        bit_display = f"{low}..{high}"

                    comment = f"({field['access']})"
                    if field['description']:
                        desc = field['description']
                        if desc.startswith('Field '):
                            desc = desc[6:]
                        if desc and desc != 'Reserved':
                            short_desc = desc[:50]
                            comment += f" {short_desc}"

                    lines.append(f"        uint32_t    {field['name']} :{width:2d}; // bit: {bit_display} {comment}")

                current_bit = high + 1

            if current_bit <= 31:
                reserved_bits = 32 - current_bit
                if reserved_bits == 1:
                    lines.append(
                        f"        uint32_t                  :{reserved_bits:2d}; // bit: {current_bit} Reserved.")
                else:
                    lines.append(
                        f"        uint32_t                  :{reserved_bits:2d}; // bit: {current_bit}..31 Reserved.")

        lines.append(f"    }} b;")
        lines.append(f"    uint32_t  reg;")
        lines.append(f"}} {reg_info['name']}_reg_t;")

        # Пост-обработка для форматирования
        c_code = '\n'.join(lines)

        # 1. Добавляем (R) к Reserved
        c_code = re.sub(r'Reserved\.', '(R) Reserved.', c_code)

        # 2. Убираем пробелы вокруг .. в битах
        c_code = re.sub(r'bit:\s+(\d+)\s*\.\.\s*(\d+)', r'bit: \1..\2', c_code)

        # 3. Выравнивание полей - находим максимальную длину имени
        lines_list = c_code.split('\n')
        formatted_lines = []

        # Сначала найдем все строки с полями внутри struct
        field_lines_indices = []
        for i, line in enumerate(lines_list):
            if 'uint32_t' in line and '// bit:' in line and '} b;' not in line:
                field_lines_indices.append(i)

        if field_lines_indices:
            # Находим максимальную позицию двоеточия
            max_colon_pos = 0
            for idx in field_lines_indices:
                line = lines_list[idx]
                if ':' in line:
                    colon_pos = line.find(':')
                    max_colon_pos = max(max_colon_pos, colon_pos)

            # Выравниваем все строки
            for idx in field_lines_indices:
                line = lines_list[idx]
                if ':' in line:
                    colon_pos = line.find(':')
                    if colon_pos < max_colon_pos:
                        # Добавляем пробелы
                        spaces_to_add = max_colon_pos - colon_pos
                        line = line[:colon_pos] + ' ' * spaces_to_add + line[colon_pos:]
                        lines_list[idx] = line

        c_code = '\n'.join(lines_list)

        return c_code


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