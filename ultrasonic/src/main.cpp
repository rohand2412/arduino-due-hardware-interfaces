#include <Arduino.h>
#include <Wire.h>
#include <Ultrasonic_Wrapper.h>

unsigned int echoPins[4] = {53, 51, 49, 47};
Ultrasonic_Wrapper ultrasonics(52, echoPins, 20, 4);

void ultrasonicFrontEchoPinISR() { ultrasonics.echoPinISR(0); }

void ultrasonicLeftEchoPinISR() { ultrasonics.echoPinISR(1); }

void ultrasonicRightEchoPinISR() { ultrasonics.echoPinISR(2); }

void ultrasonicBackEchoPinISR() { ultrasonics.echoPinISR(3); }

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
  Serial.print(ultrasonics.getDistance(0));
  Serial.print("\tLeft: ");
  Serial.print(ultrasonics.getDistance(1));
  Serial.print("\tRight: ");
  Serial.print(ultrasonics.getDistance(2));
  Serial.print("\tBack: ");
  Serial.print(ultrasonics.getDistance(3));
  Serial.print("\n");
}