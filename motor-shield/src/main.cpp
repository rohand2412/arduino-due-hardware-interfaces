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

  motors.setPid(3.5, 10, 0, Motor_Wrapper::MOTOR_LEFT);
  motors.setPid(3.5, 10, 0, Motor_Wrapper::MOTOR_RIGHT);
  motors.setPid(1, 2.5, 0.15, Motor_Wrapper::MOTOR_DIF);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_FLIP, Motor_Wrapper::MOTOR_LEFT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_NO_FLIP, Motor_Wrapper::MOTOR_RIGHT);

  motors.begin();

  for (size_t motor = 0; motor < motors.getMotorNum(); motor++)
  {
    Serial.print("motor id: ");
    Serial.println(motor);
    Serial.print("speedMultiplier: ");
    Serial.println(motors.getSpeedMultiplier(motor));
    Serial.print("speed: ");
    Serial.println(motors.getSpeed(motor));
    Serial.print("state: ");
    Serial.println(motors.getState(motor));
    Serial.print("Encoder OUT_A: ");
    Serial.println(motors.getEncoderPin(motor, Encoder_Wrapper::ENCODER_OUT_A));
    Serial.print("Encoder OUT_B: ");
    Serial.println(motors.getEncoderPin(motor, Encoder_Wrapper::ENCODER_OUT_B));
  }

  delay(2000);

  motors.run(0.5);
}

void loop()
{
  motors.update();

  long int rightCount = motors.getUpdateCounts(Motor_Wrapper::MOTOR_RIGHT);
  long int leftCount = motors.getUpdateCounts(Motor_Wrapper::MOTOR_LEFT);
  double rightActualSpeed = motors.getActualSpeed(Motor_Wrapper::MOTOR_RIGHT);
  double leftActualSpeed = motors.getActualSpeed(Motor_Wrapper::MOTOR_LEFT);
  unsigned int rightElapsedTime = motors.getElapsedCorrectedTime_MS(Motor_Wrapper::MOTOR_RIGHT);
  unsigned int leftElapsedTime = motors.getElapsedCorrectedTime_MS(Motor_Wrapper::MOTOR_LEFT);

  Serial.print("Left Count: ");
  Serial.print(leftCount);
  Serial.print("\t right count: ");
  Serial.print(rightCount);
  Serial.print("\t Left Actual Speed: ");
  Serial.print(leftActualSpeed);
  Serial.print("\tRight Actual Speed: ");
  Serial.print(rightActualSpeed);
  Serial.print("\tLeft Elapsed Time: ");
  Serial.print(leftElapsedTime);
  Serial.print("\tRight Elapsed Time: ");
  Serial.print(rightElapsedTime);
  Serial.print("\n");
}