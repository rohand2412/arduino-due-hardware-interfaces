#include <Arduino.h>

const uint8_t buttonPin = 40;
bool buttonState = false;
bool dormantState = false;
unsigned int updateCounter = 0;
const unsigned long debounceDelay = 30;
volatile unsigned long lastDebounce = millis() - debounceDelay;

void buttonISR()
{
  lastDebounce = millis();
}

void setup() {
  Serial.begin(115200);

  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, CHANGE);
}

void loop()
{
  bool curButtonState = digitalRead(buttonPin);

  if ((millis() - lastDebounce) > debounceDelay)
  {
    if (curButtonState != buttonState)
    {
      buttonState = curButtonState;

      if (buttonState == HIGH) {
        dormantState = !dormantState;
        updateCounter++;
      }
    }
  }

  Serial.print(dormantState);
  Serial.print("\t");
  Serial.print(updateCounter);
  Serial.print("\t");
  Serial.println(curButtonState);
}