#include "esp_log.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//DS3231 components
#include "ds3231_i2c.h"
#include "ds3231_i2c_hal.h"

static const char *TAG = "example_usage";

#include "driver/i2c.h"

void app_main(void)
{
    esp_err_t err;

    ds3231_i2c_hal_init();

    ds3231_rtcc_cfg_t cfg = {
        .alarm1_set = ALARM1_DT_HR_MIN_SEC_MATCH,
        .alarm2_set = ALARM1_DT_HR_MIN_MATCH,
        .alarm1_en = FALSE,
        .alarm2_en = FALSE,
        .rate_select = RATE_SELECT_1HZ,
        .clock_format = FORMAT_12HR
    };

    err = ds3231_i2c_dev_config(cfg);
    if (err == DS3231_OK)
    {
        ESP_LOGI(TAG, "Device config successful");
    }
    else{
        ESP_LOGE(TAG, "Device config failed");
        return;
    }

    ds3231_rtcc_clock_t clock_set = {
        .hr = 11,
        .min = 59,
        .sec = 50,
        .am_pm = CLOCK_PERIOD_PM
    };

    err += ds3231_i2c_set_clock(cfg, clock_set);

    if (err == DS3231_OK)
    {
        ESP_LOGI(TAG, "Time setting successful");
    }
    else{
        ESP_LOGE(TAG, "Time setting failed");
        return;
    }

    ds3231_rtcc_calendar_t calendar_set = {
        .mon = 12,
        .date = 31,
        .year = 2022
    };

    err += ds3231_i2c_set_calendar(calendar_set);

    if (err == DS3231_OK)
    {
        ESP_LOGI(TAG, "Calendar setting successful");
    }
    else{
        ESP_LOGE(TAG, "Calendar setting failed");
        return;
    }

    if (err == DS3231_OK)
    {
        ESP_LOGI(TAG, "DS3231 initialization successful");
        ds3231_rtcc_calendar_t calendar_data;
        ds3231_rtcc_clock_t clock_data;
        while(1)
        {
            //Reading here
            ds3231_i2c_read_calendar(&calendar_data);
            ds3231_i2c_read_clock(cfg, &clock_data);
            if(cfg.clock_format == FORMAT_24HR)
            {
                ESP_LOGI(TAG, "Time: %02d:%02d:%02d", clock_data.hr, clock_data.min, clock_data.sec);
            }
            else
            {
                ESP_LOGI(TAG, "Time: %02d:%02d:%02d %s", clock_data.hr, 
                                                         clock_data.min, 
                                                         clock_data.sec, 
                                                         clock_data.am_pm ? "PM" : "AM"
                                                         );
            }
            ESP_LOGI(TAG, "Date: %02d/%02d/%02d", calendar_data.mon, calendar_data.date, calendar_data.year);
            ds3231_i2c_hal_ms_delay(1000);
        }
    }
    else{
        ESP_LOGE(TAG, "DS3231 initialization failed!");
    }
}
