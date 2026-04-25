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
                    if extra > 0:
                        next_reg_match = re.search(r'([a-z0-9_]+)\s+Register\s*\(offset', curr_text, re.IGNORECASE)
                        if next_reg_match and next_reg_match.group(1).lower() != reg_name.lower():
                            print(
                                f"[INFO] Следующий регистр '{next_reg_match.group(1)}' обнаружен на странице {page_num + extra + 1}, останавливаемся")
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
        """Извлекает поля + ПОЛНЫЕ описания (многострочные)"""
        fields = []

        html = page.get_text("html")
        if 'Field Descriptions' not in html:
            return self._extract_from_bitmask(page.get_text(), reg_name)

        start_idx = html.find('Field Descriptions')
        if start_idx == -1:
            return []

        table_html = html[start_idx:start_idx + 30000]
        pattern = r'<p style="top:([\d.]+)pt;left:([\d.]+)pt[^>]*>(.*?)</p>'

        matches = list(re.finditer(pattern, table_html, re.DOTALL))

        rows = {}
        for m in matches:
            y = float(m.group(1))
            x = float(m.group(2))
            content = re.sub(r'<[^>]+>', '', m.group(3)).strip()
            if content:
                if y not in rows:
                    rows[y] = []
                rows[y].append((x, content))

        current_field = None
        desc_lines = []

        for y in sorted(rows.keys()):
            row = sorted(rows[y], key=lambda it: it[0])
            contents = [it[1] for it in row]

            # Продолжение описания предыдущего поля
            if len(contents) <= 2 and current_field and any(x >= 300 for x, _ in row):
                desc_lines.extend(contents)
                continue

            # Новая строка таблицы
            if len(contents) >= 4:
                bits = contents[0].strip()
                name = contents[1].strip()
                access = contents[2].strip()
                reset_val = contents[3].strip()
                desc_start = contents[4].strip() if len(contents) > 4 else ''

                if bits.lower() in ['bit', 'bits'] or name.lower() in ['field']:
                    continue

                # Сохраняем предыдущее поле
                if current_field:
                    current_field['description'] = ' '.join(desc_lines).strip()
                    fields.append(current_field)

                # Валидация битов
                if not re.match(r'^\d+(?:-\d+)?$', bits):
                    continue
                try:
                    if '-' in bits:
                        high, low = map(int, bits.split('-'))
                        if high < low or high > 31 or low < 0: continue
                    else:
                        bit = int(bits)
                        if bit < 0 or bit > 31: continue
                except:
                    continue

                if access == 'W1toCl':
                    access = 'W'
                elif '-' in access:
                    access = access.split('-')[0]
                if access not in ['R', 'W', 'R/W']: access = 'R/W'

                reset_val = re.sub(r'[^0-9a-fA-FhH]', '', reset_val) or '0h'

                current_field = {
                    'bits': bits,
                    'name': name if name.upper() != 'RESERVED' else 'Reserved',
                    'access': access,
                    'reset': reset_val,
                    'description': desc_start
                }
                desc_lines = [desc_start] if desc_start else []

        if current_field:
            current_field['description'] = ' '.join(desc_lines).strip()
            fields.append(current_field)

        return fields

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

    def _refactor_description_format(self, lines: list) -> list:
        """
        Улучшает форматирование сгенерированных строк:
        - Приводит битовое описание к виду 'bit:X' или 'bits:X..Y'
        - Выравнивает уровни доступа (R), (W), (R/W)
        - Сохраняет правильные отступы для строк продолжения
        - Убирает дублирование имён полей в строках продолжения
        """
        import re

        processed = []
        access_max_len = 0
        bit_part_max_len = 0

        # Первый проход: собираем максимальные длины для выравнивания
        for line in lines:
            if '//' not in line:
                continue
            code_part, comment_part = line.split('//', 1)
            comment_part = comment_part.strip()

            # Парсим битовую часть и доступ
            match = re.match(r'(bit|bits)\s*:?\s*(\d+(?:\.\.\d+)?)\s*(\([^)]+\))?\s*(.*)', comment_part)
            if match:
                bit_word, bit_range, access, desc = match.groups()
                bit_word = 'bit' if '..' not in bit_range else 'bits'
                bit_part = f"{bit_word}:{bit_range}"
                access = access if access else ''
                bit_part_max_len = max(bit_part_max_len, len(bit_part))
                if access:
                    access_max_len = max(access_max_len, len(access))

        # Второй проход: переформатируем
        i = 0
        while i < len(lines):
            line = lines[i]

            # Если строка не содержит комментарий или это не строка с битовым полем/продолжением
            if '//' not in line:
                processed.append(line)
                i += 1
                continue

            code_part, comment_part = line.split('//', 1)
            comment_part = comment_part.strip()

            # Проверяем, является ли строка началом описания поля
            match = re.match(r'(bit|bits)\s*:?\s*(\d+(?:\.\.\d+)?)\s*(\([^)]+\))?\s*(.*)', comment_part)

            if match:
                # Это основная строка поля
                bit_word, bit_range, access, desc = match.groups()
                bit_word = 'bit' if '..' not in bit_range else 'bits'
                bit_part = f"{bit_word}:{bit_range}"
                access = access if access else ''
                desc = desc.strip()

                # Формируем выровненную строку
                bit_part_padded = bit_part.ljust(bit_part_max_len)
                access_padded = access.ljust(access_max_len) if access else ''

                # Собираем комментарий
                if access_padded:
                    comment_new = f"{bit_part_padded} {access_padded} {desc}".strip()
                else:
                    comment_new = f"{bit_part_padded} {desc}".strip()

                line = f"{code_part.rstrip()} // {comment_new}"
                processed.append(line)

                # Сохраняем code_part и позицию начала описания для возможных строк продолжения
                base_code_part = code_part.rstrip()
                desc_start_pos = len(base_code_part) + 3 + len(bit_part_padded)  # +3 для " // "
                if access_padded:
                    desc_start_pos += len(access_padded) + 1

                # Проверяем следующие строки на предмет продолжения описания
                i += 1
                while i < len(lines):
                    next_line = lines[i]

                    # Если следующая строка - это продолжение (начинается с пробелов и //)
                    if '//' in next_line:
                        next_code, next_comment = next_line.split('//', 1)
                        next_comment = next_comment.strip()

                        # Проверяем, не началось ли новое поле
                        next_match = re.match(r'(bit|bits)\s*:?\s*(\d+(?:\.\.\d+)?)\s*(\([^)]+\))?', next_comment)
                        if next_match:
                            # Это новое поле, прекращаем обработку продолжений
                            break

                        # Это продолжение описания
                        # Создаём пустой code_part той же длины
                        empty_code = ' ' * len(base_code_part)

                        # Вычисляем отступ до текста описания
                        current_pos = len(empty_code) + 3  # " // "
                        spaces_needed = desc_start_pos - current_pos

                        if spaces_needed > 0:
                            continuation_line = f"{empty_code} // {' ' * spaces_needed}{next_comment}"
                        else:
                            continuation_line = f"{empty_code} // {next_comment}"

                        processed.append(continuation_line)
                        i += 1
                    else:
                        # Строка без комментария - добавляем как есть
                        processed.append(next_line)
                        i += 1
                        break
            else:
                # Это одиночный комментарий или что-то ещё
                processed.append(line)
                i += 1

        return processed

    def generate_c_code(self, reg_info: dict) -> str:
        """Финальная отполированная версия"""
        lines = []

        offset_hex = self._convert_hex_format(reg_info['offset'])
        reset_hex = self._convert_hex_format(reg_info['reset'])

        lines.append(f"/* (offset = {offset_hex}) [reset state = {reset_hex}] */")
        lines.append("typedef union")
        lines.append("{")
        lines.append("    struct")
        lines.append("    {")

        if not reg_info.get('fields'):
            lines.append("        uint32_t                  :32; // bit 0..31 (R) Reserved")
        else:
            def get_low_bit(f):
                high, low = self._parse_bits_range(f['bits'])
                return low

            sorted_fields = sorted(reg_info['fields'], key=get_low_bit)

            # Находим максимальную длину имени поля (оригинальное имя, не uppercase)
            max_name_len = max((len(f['name']) for f in sorted_fields
                                if f['name'].lower() != 'reserved'), default=20)

            current_bit = 0

            # Вычисляем точную позицию начала комментария //
            # Создаем пример строки с максимальной длиной имени
            example_name = 'x' * max_name_len
            example_line = f"        uint32_t    {example_name} : 0; // "
            slash_pos = example_line.find('//')

            # Добавляем комментарий с названием регистра без лишних //
            reg_comment = f"/* Register {reg_info['name']} */"
            # Вычисляем сколько пробелов нужно чтобы выровнять по позиции //
            indent_spaces = ' ' * slash_pos
            lines.append(f"{indent_spaces}{reg_comment}")
            lines.append("")  # пустая строка для читаемости

            for field in sorted_fields:
                high, low = self._parse_bits_range(field['bits'])
                width = high - low + 1

                # Пропущенные reserved
                if current_bit < low:
                    res = low - current_bit
                    prefix = "bit " if res == 1 else "bits"
                    bit_str = str(current_bit) if res == 1 else f"{current_bit}..{low - 1}"
                    lines.append(
                        f"        uint32_t{'':{max_name_len + 4}} :{res:2d}; // {prefix} {bit_str:>6} (R)  Reserved")
                    current_bit = low

                # Сохраняем оригинальное имя поля (не форсируем uppercase)
                name_original = field['name']

                if name_original.lower() == 'reserved':
                    prefix = "bit " if width == 1 else "bits"
                    bit_str = str(low) if width == 1 else f"{low}..{high}"
                    lines.append(
                        f"        uint32_t{'':{max_name_len + 4}} :{width:2d}; // {prefix} {bit_str:>6} (R)  Reserved")
                else:
                    # Биты
                    if low == high:
                        bit_display = f"{low:2d}"
                        bit_prefix = "bit "
                    else:
                        bit_display = f"{low}..{high}"
                        bit_prefix = "bits"

                    # Описание
                    desc = field.get('description', '').strip()
                    if desc.startswith('Field '):
                        desc = desc[6:].strip()

                    if desc:
                        words = desc.split()
                        desc_lines = []
                        cur = []
                        for w in words:
                            if len(' '.join(cur + [w])) > 88:
                                desc_lines.append(' '.join(cur))
                                cur = [w]
                            else:
                                cur.append(w)
                        if cur:
                            desc_lines.append(' '.join(cur))
                    else:
                        desc_lines = [""]

                    # Первая строка с правильным выравниванием
                    first_line = (f"        uint32_t    {name_original:<{max_name_len}} :{width:2d}; "
                                  f"// {bit_prefix}{bit_display} ({field['access']}) {desc_lines[0]}")
                    lines.append(first_line)

                    # Автоматический отступ под //
                    slash_pos = first_line.find('//')
                    if slash_pos != -1:
                        indent = " " * (slash_pos + 0)
                    else:
                        indent = " " * 60

                    for dline in desc_lines[1:]:
                        lines.append(f"{indent}//                  {dline}")

                current_bit = high + 1

            # Последний reserved
            if current_bit <= 31:
                res = 32 - current_bit
                prefix = "bit " if res == 1 else "bits"
                bit_str = str(current_bit) if res == 1 else f"{current_bit}..31"
                lines.append(
                    f"        uint32_t{'':{max_name_len + 4}} :{res:2d}; // {prefix} {bit_str:>6} (R)  Reserved")

        lines.append("    } b;")
        lines.append("    uint32_t reg;")
        lines.append(f"}} {reg_info['name']}_reg_t;")

        # Применяем рефакторинг форматирования
        lines = self._refactor_description_format(lines)

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