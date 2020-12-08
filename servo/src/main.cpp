#include <Arduino.h>
#include <Wire.h>
#include <Servo_Wrapper.h>
Servo_Wrapper myservo;
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
  myservo.setBounds(45, 135);
}

void loop() 
{
  sweepservo();
}