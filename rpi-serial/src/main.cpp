#include <Arduino.h>
#include <Wire.h>
#include <Serial_Wrapper.h>

void setup() 
{
    Serial_Wrapper::begin(750000, Serial);

    Serial_Wrapper::begin(115200, Serial3);
}

void loop() 
{
    Serial.println("It works!");
    Serial3.write('a');
}