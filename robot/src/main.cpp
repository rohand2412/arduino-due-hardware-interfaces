#include <Arduino.h>
#include <Robot.h>

Robot robot;

void ultrasonicFrontISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_FRONT); }

void ultrasonicLeftISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_LEFT); }

void ultrasonicRightISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_RIGHT); }

void ultrasonicBackISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_BACK); }

void setup() 
{
    Serial_Wrapper::begin(115200, Serial);


    void (*ultrasonicISR[4])() = {ultrasonicFrontISR,
                                  ultrasonicLeftISR,
                                  ultrasonicRightISR,
                                  ultrasonicBackISR};
    robot.begin(ultrasonicISR);
}

void loop()
{
    robot.update();

    switch (millis())
    {
        case 0 ... 9999:
            robot.run(0.5, 0.5);
            break;
        
        case 10000 ... 14999:
            robot.getMotors().stop();
            robot.captureBall();
            break;
        
        case 15000 ... 19999:
            robot.holdBalls();
            break;
        
        case 20000 ... 24999:
            robot.dropBalls();
            break;
        
        case 25000 ... 29999:
            robot.setLine();
            break;
        
        case 30000 ... 34999:
            robot.setEvac();
            break;

        case 35000 ... 64999:
            robot.getIMU().displayOrientation();
            robot.getIMU().displayCalStatus();
            break;

        default:
            Serial.print("nearObstacle: ");
            Serial.print(robot.nearObstacle());
            Serial.print("\tFront: ");
            Serial.print(robot.getUltrasonics().getDistance(Ultrasonic_Wrapper::ULTRASONIC_FRONT));
            Serial.print("\tBack: ");
            Serial.print(robot.getUltrasonics().getDistance(Ultrasonic_Wrapper::ULTRASONIC_BACK));
            Serial.print("\tLeft: ");
            Serial.print(robot.getUltrasonics().getDistance(Ultrasonic_Wrapper::ULTRASONIC_LEFT));
            Serial.print("\tRight: ");
            Serial.print(robot.getUltrasonics().getDistance(Ultrasonic_Wrapper::ULTRASONIC_RIGHT));
            Serial.print("\n");
            break;
    }
}