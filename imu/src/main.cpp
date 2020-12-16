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

IMU_Wrapper imu(45);    //Input whichever interrupt pin IMU is connected to

void imuDmpDataReady()
{
    imu.dmpDataReady();
}

void setup() 
{
    Serial.begin(115200);
    while (!Serial);
    delay(300);

    imu.setOffsets(1451, -2164, 1053, -32, 11, 36);
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