#include <Arduino.h>
#include <IMU.h>

IMU imu(38);

void imuDmpDataReady()
{
    imu.dmpDataReady();
}

void setup() 
{
    Serial.begin(115200);
    while (!Serial);
    delay(300);

    imu.setOffsets(1474, -2125, 1039, -174, 10, 40);
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