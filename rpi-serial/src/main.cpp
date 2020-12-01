#include <Arduino.h>
char incomingByte;
int mspeedone = 0;
int mspeedtwo = 0;
void setup() 
{
  Serial.begin(57600);
}

void loop() 
{
  if((incomingByte = Serial.read()) == '<')
  {
    bool firstneg = false;
    bool secondneg = false;
    while((incomingByte = Serial.read()) != ',')
    {
      if(incomingByte == '-')
      {
        firstneg = true;
      }
      else if(incomingByte < '0' && incomingByte > '0')
      {
        mspeedone = (mspeedone*10) + (incomingByte - '0');
      }
    }
    while((incomingByte = Serial.read()) != '>')
    {
      if(incomingByte == '-')
      {
        secondneg = true;
      }
      else if(incomingByte < '0' && incomingByte > '0')
      {
        mspeedone = (mspeedtwo*10) + (incomingByte - '0');
      }
    }
    if(firstneg)
    {
      mspeedone = mspeedone * (-1);
    }
    if(secondneg)
    {
      mspeedtwo = mspeedtwo * (-1);
    }
  }
}