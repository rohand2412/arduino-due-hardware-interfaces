/**
 * Ultrasonic_Wrapper test cases/example code
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
#include <Ultrasonic_Wrapper.h>

unsigned int echoPins[5] = {53, 51, 49, 47, 33};
Ultrasonic_Wrapper ultrasonics(52, echoPins, 20, 5);

void ultrasonicFrontEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_FRONT); }

void ultrasonicLeftEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_LEFT); }

void ultrasonicRightEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_RIGHT); }

void ultrasonicBackEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_BACK); }

void ultrasonicTopEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_TOP); }

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  delay(300);

  void (*ultrasonicISR[5])() = {ultrasonicFrontEchoPinISR,
                                ultrasonicLeftEchoPinISR, 
                                ultrasonicRightEchoPinISR, 
                                ultrasonicBackEchoPinISR,
                                ultrasonicTopEchoPinISR};
  ultrasonics.begin(ultrasonicISR);
}

void loop() {
  ultrasonics.update();
  Serial.print("Front: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_FRONT));
  Serial.print("\tLeft: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_LEFT));
  Serial.print("\tRight: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_RIGHT));
  Serial.print("\tBack: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_BACK));
  Serial.print("\tTop: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_TOP));
  Serial.print("\n");
}