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

#include "ds3231_i2c.h"
#include "ds3231_i2c_hal.h" 

#include "stdio.h"

static uint8_t bcd_to_dec(uint8_t val)
{
    return ((val >> 4) * 10) + (val & 0x0F);
}

static uint8_t dec_to_bcd(uint8_t val)
{
    return (((val-(val%10))/10) << 4) | (val%10);
}

int16_t ds3231_i2c_read_control_status(uint8_t flag)
{
    uint8_t reg = REG_CONTROL_STATUS;
    uint8_t data;
    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, &data, 1);

    if(err != DS3231_OK) 
        return err;

    return (data & ~(flag)) ? TRUE : FALSE;
}

int16_t ds3231_i2c_set_control_status(uint8_t flag)
{
    uint8_t reg = REG_CONTROL_STATUS;
    uint8_t data;
    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, &data, 1);

    if(err != DS3231_OK) 
        return err;

    data &= ~(flag);

    err = ds3231_i2c_hal_write(I2C_ADDRESS_DS3231, &data, 2);

    return err;
}

int16_t ds3231_i2c_set_alarm1(ds3231_alarm1_t setting)
{
    uint8_t reg = REG_ALARM1_SECONDS;
    uint8_t data_read[4];
    uint8_t data_write[5];
    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, data_read, 4);

    if(err != DS3231_OK) 
        return err;

    data_write[0] = reg;
    for(uint8_t i=0; i<3;i++)
    {
        data_write[i+1] = (setting & ~(1 << i)) ? data_read[i] | (1 << 7) : data_read[i] & ~(1 << 7);
    }
    data_write[4] = (setting & ~(1 << 4)) ? data_read[3] | (1 << 6) : data_read[3] & ~(1 << 6);

    err = ds3231_i2c_hal_write(I2C_ADDRESS_DS3231, data_write, 5);

    return err;
}

int16_t ds3231_i2c_set_alarm2(ds3231_alarm2_t setting)
{
    uint8_t reg = REG_ALARM2_MINUTES;
    uint8_t data_read[3];
    uint8_t data_write[4];
    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, data_read, 3);

    if(err != DS3231_OK) 
        return err;

    data_write[0] = reg;
    for(uint8_t i=0; i<3;i++)
    {
        data_write[i+1] = (setting & ~(1 << i)) ? data_read[i] | (1 << 7) : data_read[i] & ~(1 << 7);
    }
    data_write[3] = (setting & ~(1 << 3)) ? data_read[2] | (1 << 6) : data_read[2] & ~(1 << 6);

    err = ds3231_i2c_hal_write(I2C_ADDRESS_DS3231, data_write, 4);

    return err;
}

int16_t ds3231_i2c_rate_select(ds3231_ratesel_t setting)
{
    uint8_t reg = REG_CONTROL;
    uint8_t data_read;
    uint8_t data_write[2];
    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, &data_read, 3);

    if(err != DS3231_OK) 
        return err;

    data_write[0] = reg;
    data_write[1] = (setting & ~(1 << 1)) ? data_read | (1 << 7) : data_read & ~(1 << 7);

    err = ds3231_i2c_hal_write(I2C_ADDRESS_DS3231, data_write, 2);

    return err;
}

int16_t ds3231_i2c_set_clock_format(ds3231_clock_format_t setting)
{
    uint8_t reg = REG_HOURS;
    uint8_t data_read;
    uint8_t data_write[2];

    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, &data_read, 1);
    if(err != DS3231_OK) 
        return err;

    data_write[0] = reg;
    data_write[1] = setting ? data_read | (1 << 6) : data_read & ~(1 << 6);

    err = ds3231_i2c_hal_write(I2C_ADDRESS_DS3231, data_write, 2);

    return err;
}

int16_t ds3231_i2c_osc_en(uint8_t status)
{
    uint8_t reg = REG_CONTROL;
    uint8_t data_read;
    uint8_t data_write[2];

    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, &data_read, 1);
    if(err != DS3231_OK) 
        return err;

    data_write[0] = reg;
    data_write[1] = status ? (data_read & ~(1 << 7)) : (data_read | (1 << 7));

    err = ds3231_i2c_hal_write(I2C_ADDRESS_DS3231, data_write, 2);

    return err;
}

