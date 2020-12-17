#include <Arduino.h>
#include <Wire.h>
#include <Servo_Wrapper.h>

/*==========================

Arduino Due -----  Servo
5V          -----    RED
GND         -----  BLACK
9           ----- YELLOW   
(^Any PWM Pin Works)

==========================*/

//45 - min degree
//135 - max degree
Servo_Wrapper myservo(45, 135);

int pos = 0;
void sweepservo()
{
  for (pos = 0; pos <= 180; pos += 1)
  {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1)
  {
    myservo.write(pos);
    delay(15);
  }
}

void setup() 
{
  //9 - signal pin, 
  //553 and 2520 - min/max PWM signal range 
  //from servocity.com
  myservo.attach(9, 553, 2520);
}

void loop() 
{
  sweepservo();
}