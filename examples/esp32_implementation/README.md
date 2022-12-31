# DS3231 - ESP-IDF

DS3231 I2C library for ESP-IDF.
ESP-IDF template used for this project: https://github.com/espressif/esp-idf/tree/master/examples/peripherals/i2c/i2c_simple

## Overview

This example demonstrates usage of DS3231 for reading realtime clock/calendar.

### Hardware Required

The DS3231 is a low-cost, extremely accurate I2C real-time clock (RTC) with an integrated temperaturecompensated crystal oscillator (TCXO) and crystal. The device incorporates a battery input, and maintains accurate timekeeping when main power to the device is interrupted. You can read the datasheet [here](https://www.analog.com/media/en/technical-documentation/data-sheets/DS3231.pdf).

#### Pin Assignment:

**Note:** The following pin assignments are used by default, you can change these in the `menuconfig` .

|                  | SDA            | SCL            |
| ---------------- | -------------- | -------------- |
| ESP I2C Master   | I2C_MASTER_SDA | I2C_MASTER_SCL |
| DS3231           | SDA            | SCL            |


For the actual default value of `I2C_MASTER_SDA` and `I2C_MASTER_SCL` see `Example Configuration` in `menuconfig`.

**Note: ** There’s no need to add an external pull-up resistors for SDA/SCL pin, because the driver will enable the internal pull-up resistors.

### Build and Flash

Enter `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

See the [Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for full steps to configure and use ESP-IDF to build projects.

## Example Output

```bash
I (515) example_usage: Device config successful
I (515) example_usage: Time setting successful
I (515) example_usage: Calendar setting successful
I (515) example_usage: DS3231 initialization successful
I (525) example_usage: Time: 19:30:05
I (525) example_usage: Date: 12/31/2022
I (1525) example_usage: Time: 19:30:06
I (1525) example_usage: Date: 12/31/2022
I (2525) example_usage: Time: 19:30:07
I (2525) example_usage: Date: 12/31/2022
I (3525) example_usage: Time: 19:30:08
I (3525) example_usage: Date: 12/31/2022
I (4525) example_usage: Time: 19:30:09
I (4525) example_usage: Date: 12/31/2022
I (5525) example_usage: Time: 19:30:10
I (5525) example_usage: Date: 12/31/2022
I (6525) example_usage: Time: 19:30:11
I (6525) example_usage: Date: 12/31/2022
I (7525) example_usage: Time: 19:30:12
I (7525) example_usage: Date: 12/31/2022
I (8525) example_usage: Time: 19:30:13
I (8525) example_usage: Date: 12/31/2022
I (9525) example_usage: Time: 19:30:14
I (9525) example_usage: Date: 12/31/2022
I (10525) example_usage: Time: 19:30:15
I (10525) example_usage: Date: 12/31/2022
I (11525) example_usage: Time: 19:30:16
I (11525) example_usage: Date: 12/31/2022
I (12525) example_usage: Time: 19:30:17
I (12525) example_usage: Date: 12/31/2022
I (13525) example_usage: Time: 19:30:18
I (13525) example_usage: Date: 12/31/2022
I (14525) example_usage: Time: 19:30:19
I (14525) example_usage: Date: 12/31/2022
I (15525) example_usage: Time: 19:30:20
I (15525) example_usage: Date: 12/31/2022
I (16525) example_usage: Time: 19:30:21
I (16525) example_usage: Date: 12/31/2022
```