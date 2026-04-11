# Генератор SVD файлов из C++ заголовков для AM335x

Этот скрипт преобразует C++ заголовочные файлы с описанием регистров периферии (в стиле `REGS.hpp`) в формат CMSIS-SVD для использования в отладчиках (Segger Ozone, Keil MDK, IAR и др.).

## Содержание
- [Требования](#требования)
- [Быстрый старт](#быстрый-старт)
- [Настройка PERIPHERAL_CONFIG](#настройка-peripheral_config)
- [Настройка groupName](#настройка-groupname)
- [Примеры](#примеры)
- [Устранение проблем](#устранение-проблем)
- [Дополнительные возможности](#дополнительные-возможности)

## Требования

- Python 3.6 или выше
- Заголовочный файл `.hpp` с описанием регистров в определённом формате

## Быстрый старт

1. Поместите скрипт в одну папку с вашим `.hpp` файлом
2. Настройте секцию `PERIPHERAL_CONFIG` под ваш файл
3. Настройте логику `groupName` если нужно
4. Установить пакет python-is-python3(для Ubuntu/Debian)
```bash
sudo apt update
sudo apt install python-is-python3
```
и можно запускать командой:
```bash
python hpp_to_svd.py ваш_файл.hpp
```
если не охота ставить python-is-python3 то можно и так:
```bash
python3 hpp_to_svd.py ваш_файл.hpp
```
Или добавьте в начало скрипта hpp_to_svd.py первую строку:
```python
#!/usr/bin/env python3

import re
import sys
# ... остальной код
```
   Затем сделайте скрипт исполняемым:
```bash
chmod +x hpp_to_svd.py
```
Теперь можно запускать напрямую::
```bash
./hpp_to_svd.py ваш_файл.hpp
```
5. Полученный .svd файл загрузите в Ozone через .jdebug фаил
```
Project.AddSvdFile("Cortex-A8.svd");    // <- this line first
Project.AddSvdFile ("ваш_файл.svd");    // <- this line second
```

# Настройка PERIPHERAL_CONFIG
## Структура записи в конфиге
```python
PERIPHERAL_CONFIG = {
    'ИМЯ_В_SVD': {
        'struct_pattern': 'ИМЯ_СТРУКТУРЫ_В_HPP',  # обязательно
        'base_address': '0xXXXXXXXX',             # опционально (если не найден автоматически)
        'description': 'Описание периферии'       # опционально
    },
}
```
## Как найти нужные значения в вашем .hpp файле
### 1. Ищем структуры периферии
   В файле найдите объявления структур вида:
```c++
struct AM335x_EMIF4D_Type
{
    // ... регистры ...
};
```
или 
```c++
struct AM335x_CM_PER_Type
{
    // ... регистры ...
};
```
struct_pattern = точное имя структуры, например "AM335x_CM_PER_Type"

### 2. Ищем базовый адрес
   Найдите строки вида:
```c++
constexpr uint32_t AM335x_EMIF0_BASE = 0x4C000000;
constexpr uint32_t AM335x_CM_PER_BASE = AM335x_PRCM_BASE;  // = 0x44E00000
```
или в inline-указателях:
```c++
inline AM335x_CM_PER_Type *AM335x_CM_PER = 
    reinterpret_cast<AM335x_CM_PER_Type*>(AM335x_CM_PER_BASE);
//                                        ^^^^^^^^^^^^^^^^^^^
//                                        здесь базовый адрес
```
base_address = полный шестнадцатеричный адрес, например "0x44E00000"

### 3. Выбираем имя периферии в SVD
   ИМЯ_В_SVD - как модуль будет называться в отладчике. Рекомендуется использовать краткие имена:

- "EMIF0" вместо "AM335x_EMIF4D"

- "CM_PER" вместо "AM335x_CM_PER"

- "PRM_IRQ" вместо "AM335x_PRM_IRQ"

## Пример конфигурации для EMIF.hpp
```python
PERIPHERAL_CONFIG = {
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
}
```
## Пример конфигурации для PRCM.hpp
```python
PERIPHERAL_CONFIG = {
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
}
```

# Настройка groupName
SVD поддерживает группировку периферии для удобной навигации в отладчике.   
Настройка находится в функции generate_svd():
```python
# Определяем groupName на основе имени
if 'EMIF' in p_name or 'DDR' in p_name:
    SubElement(periph_elem, 'groupName').text = 'Memory'
elif 'CM_' in p_name:
    SubElement(periph_elem, 'groupName').text = 'Clock Modules'
elif 'PRM_' in p_name:
    SubElement(periph_elem, 'groupName').text = 'Power Reset Modules'
else:
    SubElement(periph_elem, 'groupName').text = 'Peripherals'
```

## Как добавить новую группу
Допустим, у вас есть периферия с именами GPIO0, GPIO1, UART0 и т.д. Добавьте соответствующие условия:
```python
if 'EMIF' in p_name or 'DDR' in p_name:
    SubElement(periph_elem, 'groupName').text = 'Memory'
elif 'CM_' in p_name:
    SubElement(periph_elem, 'groupName').text = 'Clock Modules'
elif 'PRM_' in p_name:
    SubElement(periph_elem, 'groupName').text = 'Power Reset Modules'
elif 'GPIO' in p_name:
    SubElement(periph_elem, 'groupName').text = 'GPIO'
elif 'UART' in p_name:
    SubElement(periph_elem, 'groupName').text = 'Serial'
elif 'I2C' in p_name or 'SPI' in p_name:
    SubElement(periph_elem, 'groupName').text = 'Communication'
else:
    SubElement(periph_elem, 'groupName').text = 'Other Peripherals'
```

## Стандартные группы в SVD
Рекомендуемые имена групп (будут отображаться в дереве периферии):

- **Memory** - контроллеры памяти
- **Clock Modules** - модули тактирования
- **Power Reset Modules** - модули питания и сброса
- **GPIO** - порты ввода-вывода
- **Serial** - последовательные интерфейсы
- **Communication** - коммуникационные интерфейсы
- **Timers** - таймеры
- **ADC** - аналого-цифровые преобразователи
- **System** - системные модули
- **Peripherals** - общая категория

#  Примеры
##  Пример 1: Создание SVD для EMIF
```python
# 1. Настройте PERIPHERAL_CONFIG
PERIPHERAL_CONFIG = {
    'EMIF0': {
        'struct_pattern': 'AM335x_EMIF4D_Type',
        'base_address': '0x4C000000',
        'description': 'External Memory Interface 4D (EMIF)'
    },
    'DDR23mPHY': {
        'struct_pattern': 'AM335x_DDR23mPHY_Type',
        'base_address': '0x44E12000',
        'description': 'DDR PHY Control Registers'
    },
}

# 2. Запустите
python hpp_to_svd.py EMIF.hpp

# 3. Результат: EMIF.svd
```
## Пример 2: Создание SVD для PRCM
```python
# 1. Настройте PERIPHERAL_CONFIG (все 16 модулей как показано выше)

# 2. Запустите
python hpp_to_svd.py PRCM.hpp

# 3. Результат: PRCM.svd с группами Clock Modules и Power Reset Modules
```

## Пример 3: Создание универсального конфига для всех периферий
Можно создать один скрипт с конфигурацией для всех периферийных модулей:
```python
PERIPHERAL_CONFIG = {
    # EMIF
    'EMIF0': {'struct_pattern': 'AM335x_EMIF4D_Type', 'base_address': '0x4C000000'},
    'DDR23mPHY': {'struct_pattern': 'AM335x_DDR23mPHY_Type', 'base_address': '0x44E12000'},
    
    # PRCM - Clock Modules
    'CM_PER': {'struct_pattern': 'AM335x_CM_PER_Type', 'base_address': '0x44E00000'},
    'CM_WKUP': {'struct_pattern': 'AM335x_CM_WKUP_Type', 'base_address': '0x44E00400'},
    # ... остальные CM_
    
    # PRCM - Power Reset Modules
    'PRM_IRQ': {'struct_pattern': 'AM335x_PRM_IRQ_Type', 'base_address': '0x44E00B00'},
    # ... остальные PRM_
    
    # GPIO
    'GPIO0': {'struct_pattern': 'AM335x_GPIO_Type', 'base_address': '0x44E07000'},
    'GPIO1': {'struct_pattern': 'AM335x_GPIO_Type', 'base_address': '0x4804C000'},
    # ... остальные GPIO
}

# И добавьте соответствующие groupName
```

# Устранение проблем
### Проблема: "Не найден базовый адрес для XXX"
**Решение 1:** Укажите адрес явно в PERIPHERAL_CONFIG  
**Решение 2:** Проверьте, есть ли в .hpp файле constexpr с адресом:
```c++
constexpr uint32_t AM335x_CM_PER_BASE = 0x44E00000;
```

### Проблема: "Тип регистра XXX не найден"
Это означает, что регистр используется в структуре периферии, но его определение (typedef union { ... } XXX_reg_t;) не найдено. Проверьте:
- Правильность имени типа регистра
- Все ли заголовочные файлы включены

### Проблема: Выходной SVD пустой или содержит мало периферии
Установите PARSE_ALL_STRUCTURES = True чтобы найти все структуры, даже не указанные в конфиге.

### Проблема: Поля регистров не отображаются в Ozone
Проверьте:
- SVD файл содержит секции <fields>
- Ozone показывает регистры в режиме отладки 
- Базовый адрес периферии корректен

# Дополнительные возможности
### Автоматический парсинг всех структур
Установите **PARSE_ALL_STRUCTURES** = True чтобы скрипт автоматически находил и добавлял все структуры вида AM335x_*_Type, даже если их нет в **PERIPHERAL_CONFIG**. Базовые адреса будут найдены автоматически если есть соответствующие constexpr.

### Ручное управление парсингом
Если **PARSE_ALL_STRUCTURES** = False, скрипт будет обрабатывать только те структуры, которые явно указаны в **PERIPHERAL_CONFIG**. Это полезно когда нужно создать SVD только для определённых модулей.

### Структура ожидаемого .hpp файла
Скрипт ожидает следующий формат:
```c++
// 1. Определение типа регистра
/* [reset state = 0xXXXXXXXX] [offset = 0xXXXX] */
typedef union 
{
    struct 
    {                                         
        uint32_t    FIELD_NAME  : WIDTH;     // bit: X..Y (RW) Description
        uint32_t                : WIDTH2;    // bit: X..Y (R)  Reserved             
    } b;
    uint32_t  reg;
} REG_NAME_reg_t;

// 2. Структура периферии
struct AM335x_MODULE_Type
{
    __R  REG_NAME_reg_t  REG_NAME;  // (0x00)
    __RW OTHER_REG_reg_t OTHER_REG; // (0x04)
    // ...
};

// 3. Базовый адрес (опционально)
constexpr uint32_t AM335x_MODULE_BASE = 0xXXXXXXXX;
```