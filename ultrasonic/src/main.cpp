#include <Arduino.h>
#include <Wire.h>
#include <Ultrasonic_Wrapper.h>

unsigned int echoPins[5] = {53, 51, 49, 47, 33};
Ultrasonic_Wrapper ultrasonics(52, echoPins, 20, 5);

void ultrasonicFrontEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_FRONT); }

void ultrasonicLeftEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_LEFT); }

void ultrasonicRightEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_RIGHT); }

void ultrasonicBackEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_BACK); }

void ultrasonicTopEchoPinISR() { ultrasonics.echoPinISR(Ultrasonic_Wrapper::ULTRASONIC_TOP); }

void setup() 
{
  Serial.begin(115200);
  while (!Serial);
  delay(300);

  void (*ultrasonicISR[5])() = {ultrasonicFrontEchoPinISR,
                                ultrasonicLeftEchoPinISR, 
                                ultrasonicRightEchoPinISR, 
                                ultrasonicBackEchoPinISR,
                                ultrasonicTopEchoPinISR};
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
  Serial.print("\tTop: ");
  Serial.print(ultrasonics.getDistance(Ultrasonic_Wrapper::ULTRASONIC_TOP));
  Serial.print("\n");
}