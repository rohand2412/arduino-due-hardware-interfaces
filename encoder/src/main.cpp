#include <Arduino.h>
#include <Wire.h>
#include <Encoder_Wrapper.h>

void setup() 
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);

  size_t encoderNum = 3;
  size_t wrapperNum = 3;
  Encoder_Wrapper encoders[wrapperNum];
  unsigned int newEncoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {25, 23, 29, 27, 31, 33};
  encoders[0].begin(newEncoderPins, encoderNum);
  unsigned int mixedEncoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {31, 33, 46, 44, 50, 48};
  encoders[1].begin(mixedEncoderPins, encoderNum);
  unsigned int repeatedEncoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {29, 27, 25, 23, 46, 44};
  encoders[2].begin(repeatedEncoderPins, encoderNum);

  Serial.print("Total Number of Initialized Encoders: ");
  Serial.println(Encoder_Wrapper::getTotalSensorNum());

  for (size_t wrapper = 0; wrapper < wrapperNum; wrapper++)
  {
    for (size_t sensor = 0; sensor < encoders[wrapper].getSensorNum(); sensor++)
    {
      Serial.print("encoders getCount: ");
      Serial.println(encoders[wrapper].getCount(sensor));
      encoders[wrapper].setCount(sensor, -100);
      Serial.print("encoders getCount: ");
      Serial.println(encoders[wrapper].getCount(sensor));
      encoders[wrapper].resetCount();
      Serial.print("encoders getCount: ");
      Serial.println(encoders[wrapper].getCount(sensor));
      Serial.print("encoders getPin: ");
      Serial.print(encoders[wrapper].getPin(sensor, Encoder_Wrapper::ENCODER_OUT_A));
      Serial.print(" ");
      Serial.println(encoders[wrapper].getPin(sensor, Encoder_Wrapper::ENCODER_OUT_B));
    }
  }
}

void loop(){};