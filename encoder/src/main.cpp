#include <Arduino.h>
#include <Wire.h>
#include <Encoder_Wrapper.h>

bool once = true;
Encoder_Wrapper totalEncoders;
Encoder_Wrapper localEncoders;

void setup() 
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);

  const size_t encoderNum = 3;
  const size_t wrapperNum = 3;
  Encoder_Wrapper encoders[wrapperNum];
  unsigned int newEncoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {25, 23, 29, 27, 31, 33};
  encoders[0].begin(newEncoderPins, encoderNum);
  unsigned int mixedEncoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {33, 31, 46, 44, 50, 48};
  encoders[1].begin(mixedEncoderPins, encoderNum);
  unsigned int repeatedEncoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {29, 27, 25, 23, 44, 46};
  encoders[2].begin(repeatedEncoderPins, encoderNum);

  Serial.print("Total Number of Initialized Encoders: ");
  Serial.println(Encoder_Wrapper::getTotalSensorNum());

  for (size_t wrapper = 0; wrapper < wrapperNum; wrapper++)
  {
    for (size_t sensor = 0; sensor < encoders[wrapper].getSensorNum(); sensor++)
    {
      if (sensor == encoders[wrapper].getSensorNum() - 1)
      {
        //Check for index capping functionality
        sensor++;
      }
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
      //Check for index capping functionality
      Serial.println(encoders[wrapper].getPin(sensor, Encoder_Wrapper::ENCODER_OUT_B + 1));
    }
  }

  delay(2000);
}

void loop()
{
  if (once)
  {
    const size_t encoderNum = 2;
    unsigned int totalEncoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {46, 44, 50, 48};
    unsigned int localEncoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {44, 46, 48, 50};
    totalEncoders.begin(totalEncoderPins, encoderNum);
    localEncoders.begin(localEncoderPins, encoderNum);
    once = false;
  }

  Serial.print("localEncoders: Left: ");
  Serial.print(localEncoders.getCount(Encoder_Wrapper::ENCODER_LEFT));
  Serial.print("\tRight: ");
  Serial.print(localEncoders.getCount(Encoder_Wrapper::ENCODER_RIGHT));
  Serial.print("\ttotalEncoders: Left: ");
  Serial.print(totalEncoders.getCount(Encoder_Wrapper::ENCODER_LEFT));
  Serial.print("\tRight: ");
  Serial.print(totalEncoders.getCount(Encoder_Wrapper::ENCODER_RIGHT));
  Serial.print("\n");

  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset localEncoders");
    localEncoders.resetCount();
  }
}