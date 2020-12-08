#include <Arduino.h>
#include <IMU_Wrapper.h>

IMU_Wrapper imu(38);

void imuDmpDataReady()
{
    imu.dmpDataReady();
}

void setup() 
{
    Serial.begin(115200);
    while (!Serial);
    delay(300);

    imu.setOffsets(1462, -2132, 1028, -151, 13, 41);
    imu.begin(&imuDmpDataReady);
}

void loop() 
{
    imu.update();
    Serial.print("ypr\t");
    Serial.print(imu.getYaw());
    Serial.print("\t");
    Serial.print(imu.getPitch());
    Serial.print("\t");
    Serial.print(imu.getRoll());
    Serial.println();
}