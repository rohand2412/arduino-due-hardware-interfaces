#include <Arduino.h>
#include <IMU_Wrapper.h>

/*==========================

Arduino Due ----- MPU6050
3.3V        -----     VCC
GND         -----     GND
38          -----     INT
(^Any Interrupt Pin Works)
SDA(20)     -----     SDA
SCL(21)     -----     SCL

==========================*/

IMU_Wrapper imu(38);    //Input whichever interrupt pin IMU is connected to

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
    imu.begin(imuDmpDataReady);
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