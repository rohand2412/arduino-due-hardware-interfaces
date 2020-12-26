#include <Arduino.h>
#include <Wire.h>
#include <Motor_Wrapper.h>

size_t motorNum = 2;
unsigned int motorPorts[2] = {Motor_Wrapper::SHIELD_M1, Motor_Wrapper::SHIELD_M3};
Motor_Wrapper motors(motorPorts, motorNum);

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

  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_FLIP, Motor_Wrapper::MOTOR_LEFT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_NO_FLIP, Motor_Wrapper::MOTOR_RIGHT);

  motors.begin();

  motors.run(20);
}

void loop() {}