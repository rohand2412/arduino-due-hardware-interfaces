#include <Arduino.h>
#include <Wire.h>
#include <Ultrasonic_Wrapper.h>

unsigned int echoPins[4] = {53, 51, 49, 47};
Ultrasonic_Wrapper ultrasonics(52, echoPins, 20, 4);

void ultrasonicFrontEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_FRONT); }

void ultrasonicLeftEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_LEFT); }

void ultrasonicRightEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_RIGHT); }

void ultrasonicBackEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_BACK); }

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  delay(300);

  void (*ultrasonicISR[4])() = {ultrasonicFrontEchoPinISR,
                                ultrasonicLeftEchoPinISR, 
                                ultrasonicRightEchoPinISR, 
                                ultrasonicBackEchoPinISR};
  ultrasonics.begin(ultrasonicISR);
}

void loop() {
  ultrasonics.update();
  Serial.print("Front: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_FRONT));
  Serial.print("\tLeft: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_LEFT));
  Serial.print("\tRight: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_RIGHT));
  Serial.print("\tBack: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_BACK));
  Serial.print("\n");
}