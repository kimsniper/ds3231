/*
 * Copyright (c) 2022, Mezael Docoy
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MAIN_DS3231_I2C
#define MAIN_DS3231_I2C

#ifdef __cplusplus
extern "C" {
#endif

#include "ds3231_i2c_hal.h" 

/**
 * @brief DS3231 I2C slave address
 */
#define I2C_ADDRESS_DS3231              0x68

/**
 * @brief DS3231 command code registers
 */
#define REG_SECONDS                     0x00
#define REG_MINUTES                     0x01
#define REG_HOURS                       0x02
#define REG_DAY                         0x03
#define REG_DATE                        0x04
#define REG_MONTH_CENTURY               0x05
#define REG_YEAR                        0x06
#define REG_ALARM1_SECONDS              0x07
#define REG_ALARM1_MINUTES              0x08
#define REG_ALARM1_HOURS                0x09
#define REG_ALARM1_DAY_DATE             0x0A
#define REG_ALARM2_MINUTES              0x0B
#define REG_ALARM2_HOURS                0x0C
#define REG_ALARM2_DAY_DATE             0x0D
#define REG_CONTROL                     0x0E
#define REG_CONTROL_STATUS              0x0F
#define REG_AGING_OFFSET                0x10
#define REG_MSB_OF_TEMP                 0x11
#define REG_LSB_OF_TEMP                 0x12

/**
 * @brief Other DS3231 macros
 */
#define TRUE                            0x01
#define FALSE                           0x00
#define ENABLE                          TRUE
#define DISABLE                         FALSE

/**
 * @brief Control Status bit shift macros
 */
#define ALARM1_FLAG                     (1 << 0)
#define ALARM2_FLAG                     (1 << 1)
#define DEV_BUSY_FLAG                   (1 << 2)
#define DEV_32KHZ_EN_FLAG               (1 << 3)
#define DEV_OSC_STOP_FLAG               (1 << 7)

typedef enum{
    FORMAT_24HR = 0x00,
    FORMAT_12HR = 0x01,
} ds3231_clock_format_t;

typedef enum{
    CLOCK_PERIOD_AM = 0x00,
    CLOCK_PERIOD_PM = 0x01,
} ds3231_clock_ampm_t;

typedef enum{
    ALARM1_SEC = 0x0F,
    ALARM1_SEC_MATCH = 0x0E,
    ALARM1_MIN_SEC_MATCH = 0x0C,
    ALARM1_HR_MIN_SEC_MATCH = 0x08,
    ALARM1_DT_HR_MIN_SEC_MATCH = 0x00,
    ALARM1_DY_HR_MIN_SEC_MATCH = 0x10,
} ds3231_alarm1_t;

typedef enum{
    ALARM1_MIN = 0x07,
    ALARM1_MIN_MATCH = 0x06,
    ALARM1_HR_MIN_MATCH = 0x04,
    ALARM1_DT_HR_MIN_MATCH = 0x00,
    ALARM1_DY_HR_MIN_MATCH = 0x08,
} ds3231_alarm2_t;

typedef enum{
    RATE_SELECT_1HZ = 0x00,
    RATE_SELECT_1024HZ = 0x01,
    RATE_SELECT_4096HZ = 0x02,
    RATE_SELECT_8192HZ = 0x03,
} ds3231_ratesel_t;

typedef struct{
    uint8_t hr;
    uint8_t sec;  
    uint8_t min; 
    ds3231_clock_ampm_t am_pm; 
} ds3231_rtcc_clock_t;

typedef struct{
    uint8_t mon;
    uint8_t day;  
    uint8_t date;
    uint16_t year; 
    uint8_t century; 
} ds3231_rtcc_calendar_t;

typedef struct{
    ds3231_clock_format_t clock_format;
    ds3231_alarm1_t alarm1_set;   
    ds3231_alarm2_t alarm2_set;
    uint8_t alarm1_en;
    uint8_t alarm2_en;
    ds3231_ratesel_t rate_select;
} ds3231_rtcc_cfg_t;

/**
 * @brief Read status flag in control register status
 */
int16_t ds3231_i2c_control_status(uint8_t flag);

/**
 * @brief Set status flag in control register status
 */
int16_t ds3231_i2c_set_control_status(uint8_t flag);

/**
 * @brief Set alarm 1
 */
int16_t ds3231_i2c_set_alarm1(ds3231_alarm1_t setting);

/**
 * @brief Set alarm 2
 */
int16_t ds3231_i2c_set_alarm2(ds3231_alarm2_t setting);

/**
 * @brief Set clock format
 */
int16_t ds3231_i2c_set_clock_format(ds3231_clock_format_t setting);

/**
 * @brief Start/Stop oscillator
 */
int16_t ds3231_i2c_osc_en(uint8_t status);

/**
 * @brief Read clock data
 */
int16_t ds3231_i2c_read_clock(ds3231_rtcc_cfg_t cfg, ds3231_rtcc_clock_t *dt);

/**
 * @brief Set clock data
 */
int16_t ds3231_i2c_set_clock(ds3231_rtcc_cfg_t cfg, ds3231_rtcc_clock_t dt);

/**
 * @brief Read calendar data
 */
int16_t ds3231_i2c_read_calendar(ds3231_rtcc_calendar_t *dt);

/**
 * @brief Set calendar data
 */
int16_t ds3231_i2c_set_calendar(ds3231_rtcc_calendar_t dt);

/**
 * @brief Device config
 */
int16_t ds3231_i2c_dev_config(ds3231_rtcc_cfg_t cfg);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_DS3231_I2C */
