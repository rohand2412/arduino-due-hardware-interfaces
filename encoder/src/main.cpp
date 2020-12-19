#include <Arduino.h>
#include <Wire.h>
#include <Encoder_Wrapper.h>

unsigned int twoPins[2] = {50, 48};
Encoder_Wrapper encoder(twoPins, 1);
unsigned int fourPins[4] = {46, 44, 50, 48};
Encoder_Wrapper encoders(fourPins, 2);

void setup() 
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);
}

void loop() 
{
  Serial.println(encoders.getCount(0));
  Serial.println(encoders.getCount(1));
  encoders.setCount(100, 0);
  encoders.setCount(200, 1);
  Serial.println(encoders.getCount(0));
  Serial.println(encoders.getCount(1));
  encoders.resetCount();
  Serial.println(encoders.getCount(0));
  Serial.println(encoders.getCount(1));
  Serial.println(encoders.getPin(0, 0));
  Serial.println(encoders.getPin(0, 1));
  Serial.println(encoders.getPin(1, 0));
  Serial.println(encoders.getPin(1, 1));
  while (true)
    ;
}