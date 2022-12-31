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

    if (err == DS3231_OK)
    {
        ESP_LOGI(TAG, "DS3231 initialization successful");
        ds3231_data_t data;
        while(1)
        {
            //Reading here

            ds3231_i2c_hal_ms_delay(1000);
        }
    }
    else{
        ESP_LOGE(TAG, "DS3231 initialization failed!");
    }
}
