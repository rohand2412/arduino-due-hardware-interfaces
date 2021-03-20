#include <Arduino.h>
#include <Wire.h>
#include <Button_Wrapper.h>

Button_Wrapper button(40);

void buttonISR()
{
    button.pinISR();
}

void setup() {
    Serial.begin(115200);

    button.begin(buttonISR);
}

void loop()
{
    button.update();

    Serial.println(button.getState());
}