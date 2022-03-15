/**
 * Logs status of a pin 2000 times for plotting, in a spreadsheet, a graph similar to oscilloscope
 * Copyright (C) 2022  Rohan Dugad
 * 
 * Contact info:
 * https://docs.google.com/document/d/17IhBs4cz7FXphE0praCaWMjz016a7BFU5IQbm1CNnUc/edit?usp=sharing
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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