#include "ddr_calibration.hpp"
#include "regs/EMIF.hpp"
#include "rtt/rtt_log.h"
#include "startup/cp15.h"

#define TAG "ddr_calib"

#define TEST_OFFSET         0x00001000

// Тестовые паттерны
static const uint32_t test_patterns[] =
{
    0x00000000, 0xFFFFFFFF,           // все нули и все единицы
    0x55555555, 0xAAAAAAAA,           // шахматная доска
    0x33333333, 0xCCCCCCCC,           // парные биты
    0x0F0F0F0F, 0xF0F0F0F0,           // байтовые паттерны
    0x00FF00FF, 0xFF00FF00,
    0x0000FFFF, 0xFFFF0000,
    0x69969669, 0x96696996            // случайные паттерны
};

static const int num_patterns = sizeof(test_patterns) / sizeof(test_patterns[0]);

// Расширенный тест одного адреса с разными паттернами
static bool test_address(volatile uint32_t* addr, uint32_t pattern)
{
    *addr = pattern;
    cp15_DSB_barrier();
    
    uint32_t readback = *addr;
    if (readback != pattern)
    {
        RTT_LOG_E(TAG, "Pattern mismatch: wrote 0x%08X, read 0x%08X at 0x%p", 
                  (unsigned int)pattern, (unsigned int)readback, addr);
        return false;
    }
    return true;
}

// Тест с walking 1 (проверка каждого бита отдельно)
static bool test_walking_one(volatile uint32_t* addr)
{
    for (int bit = 0; bit < 32; bit++)
    {
        const uint32_t pattern = 1UL << bit;
        if (!test_address(addr, pattern))
            return false;
    }
    return true;
}

// Тест с walking 0
static bool test_walking_zero(volatile uint32_t* addr)
{
    for (int bit = 0; bit < 32; bit++)
    {
        const uint32_t pattern = ~(1UL << bit);

        if (!test_address(addr, pattern))
            return false;
    }
    return true;
}

// Полный тест конкретного адреса
static bool test_address_comprehensive(volatile uint32_t* addr)
{
    // Тест всеми паттернами
    for (unsigned long test_pattern : test_patterns)
    {
        if (!test_address(addr, test_pattern))
            return false;
    }
    
    // Walking 1/0 тесты
    if (!test_walking_one(addr))
        return false;
    if (!test_walking_zero(addr))
        return false;
    
    // Адресный тест (записываем адрес, читаем обратно)
    auto addr_val = reinterpret_cast<uint32_t>(addr);

    if (!test_address(addr, addr_val))
        return false;
    
    return true;
}

// Поиск рабочего диапазона для read DQS
static bool find_read_dqs_range(int data_slice, uint8_t* first_ok, uint8_t* last_ok) {
    using namespace REGS::EMIF;
    auto& phy = *AM335x_DDR23mPHY;
    
    volatile uint32_t* test_addr = reinterpret_cast<uint32_t*>(DDR_START + TEST_OFFSET);
    bool found = false;
    *first_ok = 0;
    *last_ok = 0;
    
    // Диапазон 0x00 - 0x40 (64 значения)
    for (uint8_t ratio = 0; ratio <= 0x40; ratio++) {
        // Устанавливаем ratio
        if (data_slice == 0) {
            phy.DATA0_RD_DQS_SLAVE_RATIO_0.b.RD_DQS_SLAVE_RATIO_CS0 = ratio;
        } else {
            phy.DATA1_RD_DQS_SLAVE_RATIO_0.b.RD_DQS_SLAVE_RATIO_CS0 = ratio;
        }
        cp15_DSB_barrier();
        
        // Даём время на стабилизацию
        for (volatile int i = 0; i < 10; i++) {}

        if (test_address_comprehensive(test_addr))
        {
            if (!found)
            {
                *first_ok = ratio;
                found = true;
            }
            *last_ok = ratio;
        }
        else
        if (found)
            break;

    }
    
    if (found)
    {
        RTT_LOG_I(TAG, "DATA%d RD_DQS: range [0x%02X .. 0x%02X] (width=%d)", 
                  data_slice, *first_ok, *last_ok, *last_ok - *first_ok + 1);
    }
    else
    {
        RTT_LOG_E(TAG, "DATA%d RD_DQS: NO WORKING RATIO FOUND!", data_slice);
    }
    
    return found;
}


