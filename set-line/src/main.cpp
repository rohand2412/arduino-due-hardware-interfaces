#include <Arduino.h>
#include <Robot.h>

Robot robot;

void ultrasonicFrontISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_FRONT); }

void ultrasonicLeftISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_LEFT); }

void ultrasonicRightISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_RIGHT); }

void ultrasonicBackISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_BACK); }

void ultrasonicTopISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_TOP); }

void buttonPinISR() { robot.getButton().pinISR(); }

void setup()
{
    void (*ultrasonicISR[5])() = {ultrasonicFrontISR,
                                  ultrasonicLeftISR,
                                  ultrasonicRightISR,
                                  ultrasonicBackISR,
                                  ultrasonicTopISR};
    robot.begin(ultrasonicISR, buttonPinISR);

    while (robot.isDormant())
    {
        robot.update();
    }

    robot.setLine();
}

void loop()
{
    robot.update();
}