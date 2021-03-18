#include <Arduino.h>
#include <Wire.h>
#include <Motor_Wrapper.h>
#include <Serial_Wrapper.h>

const size_t packetLen = 2;
long packet[packetLen];

size_t motorNum = 2;
unsigned int motorPorts[2] = {Motor_Wrapper::SHIELD_M1, Motor_Wrapper::SHIELD_M3};
Motor_Wrapper motors(motorPorts, motorNum);

Encoder_Wrapper encoders;
const unsigned long INTERVAL_MS = 20;
const unsigned long COUNTS_PER_REV = 4560;

void setup()
{
  Serial_Wrapper::begin(750000, Serial);

  Serial_Wrapper::begin(115200, Serial3);
  Serial_Wrapper::setDefault(Serial3);

  {
    unsigned int encoderPins[motorNum * Encoder_Wrapper::PINS_PER_SENSOR] = {46, 44, 50, 48};
    motors.setEncoders(encoderPins);
  }

  motors.setPid(0.8, 0.75, 0, Motor_Wrapper::MOTOR_LEFT);
  motors.setPid(0.85, 0.8, 0, Motor_Wrapper::MOTOR_RIGHT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_FLIP, Motor_Wrapper::MOTOR_LEFT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_NO_FLIP, Motor_Wrapper::MOTOR_RIGHT);

  motors.begin();

  const size_t encoderNum = 2;
  unsigned int encoderPins[encoderNum * Encoder_Wrapper::PINS_PER_SENSOR] = {44, 46, 48, 50};
  encoders.createSensor(encoderPins, encoderNum);
}

void loop()
{
  for (size_t motor = 1; motor < motors.getMotorNum(); motor++)
  {
    //Change bounds in intervals to prevent wire twisting
    for (uint8_t pwm = 0; pwm <= 100; pwm += 5)
    {
      encoders.resetCount();
      motors.setPwm(pwm, motor);
      unsigned long lastTime = millis();
      motors.start();
      while (millis() - lastTime <= 5000)
      {
          motors.update();
      }
      unsigned long now = millis();
      motors.stop();
      double timeScaler = (double) INTERVAL_MS / (double) (now - lastTime);
      double countsPerTime = encoders.getCount(motor) * timeScaler * motors.getSpeedMultiplier(motor);
      packet[0] = pwm;
      packet[1] = static_cast <long> (100 * countsPerTime);
      Serial_Wrapper::send(packet, packetLen);
      Serial.print(packet[0]);
      Serial.print("\t");
      Serial.println(packet[1]);
      delay(2000);
    }
    while (true)
      ;
  }
}