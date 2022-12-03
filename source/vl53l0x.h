/**
 * @brief
 * @cite    Niklas Nilsson
 * @link    https://github.com/artfulbytes/vl6180x_vl53l0x_msp430.git
 */
#ifndef VL53L0X_H
#define VL53L0X_H

#include <stdbool.h>
#include <stdint.h>

#define VL53L0X_OUT_OF_RANGE (8190)

/* Comment these out if not connected */
#define VL53L0X_SECOND 0

#define VL53L0X_DEVICEMODE_SINGLE_RANGING (0)
#define VL53L0X_DEVICEMODE_CONTINUOUS_RANGING (1)
#define VL53L0X_REG_SYSRANGE_START (0x000)
#define VL53L0X_ERROR_NONE (1)

typedef enum
{
    VL53L0X_IDX_FIRST,
#if VL53L0X_SECOND
    VL53L0X_IDX_SECOND
#endif
} vl53l0x_idx_t;

/**
 * Initializes the sensors in the vl53l0x_idx_t enum.
 * @note Each sensor must have its XSHUT pin connected.
 */
bool vl53l0x_init(void);

/**
 * Does a single range measurement
 * @param idx selects specific sensor
 * @param range contains the measured range or VL53L0X_OUT_OF_RANGE
 *        if out of range.
 * @return True if success, False if error
 * @note   Polling-based
 */
bool vl53l0x_read_range_single(vl53l0x_idx_t idx, uint16_t *range);

bool vl53l0x_start_range_continuous(vl53l0x_idx_t idx, uint32_t InterMeasurementPeriodMilliSeconds);

bool vl53l0x_is_ranging_complete(vl53l0x_idx_t idx);

#endif /* VL53L0X_H */
