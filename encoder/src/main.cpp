#include <Arduino.h>
#include <Wire.h>
#include <Encoder_Wrapper.h>

unsigned int twoPins[4] = {25, 23, 29, 27};
Encoder_Wrapper encoder(twoPins, 2);
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
  Serial.print("Total Number of Initialized Encoders: ");
  Serial.println(Encoder_Wrapper::getTotalSensorNum());

  for (size_t sensor = 0; sensor < encoder.getSensorNum(); sensor++)
  {
    Serial.print("getCount: ");
    Serial.println(encoder.getCount(sensor));
    encoder.setCount(-100, sensor);
    Serial.print("getCount: ");
    Serial.println(encoder.getCount(sensor));
    encoder.resetCount();
    Serial.print("getCount: ");
    Serial.println(encoder.getCount(sensor));
    Serial.print("getPin: ");
    Serial.print(encoder.getPin(sensor, 0));
    Serial.print(" ");
    Serial.println(encoder.getPin(sensor, 1));
  }

  for (size_t sensor = 0; sensor < encoders.getSensorNum(); sensor++)
  {
    Serial.print("getCount: ");
    Serial.println(encoders.getCount(sensor));
    encoders.setCount(100, sensor);
    Serial.print("getCount: ");
    Serial.println(encoders.getCount(sensor));
    encoders.resetCount();
    Serial.print("getCount: ");
    Serial.println(encoders.getCount(sensor));
    Serial.print("getPin: ");
    Serial.print(encoders.getPin(sensor, 0));
    Serial.print(" ");
    Serial.println(encoders.getPin(sensor, 1));
  }
  while (true)
    ;
}