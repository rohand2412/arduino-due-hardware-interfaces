/**
 * RGB_LED test cases/example code
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
#include "RGB_LED.h"

RGB_LED rgb(2, 3, 4);

size_t rgb_index = RGB_LED::RED_INDEX;

void setup() 
{
    rgb.begin();
    rgb.on();
}

void loop() 
{
    for (int i = 0; i <= 255; i++)
    {
        rgb.setPwm(i, rgb_index);
        delay(10);
    }

    if (rgb_index == RGB_LED::BLUE_INDEX)
    {
        rgb_index = RGB_LED::RED_INDEX;
    }
    else
    {
        rgb_index++;
    }

    for (int i = 255; i >= 0; i--)
    {
        switch (rgb_index)
        {
            case RGB_LED::RED_INDEX:
                rgb.setPwm(i, rgb.getPwm(RGB_LED::GREEN_INDEX), rgb.getPwm(RGB_LED::BLUE_INDEX));
                break;
            case RGB_LED::GREEN_INDEX:
                rgb.setPwm(rgb.getPwm(RGB_LED::RED_INDEX), i, rgb.getPwm(RGB_LED::BLUE_INDEX));
                break;
            case RGB_LED::BLUE_INDEX:
                rgb.setPwm(rgb.getPwm(RGB_LED::RED_INDEX), rgb.getPwm(RGB_LED::GREEN_INDEX), i);
                break;
        }

        delay(10);
    }

    if (rgb_index == RGB_LED::BLUE_INDEX)
    {
        rgb_index = RGB_LED::RED_INDEX;
    }
    else
    {
        rgb_index++;
    }
}