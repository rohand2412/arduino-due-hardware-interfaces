#include <Arduino.h>
#include <Wire.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonicLeft(22, 24, 20);
Ultrasonic ultrasonicRight(22, 28, 20);

void ultrasonicLeftEchoPinISR()
{
  ultrasonicLeft.echoPinISR();
}

void ultrasonicRightEchoPinISR()
{
  ultrasonicRight.echoPinISR();
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  delay(300);

  ultrasonicLeft.begin(&ultrasonicLeftEchoPinISR);
  ultrasonicRight.begin(&ultrasonicRightEchoPinISR);
}

void loop() {
  ultrasonicLeft.update();
  ultrasonicRight.update();
  Serial.print(ultrasonicLeft.getDistance());
  Serial.print("\t");
  Serial.println(ultrasonicRight.getDistance());
}