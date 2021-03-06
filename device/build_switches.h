/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * DESCRIPTION: build_switches.h
 * This file contains all switches that are used to determine features or
 * unit tests that will be compiled.
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

#ifndef _BUILD_SWITCHES
#define _BUILD_SWITCHES

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * TARGET HARDWARE
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/
#define TARGET_HW_RASPBERRYPI    0   // Issue #1: Enables firmware that will only run on the prototype (Raspberry Pi).
#define TARGET_HW_DESKTOP        0   // Issue #9: Enables dummy responses from sensors for Desktop development.
#define TARGET_HW_C2000          0   // Issue #13: Enables firmware specific to C2000 development board.
#define TARGET_HW_MSP432         1   // Enables firmware specific to MSP432 launchpad.
#define TARGET_HW_PYTHON_CAPABLE (1 & (TARGET_HW_RASPBERRYPI | TARGET_HW_DESKTOP)) // Determines if the selected target hardware can make calls to Python.
#if (TARGET_HW_RASPBERRYPI + TARGET_HW_DESKTOP + TARGET_HW_C2000 + TARGET_HW_MSP432) > 1
 #error Only 1 hardware target can be active per build.
#endif

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * ENTRY POINTS (Main programs / Unit tests)
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

// Unit tests
#define ENABLE_UNIT_TEST                (0)
#define ENABLE_UNIT_TEST_TIMER_DELAY    (0 & ENABLE_UNIT_TEST)  // Issue NONE: Infinitely toggle using ms and us delays. Requires oscilloscope connections.
#define ENABLE_UNIT_TEST_WIRELESS_API   (0 & ENABLE_UNIT_TEST)   // Issue #8: Enables unit test for the wireless API.
#define ENABLE_UNIT_TEST_NXP_API        (0 & ENABLE_UNIT_TEST)   // Issue #2: Enables unit test for the gyro/accel/mag sensor pack reading.
#define ENABLE_UNIT_TEST_MUX            (0 & ENABLE_UNIT_TEST)   // Issue #7: Enables unit test for setting mux channels.
#define ENABLE_UNIT_TEST_MUX_LP         (0 & ENABLE_UNIT_TEST)   // Issue #15: Enables unit test for setting mux channels on the C2000 dev board.
#define ENABLE_UNIT_TEST_ADC            (0 & ENABLE_UNIT_TEST)   // Issue #7: Enables unit test for reading adc channels.
#define ENABLE_UNIT_TEST_ADC_C2000      (0 & ENABLE_UNIT_TEST)   // Issue #14: Enables unit test for reading both adc channels at the same time.
#define ENABLE_UNIT_TEST_ADC_MSP432     (0 & ENABLE_UNIT_TEST)   // Issue #36: Enables unit test for reading ADC values from flex amplifier.
#define ENABLE_UNIT_TEST_FLEX_SENSORS   (0 & ENABLE_UNIT_TEST)   // Issue #7: Enables unit test for reading all 10 flex sensor voltage levels.
#define ENABLE_UNIT_TEST_HC05_DEVICE_NAME (0 & ENABLE_UNIT_TEST)   // Issue #37: Enable test to read back HC-05 "NAME" register (returns "HC-05" by default)
#define ENABLE_UNIT_TEST_HC05_RW_TO_SLAVE (0 & ENABLE_UNIT_TEST) // Issue #35: Enable unit test to repeatedly write to / read from slave HC-05.
#define ENABLE_UNIT_TEST_I2C            (0 & ENABLE_UNIT_TEST)   // Issue #39: Enable basic I2C write/read test to be read on logic analyzer.
#define ENABLE_UNIT_TEST_EXT_PWR_SWITCH (1 & ENABLE_UNIT_TEST)  // Issue #45: Enable test that toggles external power switch. Power output be manually validated with DAD board.
#define ENABLE_UNIT_TEST_MPU6500_WHOAMI_SPI (0 & ENABLE_UNIT_TEST) // Issue #47: Enable SPI read from MPU6500's WHO_AM_I register.
#define ENABLE_UNIT_TEST_MPU6050_WHOAMI_I2C (0 & ENABLE_UNIT_TEST) // Issue #47: Enable I2C read from MPU6050's WHO_AM_I register.
#define ENABLE_UNIT_TEST_MPU6050_SENSORDATA (0 & ENABLE_UNIT_TEST) // Issue #47: Enable reading gyro/accelerometer data from MPU6050 and converting to Euler angles using DMP.
#define ENABLE_UNIT_TEST_MPU6050_SENSORDATA_RAW (0 & ENABLE_UNIT_TEST) // Issue #47: Reading raw gyro / accelerometer sensor data from MPU6050 without DMP.
#define ENABLE_UNIT_TEST_LCD_DEMO       (0 & ENABLE_UNIT_TEST)  // Issue #46: Enable demo animations to run on CFAL6448A lcd over SPI.
#define ENABLE_UNIT_TEST_LCD_TEXT       (0 & ENABLE_UNIT_TEST)  // Issue #46: Draws custom text and image to the LCD.
#define ENABLE_UNIT_TEST_STATE_OF_CHARGE (0 & ENABLE_UNIT_TEST) // Issue #51: Estimates battery state of charge using OCV and CCV circuits.

#define ENABLE_MPU6050_ESTIMATE_GYRO_ERROR  (0) // Issue #47: Script to get the average gyro error seen while the device is sitting still.
#define ENABLE_HC05_CONFIG_MSTR (0) // Issue #35: Script to configure the master HC-05's role, slave address, etc.
#define ENABLE_HAND_TRACKING_GLOVE (1) // Issue #53: Hand tracking glove's main loop (capture data, transfer to DSP Effects Rack)

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * WIRELESS API
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/
#define ENABLE_WIRELESS_API_PYTHON  (0 & TARGET_HW_PYTHON_CAPABLE) // Issue #8: Enables calls to server.py for sending/receiving client requests.

#endif
