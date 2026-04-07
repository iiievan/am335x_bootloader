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

set(ARCH_BASE_FLAGS "-mcpu=cortex-a8 -mtune=cortex-a8 -mfloat-abi=hard -mfpu=neon")

set(CMAKE_C_FLAGS_INIT "${ARCH_BASE_FLAGS} -mlong-calls -fdata-sections -funsigned-char -ffunction-sections -Wall -Wextra -g -ffreestanding")
set(CMAKE_CXX_FLAGS_INIT "${ARCH_BASE_FLAGS} -mlong-calls -fdata-sections -funsigned-char -ffunction-sections -Wall -Wextra -g -ffreestanding -fno-exceptions -fno-rtti -fno-use-cxa-atexit")
set(CMAKE_ASM_FLAGS_INIT "${ARCH_BASE_FLAGS} -x assembler-with-cpp -g")

# Флаги линковщика - здесь указываем specs
set(CMAKE_EXE_LINKER_FLAGS_INIT "--specs=nano.specs --specs=nosys.specs")
