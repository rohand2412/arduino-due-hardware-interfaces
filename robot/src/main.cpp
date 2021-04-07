#include <Arduino.h>
#include <Robot.h>

Robot robot;

void ultrasonicFrontISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_FRONT); }

void ultrasonicLeftISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_LEFT); }

void ultrasonicRightISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_RIGHT); }

void ultrasonicBackISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_BACK); }

void buttonPinISR() { robot.getButton().pinISR(); }

int turnCount = 0;

bool drove = false;

void setup() 
{
    void (*ultrasonicISR[4])() = {ultrasonicFrontISR,
                                  ultrasonicLeftISR,
                                  ultrasonicRightISR,
                                  ultrasonicBackISR};
    robot.begin(ultrasonicISR, buttonPinISR);
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
            Serial.print("isTurning: ");
            Serial.print(robot.isTurning());
            Serial.print("\t");
            robot.getIMU().displayOrientation();
            robot.getIMU().displayCalStatus();

            if (!robot.isTurning())
            {
                if (!turnCount)
                {
                    robot.turn(90);
                    turnCount++;
                }
                else if (turnCount == 1)
                {
                    robot.turn(-180);
                    turnCount++;
                }
                else
                {
                    robot.run(0, 0);
                }
            }
            break;

        case 65000 ... 69750:
            robot.getLED().toggle();
            robot.getRGB_LED().toggle();
            delay(250);
            break;

        case 70000 ... 89999:
            Serial.print("isDrivingDistance: ");
            Serial.print(robot.isDrivingDistance());
            Serial.print("\tLeftCounts: ");
            Serial.print(robot.getEncoders().getCount(Encoder_Wrapper::ENCODER_LEFT));
            Serial.print("\tRightCounts: ");
            Serial.print(robot.getEncoders().getCount(Encoder_Wrapper::ENCODER_RIGHT));
            Serial.print("\n");

            if (!drove)
            {
                robot.runDistance_CM(0.5, 30);
                drove = true;
            }
            if (!robot.isDrivingDistance())
            {
                robot.getMotors().stop();
            }
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