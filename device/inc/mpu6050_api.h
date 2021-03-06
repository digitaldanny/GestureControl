#ifndef _SRC_MPU6050_API
#define _SRC_MPU6050_API

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * INCLUDES
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

#include "build_switches.h"
#include "target_hw_common.h"
#include "i2c_if.h"

/*
 * +=====+=====+=====+=====+=====+=====+=====+==5===+=====+=====+=====+=====+
 * DEFINES
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

// Configuration register indices
#define MPU6050_NUM_CONFIGS         3
#define MPU6050_PWR_MGMT_1          0
#define MPU6050_GYRO_CONFIG         1
#define MPU6050_ACCEL_CONFIG        2

// Other
#define MPU6050_DEV_ADDR            0x68
#define MPU6050_SENSOR_ADDR_START   0x3B    // XACCEL_H is the first address to read from to capture all sensor values
#define MPU6050_SENSOR_BURST_LEN    14      // 6 regs Accel X-Z H/L, 2 regs Temp H/L, 6 regs Gyro X-Z H/L

// Gyro error calculated using the TEST_mpu6050GyroError script (build switch = ENABLE_MPU6050_ESTIMATE_GYRO_ERROR)
// The first values are the ones estimated by the script and the second values are the ones that I eyeballed on the LCD
#define MPU6050_GYRO_ERROR_X        (114-150)
#define MPU6050_GYRO_ERROR_Y        (-444+220)
#define MPU6050_GYRO_ERROR_Z        (-168+40)

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * PROTOTYPES
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

namespace Mpu6050Api {

    /*
    * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
    * PROTOTYPES
    * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
    */

    bool init();
    bool readSensorData(int16_t* accelBuffer, int16_t* gyroBuffer);
}
#endif // _SRC_MPU6050_API
