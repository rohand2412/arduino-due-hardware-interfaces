/**
 * Displays encoder counts corresponding to pwm values that a motor is run at
 * (used to find relationship between pwm and motor speed for simulating PID and finding coeffs in a spreadsheet)
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
#include <Wire.h>
#include <Motor_Wrapper.h>
#include <Serial_Wrapper.h>

size_t motorNum = 2;
unsigned int motorPorts[2] = {Motor_Wrapper::SHIELD_M1, Motor_Wrapper::SHIELD_M3};
Motor_Wrapper motors(motorPorts, motorNum);

Encoder_Wrapper encoders;
const unsigned long INTERVAL_MS = 20;
const unsigned long COUNTS_PER_REV = 4560;

void setup()
{
  Serial_Wrapper::begin(750000, Serial);

  {
    unsigned int encoderPins[motorNum * Encoder_Wrapper::PINS_PER_SENSOR] = {46, 44, 50, 48};
    motors.setEncoders(encoderPins);
  }

  motors.setPid(0.8, 0.75, 0, Motor_Wrapper::MOTOR_LEFT);
  motors.setPid(0.85, 0.8, 0, Motor_Wrapper::MOTOR_RIGHT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_FLIP, Motor_Wrapper::MOTOR_LEFT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_NO_FLIP, Motor_Wrapper::MOTOR_RIGHT);

  motors.begin();

  const size_t encoderNum = 2;
  unsigned int encoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {44, 46, 48, 50};
  encoders.createSensor(encoderPins, encoderNum);
}

void loop()
{
  for (size_t motor = 1; motor < motors.getMotorNum(); motor++)
  {
    //Change bounds in intervals to prevent wire twisting
    for (uint8_t pwm = 0; pwm <= 100; pwm += 5)
    {
      encoders.resetCount();
      motors.setPwm(pwm, motor);
      unsigned long lastTime = millis();
      motors.start();
      while (millis() - lastTime <= 5000)
      {
          motors.update();
      }
      unsigned long now = millis();
      motors.stop();
      double timeScaler = (double) INTERVAL_MS / (double) (now - lastTime);
      double countsPerTime = encoders.getCount(motor) * timeScaler * motors.getSpeedMultiplier(motor);
      Serial.print(pwm);
      Serial.print("\t");
      Serial.println(countsPerTime);
      delay(2000);
    }
    while (true)
      ;
  }
}