int16_t ds3231_i2c_read_clock(ds3231_rtcc_cfg_t cfg, ds3231_rtcc_clock_t *dt)
{
    uint8_t reg = REG_SECONDS;
    uint8_t data[3] = {0};

    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, data, 3);
    if(err != DS3231_OK) 
        return err;

    dt->sec = bcd_to_dec(data[0]);
    dt->min = bcd_to_dec(data[1]);

    if(cfg.clock_format == FORMAT_24HR)
    {
        dt->hr = bcd_to_dec(data[2] & 0x3F);
    }
    else
    {
        dt->am_pm = (data[2] & ~(1 << 5));
        dt->hr = bcd_to_dec(data[2] & 0x1F);
    }

    return err;
}

int16_t ds3231_i2c_set_clock(ds3231_rtcc_cfg_t cfg, ds3231_rtcc_clock_t dt)
{
    uint8_t reg = REG_HOURS;
    uint8_t data[4] = {0};
    uint8_t hour_reg;

    if((cfg.clock_format == FORMAT_24HR && dt.hr > 23) || 
       (cfg.clock_format == FORMAT_12HR && dt.hr > 12) || 
       dt.min > 59 ||
       dt.sec > 59
       )
        return DS3231_ERR;

    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, &hour_reg, 1);
    if(err != DS3231_OK) 
        return err;

    data[0] = REG_SECONDS;
    data[1] = dec_to_bcd(dt.sec);
    data[2] = dec_to_bcd(dt.min);
    data[3] = (cfg.clock_format == FORMAT_24HR) ? (hour_reg & 0xC0) | dec_to_bcd(dt.hr) : (hour_reg & 0xE0) | dec_to_bcd(dt.hr);
    data[3] = (cfg.clock_format == FORMAT_24HR) ? data[3] : ((data[3] & ~(1 << 5)) | (dt.am_pm << 5));

    err = ds3231_i2c_hal_write(I2C_ADDRESS_DS3231, data, 4);

    return err;
}

int16_t ds3231_i2c_read_calendar(ds3231_rtcc_calendar_t *dt)
{
    uint8_t reg = REG_DAY;
    uint8_t data[4] = {0};

    int16_t err = ds3231_i2c_hal_read(I2C_ADDRESS_DS3231, &reg, data, 4);
    if(err != DS3231_OK) 
        return err;

    dt->day = bcd_to_dec(data[0]);
    dt->date = bcd_to_dec(data[1]);
    dt->mon = bcd_to_dec(data[2] & 0x7F);
    dt->year = 2000 + (uint16_t) bcd_to_dec(data[3]);
    dt->century = data[2] >> 7;

    return err;
}

int16_t ds3231_i2c_set_calendar(ds3231_rtcc_calendar_t dt)
{
    uint8_t reg = REG_DATE;
    uint8_t data[4] = {0};

    data[0] = reg;
    data[1] = dec_to_bcd(dt.date);
    data[2] = dec_to_bcd(dt.mon & 0x7F);
    data[3] = dec_to_bcd((uint16_t)(dt.year - 2000));

    int16_t err = ds3231_i2c_hal_write(I2C_ADDRESS_DS3231, data, 4);

    return err;
}

int16_t ds3231_i2c_dev_config(ds3231_rtcc_cfg_t cfg)
{
    /* Set clock format */
    int16_t err = ds3231_i2c_set_clock_format(cfg.clock_format);
    
    if(err != DS3231_OK) 
        return err;

    ds3231_i2c_hal_ms_delay(50);

    /* Set alarm 1 */
    if(cfg.alarm1_en == TRUE)
    {
        err = ds3231_i2c_set_alarm1(cfg.alarm1_set);
        if(err != DS3231_OK) 
            return err;
        ds3231_i2c_hal_ms_delay(50);
    }

    /* Set alarm 2 */
    if(cfg.alarm2_en == TRUE)
    {
        err = ds3231_i2c_set_alarm2(cfg.alarm2_set);
        if(err != DS3231_OK) 
            return err;
        ds3231_i2c_hal_ms_delay(50);
    }

    /* Set rate */
    err = ds3231_i2c_rate_select(cfg.rate_select);
    if(err != DS3231_OK) 
        return err;
    ds3231_i2c_hal_ms_delay(50);

    return err;
}