static bool find_write_dqs_range(int data_slice, uint8_t* first_ok, uint8_t* last_ok)
{
    using namespace REGS::EMIF;
    auto& phy = *AM335x_DDR23mPHY;
    
    volatile uint32_t* test_addr = reinterpret_cast<uint32_t*>(DDR_START + TEST_OFFSET);
    bool found = false;
    *first_ok = 0;
    *last_ok = 0;
    
    for (uint8_t ratio = 0; ratio <= 0x40; ratio++)
    {
        if (data_slice == 0)
            phy.DATA0_WR_DQS_SLAVE_RATIO_0.b.WR_DQS_SLAVE_RATIO_CS0 = ratio;
        else
            phy.DATA1_WR_DQS_SLAVE_RATIO_0.b.WR_DQS_SLAVE_RATIO_CS0 = ratio;

        cp15_DSB_barrier();
        
        for (volatile int i = 0; i < 10; i++) {}

        if (test_address_comprehensive(test_addr))
        {
            if (!found)
            {
                *first_ok = ratio;
                found = true;
            }
            *last_ok = ratio;
        }
        else
        if (found)
            break;
    }
    
    if (found)
    {
        RTT_LOG_I(TAG, "DATA%d WR_DQS: range [0x%02X .. 0x%02X] (width=%d)", 
                  data_slice, *first_ok, *last_ok, *last_ok - *first_ok + 1);
    }
    else
    {
        RTT_LOG_E(TAG, "DATA%d WR_DQS: NO WORKING RATIO FOUND!", data_slice);
    }
    
    return found;
}

static bool find_write_data_range(int data_slice, uint8_t* first_ok, uint8_t* last_ok)
{
    using namespace REGS::EMIF;
    auto& phy = *AM335x_DDR23mPHY;
    
    volatile uint32_t* test_addr = reinterpret_cast<uint32_t*>(DDR_START + TEST_OFFSET);
    bool found = false;
    *first_ok = 0;
    *last_ok = 0;
    
    for (uint8_t ratio = 0; ratio <= 0x40; ratio++)
    {
        if (data_slice == 0)
            phy.DATA0_WR_DATA_SLAVE_RATIO_0.b.WR_DATA_SLAVE_RATIO_CS0 = ratio;
        else
            phy.DATA1_WR_DATA_SLAVE_RATIO_0.b.WR_DATA_SLAVE_RATIO_CS0 = ratio;

        cp15_DSB_barrier();
        
        for (volatile int i = 0; i < 10; i++) {}

        if (test_address_comprehensive(test_addr))
        {
            if (!found)
            {
                *first_ok = ratio;
                found = true;
            }

            *last_ok = ratio;
        }
        else
        if (found)
            break;
    }
    
    if (found)
    {
        RTT_LOG_I(TAG, "DATA%d WR_DATA: range [0x%02X .. 0x%02X] (width=%d)", 
                  data_slice, *first_ok, *last_ok, *last_ok - *first_ok + 1);
    }
    else
    {
        RTT_LOG_E(TAG, "DATA%d WR_DATA: NO WORKING RATIO FOUND!", data_slice);
    }
    
    return found;
}

// Калибровка командных регистров (обычно не критичны, но проверить стоит)
static void calibrate_command_regs(ddr_calib_values_t* values)
{
    using namespace REGS::EMIF;
    auto& phy = *AM335x_DDR23mPHY;
    
    // Command регистры обычно работают в широком диапазоне
    // Берём стандартное значение из TI Starterware
    values->cmd0_ratio = DDR3_CMD_SLAVE_RATIO;
    values->cmd1_ratio = DDR3_CMD_SLAVE_RATIO;
    values->cmd2_ratio = DDR3_CMD_SLAVE_RATIO;
    
    phy.CMD0_CTRL_SLAVE_RATIO_0.b.CMD_SLAVE_RATIO = values->cmd0_ratio;
    phy.CMD1_CTRL_SLAVE_RATIO_0.b.CMD_SLAVE_RATIO = values->cmd1_ratio;
    phy.CMD2_CTRL_SLAVE_RATIO_0.b.CMD_SLAVE_RATIO = values->cmd2_ratio;
    
    RTT_LOG_I(TAG, "CMD ratios set to 0x%02X (default)", values->cmd0_ratio);
}

