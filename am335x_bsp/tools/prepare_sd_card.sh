#!/bin/bash
# setup_sd_card.sh - Создание двух разделов для BeagleBone Black
# Первый раздел: 128MB FAT32 (BOOT) для MLO
# Второй раздел: остальное пространство ext4 (rootfs)

set -e

# Цвета
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}BeagleBone Black SD Card Setup${NC}"
echo -e "${BLUE}Partition scheme: 128MB FAT32 + ext4${NC}"
echo -e "${BLUE}========================================${NC}"

# Проверка прав
if [ "$EUID" -ne 0 ]; then
    echo -e "${RED}Запустите с sudo: sudo $0${NC}"
    exit 1
fi

# Показываем устройства
echo -e "${YELLOW}Доступные устройства:${NC}"
lsblk -o NAME,SIZE,MODEL,MOUNTPOINT | grep -E "^(sd|mmcblk)"
echo ""

echo -e "${YELLOW}Введите устройство SD-карты (например, sdb, mmcblk0):${NC}"
read -p "Устройство: " DEVICE

DEVICE_PATH="/dev/$DEVICE"

if [ ! -b "$DEVICE_PATH" ]; then
    echo -e "${RED}Ошибка: $DEVICE_PATH не существует!${NC}"
    exit 1
fi

# Предупреждение
echo -e "${RED}⚠️  ВНИМАНИЕ! Все данные на ${DEVICE_PATH} будут УНИЧТОЖЕНЫ!${NC}"
read -p "Введите 'YES' для продолжения: " CONFIRM
if [ "$CONFIRM" != "YES" ]; then
    echo -e "${YELLOW}Операция отменена.${NC}"
    exit 0
fi

# Определяем имена разделов
if [[ $DEVICE == mmcblk* ]]; then
    PART1="${DEVICE_PATH}p1"
    PART2="${DEVICE_PATH}p2"
else
    PART1="${DEVICE_PATH}1"
    PART2="${DEVICE_PATH}2"
fi

# Размонтируем все разделы
echo -e "${GREEN}Размонтирование разделов...${NC}"
for part in $(ls ${DEVICE_PATH}* 2>/dev/null | grep -E "${DEVICE}[0-9]+"); do
    umount -f $part 2>/dev/null || true
done

# Стираем начало карты (16MB)
echo -e "${GREEN}Стирание загрузочной области (16MB)...${NC}"
dd if=/dev/zero of=$DEVICE_PATH bs=1M count=16 status=progress

# Создаём разделы через fdisk (автоматически)
echo -e "${GREEN}Создание разделов...${NC}"

# Удаляем существующую таблицу разделов и создаём новую
(
echo o                    # Создать новую MBR (DOS)
echo n                    # Новый раздел
echo p                    # Primary
echo 1                    # Номер 1
echo 2048                 # Начальный сектор (оставляем место для загрузчика)
echo +128M                # Размер 128MB
echo t                    # Изменить тип
echo b                    # W95 FAT32 (b) вместо e (FAT16)
echo n                    # Новый раздел
echo p                    # Primary
echo 2                    # Номер 2
echo                      # Начало (по умолчанию, следующий сектор)
echo                      # Конец (весь остаток диска)
echo t                    # Изменить тип второго раздела
echo 2                    # Номер раздела 2
echo 83                   # Тип 83 (Linux)
echo a                    # Сделать первый раздел загрузочным
echo 1                    # Номер раздела 1
echo w                    # Записать изменения
) | fdisk $DEVICE_PATH

# Ждём обновления разделов
sleep 2
partprobe $DEVICE_PATH 2>/dev/null || true

# Форматируем разделы
echo -e "${GREEN}Форматирование FAT32 (BOOT)...${NC}"
mkfs.vfat -F 32 -S 512 -n "BOOT" $PART1

echo -e "${GREEN}Форматирование ext4 (rootfs)...${NC}"
mkfs.ext4 -L "rootfs" -E nodiscard $PART2

# Создаём точку монтирования
MOUNT_BOOT="/mnt/bbb_boot"
MOUNT_ROOT="/mnt/bbb_root"
mkdir -p $MOUNT_BOOT $MOUNT_ROOT

# Монтируем
mount $PART1 $MOUNT_BOOT
mount $PART2 $MOUNT_ROOT

# Создаём информационные файлы
cat > $MOUNT_BOOT/README.txt << EOF
BeagleBone Black Boot Partition (FAT32)
========================================
Copy MLO file here to boot from SD card.

Created: $(date)
EOF

cat > $MOUNT_ROOT/README.txt << EOF
BeagleBone Black RootFS Partition (ext4)
========================================
This partition is for root filesystem if you run Linux.
For baremetal, you can ignore this partition.

Created: $(date)
EOF

# Проверяем размеры
BOOT_SIZE=$(df -h $MOUNT_BOOT | tail -1 | awk '{print $2}')
ROOT_SIZE=$(df -h $MOUNT_ROOT | tail -1 | awk '{print $2}')

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}✅ SD-карта успешно подготовлена!${NC}"
echo -e "${GREEN}========================================${NC}"
echo -e "Устройство: ${YELLOW}$DEVICE_PATH${NC}"
echo -e "Разделы:"
echo -e "  ${GREEN}1. BOOT (FAT32)${NC} - $MOUNT_BOOT ($BOOT_SIZE)"
echo -e "  ${GREEN}2. rootfs (ext4)${NC} - $MOUNT_ROOT ($ROOT_SIZE)"
echo ""

# Копируем MLO
if [ -f "cmake-build-release/MLO" ]; then
    echo -e "${BLUE}Найден MLO в cmake-build-release/${NC}"
    read -p "Скопировать MLO на BOOT раздел? (y/n): " COPY_MLO
    if [ "$COPY_MLO" = "y" ] || [ "$COPY_MLO" = "Y" ]; then
        cp cmake-build-release/MLO $MOUNT_BOOT/
        sync
        echo -e "${GREEN}✅ MLO скопирован!${NC}"
    fi
else
    echo -e "${RED}MLO не найден в cmake-build-release/${NC}"
    echo "Сначала соберите проект: cmake --build cmake-build-release --target GenerateMLO"
fi

# Размонтируем
echo ""
read -p "Размонтировать карту? (y/n): " UNMOUNT
if [ "$UNMOUNT" = "y" ] || [ "$UNMOUNT" = "Y" ]; then
    umount $MOUNT_BOOT
    umount $MOUNT_ROOT
    rmdir $MOUNT_BOOT $MOUNT_ROOT
    echo -e "${GREEN}✅ Карта размонтирована. Можно извлекать!${NC}"
fi

echo -e "${BLUE}========================================${NC}"
echo -e "${GREEN}Готово! Вставьте SD-карту в BeagleBone Black и включите питание.${NC}"