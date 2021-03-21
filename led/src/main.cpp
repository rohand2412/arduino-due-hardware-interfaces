#include <Arduino.h>
#include <Wire.h>
#include "LED.h"

LED led(5);

void setup() 
{
    led.begin();
    led.on();
}

void loop() 
{
    for (int i = 0; i <= 255; i++)
    {
        led.setPwm(i);
        delay(10);
    }
    for (int i = 255; i >= 0; i--)
    {
        led.setPwm(i);
        delay(10);
    }
}