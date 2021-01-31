#include <Arduino.h>
#include <Wire.h>
#include <LightPeripherals.h>

LED led(39);

RGB_LED rgb(36, 35, 37);

void setup() 
{
    led.begin();
    rgb.begin();
}

void loop() 
{
    led.toggle();
    rgb.toggle();
    delay(250);
}