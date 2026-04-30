## 1. Создайте .venv
```bash
python3 -m venv .venv
```

## 2. Активируйте
```bash
source .venv/bin/activate
```

## 3. Обновите pip (рекомендуется)
```bash
pip install --upgrade pip
```

## 4. Установите зависимости (если есть requirements.txt)
```bash
pip install -r requirements.txt
```

## 5. Или установите часто используемые пакеты вручную
```bash
pip install lxml PyPDF2 pdfplumber beautifulsoup4
```

## 6. Проверьте что установлено
```bash
pip list
````

## 7. Сохраните список зависимостей
```bash
pip freeze > requirements.txt
```

## 8. Проверьте что скрипты работают
```bash
python parse_register.py --help
```