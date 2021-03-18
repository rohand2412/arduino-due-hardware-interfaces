#include <Arduino.h>
#include <Wire.h>
#include <Motor_Wrapper.h>

size_t motorNum = 2;
unsigned int motorPorts[2] = {Motor_Wrapper::SHIELD_M1, Motor_Wrapper::SHIELD_M3};
Motor_Wrapper motors(motorPorts, motorNum);

Encoder_Wrapper encoders;

bool stopped = false;
unsigned long stopped_ms = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);

  {
    unsigned int encoderPins[motorNum * Encoder_Wrapper::PINS_PER_SENSOR] = {46, 44, 50, 48};
    motors.setEncoders(encoderPins);
    unsigned int localEncoderPins[motorNum * Encoder_Wrapper::PINS_PER_SENSOR] = {46, 44, 50, 48};
    encoders.createSensor(localEncoderPins, 2);
  }

  motors.setPid(0.8, 0.75, 0, Motor_Wrapper::MOTOR_LEFT);
  motors.setPid(0.85, 0.8, 0, Motor_Wrapper::MOTOR_RIGHT);
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

  switch (millis())
  {
      case 7500 ... 11000:
          motors.stop();
          break;
      case 11001 ... 11020:
          motors.start();
          break;
      case 15000 ... 15500:
          motors.setSpeed(0, Motor_Wrapper::MOTOR_ALL);
          break;
      case 18001 ... 18020:
          motors.start();
          break;
      case 20001 ... 20020:
          motors.setSpeed(0.5, Motor_Wrapper::MOTOR_ALL);
          break;
      case 22000 ... 22020:
          motors.run(-0.5);
          break;
  }

  if (millis() < 10000)
  {
      encoders.resetCount();
  }

  double rightActualSpeed = motors.getActualSpeed(Motor_Wrapper::MOTOR_RIGHT);
  double leftActualSpeed = motors.getActualSpeed(Motor_Wrapper::MOTOR_LEFT);
  double rightOutput = motors.getOutput(Motor_Wrapper::MOTOR_RIGHT);
  double leftOutput = motors.getOutput(Motor_Wrapper::MOTOR_LEFT);
  double rightInput = motors.getInput(Motor_Wrapper::MOTOR_RIGHT);
  double leftInput = motors.getInput(Motor_Wrapper::MOTOR_LEFT);

  Serial.print(leftActualSpeed);
  Serial.print("\t");
  Serial.print(rightActualSpeed);
  Serial.print("\t");
  Serial.print(leftInput);
  Serial.print("\t");
  Serial.print(rightInput);
  Serial.print("\t");
  Serial.print(leftOutput);
  Serial.print("\t");
  Serial.print(rightOutput);
  Serial.print("\t");
  Serial.print(encoders.getCount(Encoder_Wrapper::ENCODER_LEFT));
  Serial.print("\t");
  Serial.print(encoders.getCount(Encoder_Wrapper::ENCODER_RIGHT));
  Serial.print("\t");
  Serial.print(millis());
  Serial.print("\n");
}