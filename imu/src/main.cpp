#include <Arduino.h>
#include <Wire.h>
#include <IMU_Wrapper.h>

IMU_Wrapper myImu;

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  myImu.begin();

  /* Display some basic information on this sensor */
  myImu.displaySensorDetails();

  /* Optional: Display current status */
  myImu.displaySensorStatus();
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
  /* Get a new sensor information */
  myImu.update();

  /* Display the floating point data */
  myImu.displayOrientation();

  /* Optional: Display calibration status */
  myImu.displayCalStatus();

  /* Optional: Display sensor status (debug only) */
  // myImu.displaySensorStatus();
}