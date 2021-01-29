#include <Arduino.h>
#include <Wire.h>
#include <Servo_Wrapper.h>

/*==========================

Arduino Due -----  Servo
5V          -----    RED
GND         -----  BLACK
9           ----- YELLOW   
(^Any PWM Pin Works)

==========================*/

const unsigned int LOWER_BOUND = 45;
const unsigned int UPPER_BOUND = 135;
const unsigned int BOUND_DIF = UPPER_BOUND - LOWER_BOUND;
Servo_Wrapper myservo(LOWER_BOUND, UPPER_BOUND);

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

  //510 and 2520 - min/max PWM signal range 
  //myservo.attach(Servo_Wrapper::SERVO_S1, 510, 2520);

  myservo.attach(Servo_Wrapper::SERVO_S2);
}

void loop() 
{
  //sweepservo();
  myservo.write(15);
}

//Line - 35 deg
//Evac - 15 deg