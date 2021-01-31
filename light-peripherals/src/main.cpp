#include <Arduino.h>
#include <Wire.h>
#include <LightPeripherals.h>

LED led(39);

void setup() 
{
    led.begin();
}

void loop() 
{
    led.toggle();
    delay(250);
}