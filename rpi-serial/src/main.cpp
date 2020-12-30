#include <Arduino.h>

void setup() 
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(300);

  Serial3.begin(115200);
  while (!Serial3)
    ;
  delay(300);
}

void loop() 
{
  if (Serial3.available())
  {
    Serial.println(Serial3.read());
  }
}