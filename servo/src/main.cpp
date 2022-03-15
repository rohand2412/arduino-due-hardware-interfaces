/**
 * Servo_Wrapper test cases/example code
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
#include <Servo_Wrapper.h>
#include <LED.h>

/*==========================

Arduino Due -----  Servo
5V          -----    RED
GND         -----  BLACK
9           ----- YELLOW   
(^Any PWM Pin Works)

==========================*/

Servo_Wrapper camServo(47, 137);

LED led(5);

void setup() 
{
    Serial.begin(115200);

    led.begin();
    led.on();
    led.setPwm(255);

    camServo.attach(Servo_Wrapper::SERVO_S2);
    camServo.write(18);
}

void loop() {}
