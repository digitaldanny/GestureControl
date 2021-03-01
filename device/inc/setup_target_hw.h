/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * DESCRIPTION: setup_target_hw.h
 * This file contains functions to initialize **non-module** target hardware.
 * Examples of inits in this file) Setting clock speed, disabling WDT
 * Examples of inits NOT in this file) Configuring UART for transmitting Bluetooth data
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * INCLUDES
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/
#ifndef _SETUP_TARGET_HARDWARE
#define _SETUP_TARGET_HARDWARE

#include "build_switches.h"

#if TARGET_HW_C2000
extern "C" {
 #include "device.h"
}
#endif // TARGET_HW_C2000

#if TARGET_HW_MSP432
extern "C" {
 #include "driverlib.h"
}
#endif // TARGET_HW_MSP432

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * FUNCTIONS
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

void setupTargetHw();

#endif // _SETUP_TARGET_HARDWARE
