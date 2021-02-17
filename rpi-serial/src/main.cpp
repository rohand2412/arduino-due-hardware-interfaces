#include <Arduino.h>
#include <Wire.h>
#include <Serial_Wrapper.h>

const size_t bufferLen = 256;
uint8_t buffer_uint8[bufferLen];
long buffer_long[bufferLen];
size_t dataLen = 0;

void setup() 
{
    Serial_Wrapper::begin(750000, Serial);

    Serial_Wrapper::begin(115200, Serial3);
    Serial_Wrapper::setDefault(Serial3);
}

void loop() 
{
    dataLen = Serial_Wrapper::receive(buffer_uint8, bufferLen);

    if (dataLen != 0xFFFFFFFF) //!= -1
    {
        for (size_t item = 0; item < dataLen; item++)
        {
            buffer_long[item] = buffer_uint8[item];
        }
        Serial_Wrapper::send(buffer_long, dataLen);
    }
}