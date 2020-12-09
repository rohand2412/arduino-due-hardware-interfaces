#include <Arduino.h>
#include <Wire.h>
#include <Ultrasonic.h>

Ultrasonic ultrasonic(22, 24, 20);

void ultrasonicEchoPinISR()
{
  ultrasonic.echoPinISR();
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  delay(300);

  ultrasonic.begin(&ultrasonicEchoPinISR);
}

void loop() {
  ultrasonic.update();
  Serial.println(ultrasonic.getDistance());
}