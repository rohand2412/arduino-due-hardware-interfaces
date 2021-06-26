#include <Arduino.h>
#include <Wire.h>
#include <Servo_Wrapper.h>
#include <LED.h>

/*==========================

Arduino Due -----  Servo
5V          -----    RED
GND         -----  BLACK
9           ----- YELLOW   
(^Any PWM Pin Works)

==========================*/

Servo_Wrapper camServo(47, 137);

LED led(5);

void setup() 
{
    Serial.begin(115200);

    led.begin();
    led.on();
    led.setPwm(255);

    camServo.attach(Servo_Wrapper::SERVO_S2);
    camServo.write(18);
}

void loop() {}
