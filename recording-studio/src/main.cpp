#include <Arduino.h>
#include <Robot.h>

Robot robot;

void ultrasonicFrontISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_FRONT); }

void ultrasonicLeftISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_LEFT); }

void ultrasonicRightISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_RIGHT); }

void ultrasonicBackISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_BACK); }

void buttonPinISR() { robot.getButton().pinISR(); }

int increment = -1;
unsigned long INTERVAL_MS = 0;
unsigned long lastTimeServo = millis() - INTERVAL_MS;

void setup()
{
    void (*ultrasonicISR[4])() = {ultrasonicFrontISR,
                                  ultrasonicLeftISR,
                                  ultrasonicRightISR,
                                  ultrasonicBackISR};
    robot.begin(ultrasonicISR, buttonPinISR);

    robot.getRGB_LED().setPwm(255, 0, 0);
    robot.getRGB_LED().on();
    while (robot.isDormant())
    {
        robot.update();
    }
    robot.getRGB_LED().setPwm(0, 0, 255);

    int32_t buffer[1];
    size_t dataLen = Serial_Wrapper::receive(buffer, 1);
    while (dataLen == 0xFFFFFFFF)
    {
        dataLen = Serial_Wrapper::receive(buffer, 1);
    }
    robot.getRGB_LED().off();
}

void loop()
{
    robot.update();

    if (millis() >= lastTimeServo + INTERVAL_MS)
    {
        robot.getArmServo().write(robot.getArmServo().read() + increment);
        if (robot.getArmServo().read() > 85)
        {
            INTERVAL_MS = 20;
            increment = -1;
            delay(500);
        }
        else if (robot.getArmServo().read() <= 0)
        {
            INTERVAL_MS = 20;
            increment = 1;
            delay(500);
        }

        lastTimeServo = millis();
    }
}