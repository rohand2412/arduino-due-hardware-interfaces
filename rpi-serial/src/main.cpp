#include <Arduino.h>
#include <Wire.h>
#include <Serial_Wrapper.h>

const size_t bufferLen = 10;
uint8_t buffer[bufferLen];
size_t dataLen = 0;

void setup() 
{
    Serial_Wrapper::begin(750000, Serial);

    Serial_Wrapper::begin(115200, Serial3);
    Serial_Wrapper::setDefault(Serial3);
}

void loop() 
{
    dataLen = Serial_Wrapper::receive(buffer, bufferLen);
    Serial_Wrapper::send(buffer, dataLen);
}