#include <Arduino.h>
#include <Wire.h>
#include <Servo_Wrapper.h>
#include <Motor_Wrapper.h>

/*==========================

Arduino Due -----  Servo
5V          -----    RED
GND         -----  BLACK
9           ----- YELLOW   
(^Any PWM Pin Works)

==========================*/

size_t motorNum = 2;
unsigned int motorPorts[2] = {Motor_Wrapper::SHIELD_M1, Motor_Wrapper::SHIELD_M3};
Motor_Wrapper motors(motorPorts, motorNum);

const unsigned int LOWER_BOUND = 35;
const unsigned int UPPER_BOUND = 140;
const unsigned int BOUND_DIF = UPPER_BOUND - LOWER_BOUND;
Servo_Wrapper myservo(LOWER_BOUND, UPPER_BOUND);
Servo_Wrapper camServo(47, 137);

unsigned int pos = 0;
void sweepservo()
{
  for (pos = 0; pos <= BOUND_DIF; pos += 1)
  {
    myservo.write(pos);
    Serial.println(myservo.read());
    delay(30);
  }
  for (pos = BOUND_DIF; pos <= BOUND_DIF && pos >= 0; pos -= 1)
  {
    myservo.write(pos);
    Serial.println(myservo.read());
    delay(30);
  }
  delay(300);
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

  motors.setPid(0.8, 0.75, 0, 0.75, 0.7, 0, Motor_Wrapper::MOTOR_LEFT);
  motors.setPid(0.85, 0.8, 0, 0.8, 0.75, 0, Motor_Wrapper::MOTOR_RIGHT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_FLIP, Motor_Wrapper::MOTOR_LEFT);
  motors.setSpeedMultiplier(Motor_Wrapper::MOTOR_NO_FLIP, Motor_Wrapper::MOTOR_RIGHT);

  motors.begin();

  //510 and 2520 - min/max PWM signal range 
  myservo.attach(Servo_Wrapper::SERVO_S1, 510, 2520);
  myservo.write(85);
  camServo.attach(Servo_Wrapper::SERVO_S2);
  camServo.write(15);

  //   myservo.attach(Servo_Wrapper::SERVO_S2);
  delay(2000);
}

unsigned long DELAY_MS = 4000;
unsigned long lastTimeMotor;
bool startedRun = false;
bool alreadyRun = false;
int increment = -1;

unsigned long INTERVAL_MS = 20;
unsigned long lastTimeServo = millis() - INTERVAL_MS;
unsigned int slam_counter = 0;

void loop() 
{
    motors.update();

    if (millis() >= lastTimeServo + INTERVAL_MS)
    {
        myservo.write(myservo.read() + increment);
        if (myservo.read() > 85)
        {
            if (!(slam_counter % 3))
            {
                INTERVAL_MS = 20;
            }
            else
            {
                INTERVAL_MS = 0;
            }
            slam_counter++;
            increment = -1;
            delay(500);
        }
        else if (myservo.read() <= 0)
        {
            INTERVAL_MS = 20;
            increment = 1;
            delay(500);
        }
        
        lastTimeServo = millis();
    }

    // if (deg <= 30 && !startedRun && !alreadyRun)
    // {
    //     motors.run(-0.25);
    //     lastTimeMotor = millis();
    //     startedRun = true;
    // }

    // if ((millis() >= lastTimeMotor + DELAY_MS) && !alreadyRun && startedRun)
    // {
    //     motors.stop();
    //     delay(2000);
    //     myservo.write(85);
    //     startedRun = false;
    //     alreadyRun = true;
    // }
}
