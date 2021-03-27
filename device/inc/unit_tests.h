#ifndef _SRC_UNIT_TESTS
#define _SRC_UNIT_TESTS

#include "build_switches.h"

#if ENABLE_UNIT_TEST_EXT_PWR_SWITCH
void unitTest_enableExternalHwPower();
#endif // ENABLE_UNIT_TEST_EXT_PWR_SWITCH

#if ENABLE_UNIT_TEST_WIRELESS_API
int unitTest_wirelessApi();
#endif // ENABLE_UNIT_TEST_WIRELESS_API

#if ENABLE_UNIT_TEST_NXP_API
int unitTest_nxpApi();
#endif // ENABLE_UNIT_TEST_NXP_API

#if ENABLE_UNIT_TEST_MUX
int unitTest_mux();
#endif // ENABLE_UNIT_TEST_MUX

#if ENABLE_UNIT_TEST_MUX_LP
int unitTest_muxLp();
#endif // ENABLE_UNIT_TEST_MUX_C2000

#if ENABLE_UNIT_TEST_ADC
int unitTest_adc();
#endif // ENABLE_UNIT_TEST_ADC

#if ENABLE_UNIT_TEST_ADC_C2000
int unitTest_adcC2000();
#endif // ENABLE_UNIT_TEST_ADC_C2000

#if ENABLE_UNIT_TEST_ADC_MSP432
int unitTest_adcMsp432();
#endif // ENABLE_UNIT_TEST_ADC_MSP432

#if ENABLE_UNIT_TEST_FLEX_SENSORS
int unitTest_flexSensors();
#endif // ENABLE_UNIT_TEST_FLEX_SENSORS

#if ENABLE_UNIT_TEST_HC05_DEVICE_NAME
int unitTest_hc05DeviceName();
#endif // ENABLE_UNIT_TEST_HC05_DEVICE_NAME

#if ENABLE_UNIT_TEST_MPU6500_WHOAMI_SPI
int TEST_mpu6500WhoAmISpi();
#endif // ENABLE_UNIT_TEST_MPU6500_WHOAMI_SPI

#endif // _SRC_UNIT_TESTS