// Основная функция калибровки
bool ddr_calibrate(ddr_calib_values_t* values)
{
    using namespace REGS::EMIF;

    if (!values) return false;
    
    RTT_LOG_I(TAG, "=== Starting DDR3 calibration ===");
    
    uint8_t first, last;
    
    // Калибровка READ DQS (самая важная!)
    RTT_LOG_I(TAG, "Calibrating READ DQS...");
    if (!find_read_dqs_range(0, &first, &last)) return false;
    values->rd_dqs0_ratio = (first + last) / 2;
    
    if (!find_read_dqs_range(1, &first, &last)) return false;
    values->rd_dqs1_ratio = (first + last) / 2;

    RTT_LOG_I(TAG, "Calibrating WRITE DQS...");
    if (!find_write_dqs_range(0, &first, &last)) return false;
    values->wr_dqs0_ratio = (first + last) / 2;
    
    if (!find_write_dqs_range(1, &first, &last)) return false;
    values->wr_dqs1_ratio = (first + last) / 2;

    RTT_LOG_I(TAG, "Calibrating WRITE DATA...");
    if (!find_write_data_range(0, &first, &last)) return false;
    values->wr_data0_ratio = (first + last) / 2;
    
    if (!find_write_data_range(1, &first, &last)) return false;
    values->wr_data1_ratio = (first + last) / 2;
    
    // 4. FIFO WE регистры (оставляем дефолтные, они менее критичны)
    values->fifo_we0_ratio = DDR3_DATA0_FIFO_WE_SLAVE_RATIO;  // из Starterware
    values->fifo_we1_ratio = DDR3_DATA0_FIFO_WE_SLAVE_RATIO;

    calibrate_command_regs(values);

    ddr_apply_calibration(values);
    
    RTT_LOG_I(TAG, "=== Calibration complete ===");
    RTT_LOG_I(TAG, "RD_DQS: 0=%02X, 1=%02X", values->rd_dqs0_ratio, values->rd_dqs1_ratio);
    RTT_LOG_I(TAG, "WR_DQS: 0=%02X, 1=%02X", values->wr_dqs0_ratio, values->wr_dqs1_ratio);
    RTT_LOG_I(TAG, "WR_DATA: 0=%02X, 1=%02X", values->wr_data0_ratio, values->wr_data1_ratio);
    
    return true;
}

void ddr_apply_calibration(const ddr_calib_values_t* values)
{
    using namespace REGS::EMIF;
    auto& phy = *AM335x_DDR23mPHY;
    
    phy.CMD0_CTRL_SLAVE_RATIO_0.b.CMD_SLAVE_RATIO = values->cmd0_ratio;
    phy.CMD1_CTRL_SLAVE_RATIO_0.b.CMD_SLAVE_RATIO = values->cmd1_ratio;
    phy.CMD2_CTRL_SLAVE_RATIO_0.b.CMD_SLAVE_RATIO = values->cmd2_ratio;
    
    phy.DATA0_RD_DQS_SLAVE_RATIO_0.b.RD_DQS_SLAVE_RATIO_CS0 = values->rd_dqs0_ratio;
    phy.DATA1_RD_DQS_SLAVE_RATIO_0.b.RD_DQS_SLAVE_RATIO_CS0 = values->rd_dqs1_ratio;
    
    phy.DATA0_WR_DQS_SLAVE_RATIO_0.b.WR_DQS_SLAVE_RATIO_CS0 = values->wr_dqs0_ratio;
    phy.DATA1_WR_DQS_SLAVE_RATIO_0.b.WR_DQS_SLAVE_RATIO_CS0 = values->wr_dqs1_ratio;
    
    phy.DATA0_WR_DATA_SLAVE_RATIO_0.b.WR_DATA_SLAVE_RATIO_CS0 = values->wr_data0_ratio;
    phy.DATA1_WR_DATA_SLAVE_RATIO_0.b.WR_DATA_SLAVE_RATIO_CS0 = values->wr_data1_ratio;
    
    phy.DATA0_FIFO_WE_SLAVE_RATIO_0.b.FIFO_WE_SLAVE_RATIO_CS0 = values->fifo_we0_ratio;
    phy.DATA1_FIFO_WE_SLAVE_RATIO_0.b.FIFO_WE_SLAVE_RATIO_CS0 = values->fifo_we1_ratio;
    
    cp15_DSB_barrier();
}

bool ddr_stress_test(int iterations)
{
    using namespace REGS::EMIF;
    
    volatile uint32_t* base = (uint32_t*)DDR_START;
    const int test_size = 1024 * 1024;  // 1MB для теста
    const int num_words = test_size / 4;
    
    RTT_LOG_I(TAG, "Starting DDR stress test (%d iterations)...", iterations);
    
    for (int iter = 0; iter < iterations; iter++)
    {
        // Тест 1: Запись паттернов во все адреса
        for (int i = 0; i < num_words; i += 64)
        {
            // шаг 64 слова = 256 байт
            uint32_t pattern = test_patterns[iter % num_patterns];
            base[i] = pattern ^ i;  // XOR с адресом для уникальности
        }
        
        cp15_DSB_barrier();
        
        // Тест 2: Проверка
        for (int i = 0; i < num_words; i += 64)
        {
            uint32_t expected = test_patterns[iter % num_patterns] ^ i;

            if (base[i] != expected)
            {
                RTT_LOG_E(TAG, "Stress test failed at 0x%08X: expected 0x%08X, got 0x%08X",
                          (unsigned int)&base[i], (unsigned int)expected, (unsigned int)base[i]);
                return false;
            }
        }
        
        if ((iter + 1) % 10 == 0)
        {
            RTT_LOG_I(TAG, "Stress test iteration %d/%d passed", iter + 1, iterations);
        }
    }
    
    RTT_LOG_I(TAG, "Stress test passed!");
    return true;
}