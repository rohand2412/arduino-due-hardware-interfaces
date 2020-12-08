#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
Servo myservo;
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
  myservo.attach(9, 553, 2520);
}

void loop() 
{
  sweepservo();
}