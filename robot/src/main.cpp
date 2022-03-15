/**
 * Robot test cases/example code
 * Copyright (C) 2022  Rohan Dugad
 * 
 * Contact info:
 * https://docs.google.com/document/d/17IhBs4cz7FXphE0praCaWMjz016a7BFU5IQbm1CNnUc/edit?usp=sharing
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <Arduino.h>
#include <Robot.h>

Robot robot;

void ultrasonicFrontISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_FRONT); }

void ultrasonicLeftISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_LEFT); }

void ultrasonicRightISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_RIGHT); }

void ultrasonicBackISR() { robot.getUltrasonics().echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_BACK); }

void buttonPinISR() { robot.getButton().pinISR(); }

int turnCount = 0;

bool droveForward = false;
bool droveBackward = false;

uint32_t start_MS;

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
    robot.getRGB_LED().off();

    start_MS = millis();
}

void loop()
{
    robot.update();

    switch (millis() - start_MS)
    {
        case 0 ... 9999:
            robot.run(0.5, 0.5);
            break;
        
        case 10000 ... 14999:
            robot.stop();
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
                    robot.stop();
                }
            }
            break;

        case 65000 ... 69750:
            robot.getLED().toggle();
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

            if (!droveForward && !droveBackward && !robot.isDrivingDistance())
            {
                robot.runDistance_CM(0.5, 30);
                droveForward = true;
            }
            else if (droveForward && !droveBackward && !robot.isDrivingDistance())
            {
                robot.runDistance_CM(0.5, -30);
                droveBackward = true;
            }
            else if (droveForward && droveBackward && !robot.isDrivingDistance())
            {
                robot.stop();
            }
            break;

        case 90000 ... 109999:
            if (millis() - start_MS < 100000)
            {
                robot.run(0.5, 0.5);
            }
            else
            {
                robot.stop();
            }

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