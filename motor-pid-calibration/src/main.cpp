#include <Arduino.h>
#include <Wire.h>
#include <Motor_Wrapper.h>

const size_t motorNum = 2;
unsigned int motorPorts[2] = {Motor_Wrapper::SHIELD_M1, Motor_Wrapper::SHIELD_M3};
Motor_Wrapper motors(motorPorts, motorNum);

float proportionalCoefficients[motorNum] = {1, 1};
float integralCoefficients[motorNum] = {0, 0};
float derivativeCoefficients[motorNum] = {0, 0};

const float targetSpeed = -0.5;
const size_t bufferLen = 10;
const size_t bufferNum = 3;
size_t currentBuffer[motorNum] = {0, 0};
float actualSpeeds[bufferLen * bufferNum * motorNum];
size_t actualSpeedsLen[motorNum];
float actualSpeedAvgs[bufferNum * motorNum];

float coefficientGain[motorNum] = {10, 10};
int gainDirection[bufferNum] = {0, -1, 1};
unsigned int updateThreshold = 100;
unsigned int currentUpdateNum = 0;

void clear(float* buffer, size_t startLen, size_t endLen)
{
  for (size_t item = startLen; item < endLen; item++)
  {
    buffer[item] = 0;
  }
}

void clear(size_t* buffer, size_t startLen, size_t endLen)
{
  for (size_t item = startLen; item < endLen; item++)
  {
    buffer[item] = 0;
  }
}

void reset()
{
  motors.stop();
  motors.setSpeed(0, Motor_Wrapper::MOTOR_ALL);
  motors.resetCount();
  currentUpdateNum = 0;
}

float average(float* buffer, size_t startLen, size_t endLen)
{
  float sum = 0;
  for (size_t item = startLen; item < endLen; item++)
  {
    sum += buffer[item];
  }
  return sum / (endLen - startLen);
}

size_t minIndex(float* buffer, size_t startLen, size_t endLen)
{
  float minVal = 100000000;
  size_t indexNum = 0;

  for (size_t item = startLen; item < endLen; item++)
  {
    float absItem = buffer[item] < 0 ? -buffer[item] : buffer[item];
    if (absItem < minVal)
    {
      minVal = absItem;
      indexNum = item;
    }
  }

  return indexNum;
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);

  {
    unsigned int encoderPins[motorNum * Encoder_Wrapper::PINS_PER_SENSOR] = {46, 44, 50, 48};
    motors.setEncoders(encoderPins);
  }

  motors.setPid(proportionalCoefficients, integralCoefficients, derivativeCoefficients);

  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_FLIP, Motor_Wrapper::MOTOR_LEFT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_NO_FLIP, Motor_Wrapper::MOTOR_RIGHT);

  motors.begin();

  clear(actualSpeeds, 0, bufferLen * bufferNum * motorNum);
  clear(actualSpeedsLen, 0, motorNum);
  clear(actualSpeedAvgs, 0, bufferNum * motorNum);
}

void loop()
{
  motors.run(targetSpeed);
  motors.update();

  bool justUpdated = motors.getJustUpdated();
  for (size_t motor = 0; motor < motorNum; motor++)
  {
    if (justUpdated)
    {
      if (currentUpdateNum >= updateThreshold)
      {
        if (currentBuffer[motor] < bufferNum && actualSpeedsLen[motor] < bufferLen)
        {
          size_t actualSpeedsIndex = motor * bufferNum * bufferLen + currentBuffer[motor] * bufferLen + actualSpeedsLen[motor];
          actualSpeeds[actualSpeedsIndex] = motors.getActualSpeed(motor);
          actualSpeedsLen[motor]++;
        }
        if (actualSpeedsLen[motor] >= bufferLen)
        {
          size_t startIndex = motor * bufferNum * bufferLen + currentBuffer[motor] * bufferLen;
          actualSpeedAvgs[motor * bufferNum + currentBuffer[motor]] = average(actualSpeeds, startIndex, startIndex + bufferLen);
          actualSpeedsLen[motor] = 0;
          currentBuffer[motor]++;

          if (currentBuffer[motor] < bufferNum)
          {
            float proportional = proportionalCoefficients[motor] + coefficientGain[motor] * gainDirection[currentBuffer[motor]];
            motors.setPid(proportional, integralCoefficients[motor], derivativeCoefficients[motor], motor);
            reset();
          }
        }
        if (currentBuffer[motor] >= bufferNum)
        {
          float errors[bufferNum];
          for (size_t buffer = 0; buffer < bufferNum; buffer++)
          {
            errors[buffer] = targetSpeed - actualSpeedAvgs[motor * bufferNum + buffer];
          }

          int direction = gainDirection[minIndex(errors, 0, bufferNum)];
          proportionalCoefficients[motor] += coefficientGain[motor] * direction;
          coefficientGain[motor] /= 2;

          currentBuffer[motor] = 0;
          actualSpeedsLen[motor] = 0;

          size_t startIndex = motor * bufferNum * bufferLen;
          clear(actualSpeeds, startIndex, startIndex + bufferNum * bufferLen);
          startIndex = motor * bufferNum;
          clear(actualSpeedAvgs, startIndex, startIndex + bufferNum);

          float proportional = proportionalCoefficients[motor] + coefficientGain[motor] * gainDirection[currentBuffer[motor]];
          motors.setPid(proportional, integralCoefficients[motor], derivativeCoefficients[motor], motor);
          reset();
        }
      }
      currentUpdateNum++;
    }
  }

  if (coefficientGain[Motor_Wrapper::MOTOR_LEFT] < 0.001 || coefficientGain[Motor_Wrapper::MOTOR_RIGHT] < 0.001)
  {
    Serial.print("\n\n\n\n\n\n");
    Serial.print("Left Coefficents: ");
    Serial.print(proportionalCoefficients[Motor_Wrapper::MOTOR_LEFT]);
    Serial.print("\t");
    Serial.print(integralCoefficients[Motor_Wrapper::MOTOR_LEFT]);
    Serial.print("\t");
    Serial.print(derivativeCoefficients[Motor_Wrapper::MOTOR_LEFT]);
    Serial.print("\n");
    Serial.print("Right Coefficients: ");
    Serial.print(proportionalCoefficients[Motor_Wrapper::MOTOR_RIGHT]);
    Serial.print("\t");
    Serial.print(integralCoefficients[Motor_Wrapper::MOTOR_RIGHT]);
    Serial.print("\t");
    Serial.print(derivativeCoefficients[Motor_Wrapper::MOTOR_RIGHT]);
    Serial.print("\n");

    while(true)
      ;
  }
}