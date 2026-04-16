#ifndef __DDR_CALIBRATION_HPP
#define __DDR_CALIBRATION_HPP

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    uint8_t cmd0_ratio;
    uint8_t cmd1_ratio;
    uint8_t cmd2_ratio;
    uint8_t rd_dqs0_ratio;
    uint8_t rd_dqs1_ratio;
    uint8_t wr_dqs0_ratio;
    uint8_t wr_dqs1_ratio;
    uint8_t wr_data0_ratio;
    uint8_t wr_data1_ratio;
    uint8_t fifo_we0_ratio;
    uint8_t fifo_we1_ratio;
} ddr_calib_values_t;


bool ddr_calibrate(ddr_calib_values_t* values);

bool ddr_stress_test(int iterations);

void ddr_apply_calibration(const ddr_calib_values_t* values);

#ifdef __cplusplus
}
#endif

#endif //__DDR_CALIBRATION_HPP
