#include <Arduino.h>
#include <Wire.h>
#include <Encoder_Wrapper.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
unsigned int pins[4] = {46, 44, 50, 48};
Encoder_Wrapper encoders(pins, 2);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);
  Serial.println("TwoKnobs Encoder Test:");
}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  long newLeft, newRight;
  newLeft = encoders.getCount(0);
  newRight = encoders.getCount(1);
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    encoders.resetCount();
  }
}