#!/usr/bin/env python3
"""
ДИАГНОСТИКА СТРАНИЦЫ am335x_datasheet.PDF
необходим пакет:
pip install pdfplumber

для запуска:
python3 diagnose.py am3359_datasheet.pdf 27 > page27_dump.txt
"""

import sys
import pdfplumber


def diagnose_pdf_page(pdf_path: str, page_num: int):
    print(f"=== ДИАГНОСТИКА СТРАНИЦЫ {page_num} ===\n")

    with pdfplumber.open(pdf_path) as pdf:
        if page_num > len(pdf.pages):
            print(f"Ошибка: страница {page_num} не существует")
            return

        page = pdf.pages[page_num - 1]

        # Извлекаем текст
        text = page.extract_text()

        print("=== ИЗВЛЕЧЕННЫЙ ТЕКСТ ===\n")
        lines = text.split('\n')
        for i, line in enumerate(lines[:200]):  # Первые 200 строк
            print(f"{i:3d}: {line}")

        print("\n=== ТАБЛИЦЫ ===\n")
        tables = page.extract_tables()
        for ti, table in enumerate(tables):
            print(f"Таблица {ti}: {len(table)} строк")
            for ri, row in enumerate(table[:10]):  # Первые 10 строк
                print(f"  Строка {ri}: {row}")

        print("\n=== СЛОВА С КООРДИНАТАМИ ===\n")
        words = page.extract_words()
        for word in words[:50]:  # Первые 50 слов
            if 'GPIO' in word['text'].upper() or 'GPMC' in word['text'].upper():
                print(f"  '{word['text']}' at x={word['x0']:.1f}, y={word['top']:.1f}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Использование: python3 diagnose.py <pdf_file> <page_num>")
        sys.exit(1)

    diagnose_pdf_page(sys.argv[1], int(sys.argv[2]))