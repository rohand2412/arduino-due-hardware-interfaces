/**
 * Serial_Wrapper test cases/example code
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
#include <Wire.h>
#include <Serial_Wrapper.h>

const size_t bufferLen = 256;
int32_t buffer[bufferLen] = {0};
size_t dataLen = 0;

void setup() 
{
    Serial_Wrapper::begin(750000, Serial);

    Serial_Wrapper::begin(115200, Serial2);
    Serial_Wrapper::setDefault(Serial2);
}

void loop() 
{
    dataLen = Serial_Wrapper::receive(buffer, bufferLen);

    if (dataLen != 0xFFFFFFFF) //!= -1
    {
        Serial_Wrapper::send(buffer, dataLen);
    }
}