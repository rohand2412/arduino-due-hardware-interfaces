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
Servo_Wrapper myservo(58, 138);

int pos = 0;
void sweepservo()
{
  for (pos = 0; pos <= 80; pos += 1)
  {
    myservo.write(pos);
    Serial.println(myservo.read());
    delay(30);
  }
  for (pos = 80; pos >= 0; pos -= 1)
  {
    myservo.write(pos);
    Serial.println(myservo.read());
    delay(30);
  }
  delay(300);
}

void setup() 
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);
  //9 - signal pin, 
  //553 and 2520 - min/max PWM signal range 
  //from servocity.com
  myservo.attach(10, 510, 2520);
}

void loop() 
{
  sweepservo();
}