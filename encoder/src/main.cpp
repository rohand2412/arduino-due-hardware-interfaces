#include <Arduino.h>
#include <Wire.h>
#include <Encoder_Wrapper.h>

unsigned int twoPins[2] = {25, 23};
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
  Serial.println(encoder.getCount());
  Serial.println(encoders.getCount(0));
  Serial.println(encoders.getCount(1));
  encoder.setCount(-100, 0);
  encoders.setCount(100, 0);
  encoders.setCount(200, 1);
  Serial.println(encoder.getCount());
  Serial.println(encoders.getCount(0));
  Serial.println(encoders.getCount(1));
  encoder.resetCount();
  encoders.resetCount();
  Serial.println(encoder.getCount());
  Serial.println(encoder.getPin(0, 0));
  Serial.println(encoder.getPin(0, 1));
  Serial.println(encoders.getCount(0));
  Serial.println(encoders.getCount(1));
  Serial.println(encoders.getPin(0, 0));
  Serial.println(encoders.getPin(0, 1));
  Serial.println(encoders.getPin(1, 0));
  Serial.println(encoders.getPin(1, 1));
  while (true)
    ;
}