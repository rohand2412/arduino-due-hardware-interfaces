#include <Arduino.h>

const uint8_t pin = 40;

const size_t LOG_BUF_LEN = 2000;
unsigned long logBuf[LOG_BUF_LEN];
size_t logLen = 0;

void interruptHandler()
{
    if (logLen < LOG_BUF_LEN)
    {
        logBuf[logLen] = millis();
        logLen++;
        logBuf[logLen] = digitalRead(pin);
        logLen++;
    }
}

void setup() 
{
    Serial.begin(115200);

    pinMode(pin, INPUT);
    attachInterrupt(digitalPinToInterrupt(pin), interruptHandler, CHANGE);
}

void loop()
{
    if (logLen >= LOG_BUF_LEN)
    {
        const size_t PAIR_NUM = LOG_BUF_LEN / 2;
        unsigned long curLogTime = logBuf[0] + 1;

        for (size_t i = 0; i < PAIR_NUM; i++)
        {
            while (curLogTime <= logBuf[i * 2])
            {
                Serial.print(i - 1);
                Serial.print("      ");
                Serial.print(curLogTime);
                Serial.print("      ");
                Serial.print(logBuf[i * 2 - 1]);
                Serial.print("\n");
                curLogTime++;
            }

            curLogTime = logBuf[i * 2];
            Serial.print(i);
            Serial.print("      ");
            Serial.print(curLogTime);
            Serial.print("      ");
            Serial.print(logBuf[i * 2 + 1]);
            Serial.print("\n");
        }

        while (true)
            ;
    }
}