#include <Arduino.h>
#include <Wire.h>
#include <Motor_Wrapper.h>

size_t motorNum = 2;
unsigned int motorPorts[2] = {Motor_Wrapper::SHIELD_M1, Motor_Wrapper::SHIELD_M3};
Motor_Wrapper motors(motorPorts, motorNum);

Encoder_Wrapper encoders;
const unsigned long INTERVAL_MS = 20;
const unsigned long COUNTS_PER_REV = 4560;

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

  const size_t encoderNum = 2;
  unsigned int encoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {44, 46, 48, 50};
  encoders.begin(encoderPins, encoderNum);

  for (size_t motor = 0; motor < motors.getMotorNum(); motor++)
  {
    for (uint8_t pwm = 0; pwm <= 100; pwm += 5)
    {
      encoders.resetCount();
      unsigned long lastTime = millis();
      motors.run(pwm, motor);
      delay(5000);
      unsigned long now = millis();
      motors.stop();
      double timeScaler = (double) INTERVAL_MS / (double) (now - lastTime);
      double countsPerTime = encoders.getCount(motor) * timeScaler * motors.getSpeedMultiplier(motor);
      Serial.print("pwm: ");
      Serial.print(pwm);
      Serial.print("\tCountsPerTime: ");
      Serial.print(countsPerTime);
      Serial.print("\n");
      delay(2000);
    }
    while (true)
      ;
  }
}

void loop() {}