#!/usr/bin/env python3
"""
Диагностика структуры PDF - расширенная версия
Показывает полное HTML-представление страницы для анализа таблиц
Установка: pip install PyMuPDF
# Для просмотра HTML с таблицей Field Descriptions
python diagnose.py spruh73q.pdf 1504

# Для анализа всех таблиц на странице
python diagnose.py --tables spruh73q.pdf 1504
"""

import sys
import fitz


def diagnose_page(pdf_path: str, page_num: int):
    """Показывает сырой текст и HTML страницы для анализа"""
    doc = fitz.open(pdf_path)
    page = doc[page_num - 1]  # fitz нумерует с 0

    print(f"\n{'=' * 80}")
    print(f"ДИАГНОСТИКА СТРАНИЦЫ {page_num}")
    print(f"{'=' * 80}\n")

    # Получаем текст
    text = page.get_text()

    # Ищем регистр
    lines = text.split('\n')

    # Показываем 100 строк после регистра
    found = False
    for i, line in enumerate(lines):
        if 'mpuss_hw_debug_sel' in line.lower() and 'register' in line.lower():
            found = True
            print(f"[FOUND] Строка {i}: {line}\n")
            print("Следующие 100 строк:\n")
            for j in range(i, min(i + 100, len(lines))):
                print(f"{j:4d}: {lines[j]}")
            break

    if not found:
        # Ищем любой регистр
        for i, line in enumerate(lines):
            if 'register' in line.lower() and 'offset' in line.lower():
                found = True
                print(f"[FOUND] Регистр в строке {i}: {line}\n")
                print("Следующие 100 строк:\n")
                for j in range(i, min(i + 100, len(lines))):
                    print(f"{j:4d}: {lines[j]}")
                break

    if not found:
        print("Регистр не найден на этой странице")
        print("\nПервые 100 строк страницы:\n")
        for j in range(min(100, len(lines))):
            print(f"{j:4d}: {lines[j]}")

    # Показываем полное HTML-представление (без ограничения)
    print(f"\n{'=' * 80}")
    print("ПОЛНОЕ HTML ПРЕДСТАВЛЕНИЕ")
    print(f"{'=' * 80}\n")
    html = page.get_text("html")

    # Ищем секцию с таблицей Field Descriptions
    if 'Field Descriptions' in html:
        start_idx = html.find('Field Descriptions')
        # Показываем 10000 символов начиная с Field Descriptions
        html_snippet = html[start_idx:start_idx + 10000]
        print(html_snippet)
    else:
        # Если не нашли Field Descriptions, показываем последние 10000 символов
        print(html[-10000:])

    # Также показываем сырой текст между Figure и следующим регистром
    print(f"\n{'=' * 80}")
    print("ТЕКСТ МЕЖДУ FIGURE И СЛЕДУЮЩИМ РЕГИСТРОМ")
    print(f"{'=' * 80}\n")

    # Ищем позицию Figure
    for i, line in enumerate(lines):
        if 'Figure' in line and ('register' in line.lower() or 'cqdetect' in line):
            print(f"\nНайдено Figure в строке {i}:")
            for j in range(i, min(i + 80, len(lines))):
                print(f"{j:4d}: {lines[j]}")
            break

    doc.close()


def diagnose_all_tables(pdf_path: str, page_num: int):
    """Диагностирует все таблицы на странице"""
    doc = fitz.open(pdf_path)
    page = doc[page_num - 1]

    print(f"\n{'=' * 80}")
    print(f"ДИАГНОСТИКА ТАБЛИЦ НА СТРАНИЦЕ {page_num}")
    print(f"{'=' * 80}\n")

    # Получаем HTML
    html = page.get_text("html")

    # Ищем все таблицы
    import re
    tables = re.findall(r'<\s*table[^>]*>(.*?)<\s*/\s*table', html, re.IGNORECASE | re.DOTALL)

    print(f"Найдено таблиц: {len(tables)}\n")

    for idx, table in enumerate(tables):
        print(f"\n--- ТАБЛИЦА {idx + 1} ---")
        # Очищаем от лишних пробелов
        table_clean = re.sub(r'\s+', ' ', table)
        # Показываем первые 500 символов
        print(table_clean[:500])
        print("...")

        # Ищем строки с битовыми полями
        rows = re.findall(r'<\s*tr[^>]*>(.*?)<\s*/\s*tr', table, re.IGNORECASE | re.DOTALL)
        for row in rows[:10]:  # Первые 10 строк
            cells = re.findall(r'<\s*td[^>]*>(.*?)<\s*/\s*td', row, re.IGNORECASE | re.DOTALL)
            if len(cells) >= 4:
                print(f"  Ячейки: {len(cells)}")
                for c, cell in enumerate(cells[:5]):
                    cell_clean = re.sub(r'<[^>]+>', '', cell).strip()
                    print(f"    [{c}]: {cell_clean[:50]}")

    doc.close()


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Использование:")
        print("  python diagnose.py <pdf_file> <page_number>")
        print("  python diagnose.py --tables <pdf_file> <page_number>  # анализ таблиц")
        print("\nПримеры:")
        print("  python diagnose.py spruh73q.pdf 1504")
        print("  python diagnose.py --tables spruh73q.pdf 1504")
        sys.exit(1)

    if sys.argv[1] == '--tables':
        if len(sys.argv) != 4:
            print("Ошибка: нужно указать PDF файл и номер страницы")
            sys.exit(1)
        diagnose_all_tables(sys.argv[2], int(sys.argv[3]))
    else:
        diagnose_page(sys.argv[1], int(sys.argv[2]))