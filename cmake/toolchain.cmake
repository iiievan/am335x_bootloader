set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Базовые флаги архитектуры - используем string для объединения
set(ARCH_OPTIONS "-mcpu=cortex-a8 -mtune=cortex-a8 -mfloat-abi=hard -mfpu=neon")

set(COMMON_FLAGS "-mlong-calls -fdata-sections -funsigned-char -ffunction-sections -Wall -Wextra -g -ffreestanding")

# Флаги компиляции
set(CMAKE_C_FLAGS_INIT "${ARCH_OPTIONS} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${ARCH_OPTIONS} ${COMMON_FLAGS} -fno-exceptions -fno-rtti -fno-use-cxa-atexit")
set(CMAKE_ASM_FLAGS_INIT "${ARCH_OPTIONS} -x assembler-with-cpp -g")

# Флаги линковщика
set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nano.specs --specs=nosys.specs")