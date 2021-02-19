#include <Arduino.h>
#include <Wire.h>
#include <Serial_Wrapper.h>

const size_t bufferLen = 256;
long buffer[bufferLen];
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

    if (dataLen != 0xFFFFFFFF) //!= -1
    {
        Serial_Wrapper::send(buffer, dataLen);
    }
}