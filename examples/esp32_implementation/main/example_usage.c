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
    esp_err_t err = DS3231_OK;

    ds3231_i2c_hal_init();

    ds3231_rtcc_cfg_t cfg = {
        .alarm1_set = ALARM1_DT_HR_MIN_SEC_MATCH,
        .alarm2_set = ALARM1_DT_HR_MIN_MATCH,
        .alarm1_en = FALSE,
        .alarm2_en = FALSE,
        .rate_select = RATE_SELECT_1HZ,
        .clock_format = FORMAT_24HR
    };

    ds3231_i2c_dev_config(cfg);

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
            ESP_LOGI(TAG, "Time: %02d:%02d:%02d", clock_data.hr, clock_data.min, clock_data.sec);
            ESP_LOGI(TAG, "Date: %02d/%02d/%02d", calendar_data.mon, calendar_data.day, calendar_data.year);
            ds3231_i2c_hal_ms_delay(1000);
        }
    }
    else{
        ESP_LOGE(TAG, "DS3231 initialization failed!");
    }
}
