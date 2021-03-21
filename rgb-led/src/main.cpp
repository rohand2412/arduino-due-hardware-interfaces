#include <Arduino.h>
#include <Wire.h>
#include <LightPeripherals.h>

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