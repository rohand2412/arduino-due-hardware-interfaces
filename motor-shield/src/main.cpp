#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_MS_PWMServoDriver.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *Motorone = AFMS.getMotor(1);
Adafruit_DCMotor *Motortwo = AFMS.getMotor(1);


void setup() 
{
  AFMS.begin();
}

void runmotor(int speedone, int speedtwo)
{
  bool negone;
  bool negtwo;
  if(speedone <= -255 || speedone >= 255)
  {
    if(speedone <= -255)
    {
      speedone = -255;
    }
    else
    {
      speedone = 255;
    }
  }
  if(speedtwo <= -255 || speedtwo >= 255)
  {
    if(speedtwo <= -255)
    {
      speedtwo = -255;
    }
    else
    {
      speedtwo = 255;
    }
  }
  if(speedone<= 0)
  {
    if(speedone == 0)
    {
      Motorone->setSpeed(0);
      Motorone->run(RELEASE);
    }
    else
    {
      negone = true;
    }
  }
  if(speedtwo <= 0)
  {
    if(speedone == 0)
    {
      Motortwo->setSpeed(0);
      Motortwo->run(RELEASE);
    }
    else
    {
      negtwo = true;
    }
  }
  if(negone)
  {
    Motortwo->setSpeed(speedone);
    Motortwo->run(BACKWARD);
  }
  else if(!negone)
  {
    Motortwo->setSpeed(speedone);
    Motortwo->run(FORWARD);
  }
  if(negtwo)
  {
    Motortwo->setSpeed(speedtwo);
    Motortwo->run(BACKWARD);
  }
  else if(!negtwo)
  {
    Motortwo->setSpeed(speedtwo);
    Motortwo->run(FORWARD);
  }
}
void loop() 
{
  runmotor(-20, 20);
}