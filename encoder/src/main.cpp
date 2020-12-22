#include <Arduino.h>
#include <Wire.h>
#include <Encoder_Wrapper.h>

void setup() 
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);

  size_t sensorNum = 3;
  unsigned int newEncoderPins[sensorNum * Encoder_Wrapper::PINS_PER_SENSOR] = {25, 23, 29, 27, 31, 33};
  Encoder_Wrapper newEncoders(newEncoderPins, sensorNum);
  unsigned int mixedEncoderPins[sensorNum * Encoder_Wrapper::PINS_PER_SENSOR] = {31, 33, 46, 44, 50, 48};
  Encoder_Wrapper mixedEncoders(mixedEncoderPins, sensorNum);
  unsigned int repeatedEncoderPins[sensorNum * Encoder_Wrapper::PINS_PER_SENSOR] = {29, 27, 25, 23, 46, 44};
  Encoder_Wrapper repeatedEncoders(repeatedEncoderPins, sensorNum);

  Serial.print("Total Number of Initialized Encoders: ");
  Serial.println(Encoder_Wrapper::getTotalSensorNum());

  for (size_t sensor = 0; sensor < newEncoders.getSensorNum(); sensor++)
  {
    Serial.print("newEncoders getCount: ");
    Serial.println(newEncoders.getCount(sensor));
    newEncoders.setCount(sensor, -100);
    Serial.print("newEncoders getCount: ");
    Serial.println(newEncoders.getCount(sensor));
    newEncoders.resetCount();
    Serial.print("newEncoders getCount: ");
    Serial.println(newEncoders.getCount(sensor));
    Serial.print("newEncoders getPin: ");
    Serial.print(newEncoders.getPin(sensor, Encoder_Wrapper::ENCODER_OUT_A));
    Serial.print(" ");
    Serial.println(newEncoders.getPin(sensor, Encoder_Wrapper::ENCODER_OUT_B));
  }
  for (size_t sensor = 0; sensor < mixedEncoders.getSensorNum(); sensor++)
  {
    Serial.print("mixedEncoders getCount: ");
    Serial.println(mixedEncoders.getCount(sensor));
    mixedEncoders.setCount(sensor, 100);
    Serial.print("mixedEncoders getCount: ");
    Serial.println(mixedEncoders.getCount(sensor));
    mixedEncoders.resetCount();
    Serial.print("mixedEncoders getCount: ");
    Serial.println(mixedEncoders.getCount(sensor));
    Serial.print("mixedEncoders getPin: ");
    Serial.print(mixedEncoders.getPin(sensor, Encoder_Wrapper::ENCODER_OUT_A));
    Serial.print(" ");
    Serial.println(mixedEncoders.getPin(sensor, Encoder_Wrapper::ENCODER_OUT_B));
  }
  for (size_t sensor = 0; sensor < repeatedEncoders.getSensorNum(); sensor++)
  {
    Serial.print("repeatedEncoders getCount: ");
    Serial.println(repeatedEncoders.getCount(sensor));
    repeatedEncoders.setCount(sensor, -100);
    Serial.print("repeatedEncoders getCount: ");
    Serial.println(repeatedEncoders.getCount(sensor));
    repeatedEncoders.resetCount();
    Serial.print("repeatedEncoders getCount: ");
    Serial.println(repeatedEncoders.getCount(sensor));
    Serial.print("repeatedEncoders getPin: ");
    Serial.print(repeatedEncoders.getPin(sensor, Encoder_Wrapper::ENCODER_OUT_A));
    Serial.print(" ");
    Serial.println(repeatedEncoders.getPin(sensor, Encoder_Wrapper::ENCODER_OUT_B));
  }
}

void loop(){};