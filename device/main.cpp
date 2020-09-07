#include <stdio.h>
#include "build_switches.h"
#include "nxp_interface_api.h"

int main()
{
    NxpWrapper::SensorData_t data;

    printf("TARGET_HW_RASBERRYPI: %d\n", TARGET_HW_RASPBERRYPI);
    printf("nxp.init = %d\n", NxpWrapper::Init());

    for (int i = 0; i < 100; i++)
    {
        NxpWrapper::GetAccelData(data);
        printf("C Accel Data: %f, %f, %f\n", data.x, data.y, data.z);

        NxpWrapper::GetMagData(data);
        printf("C Mag Data: %f, %f, %f\n", data.x, data.y, data.z);
        
        NxpWrapper::GetGyroData(data);
        printf("C Gyro Data: %f, %f, %f\n\n", data.x, data.y, data.z);
    }
    return 0;
}