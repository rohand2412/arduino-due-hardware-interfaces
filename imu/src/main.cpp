#include <Arduino.h>
#include <Wire.h>
#include <IMU_Wrapper.h>

IMU_Wrapper myImu(43);

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  adafruit_bno055_offsets_t offsets{13, -48, -25,
                                    -101, 127, 438,
                                    -2, -2, 0,
                                    1000, 835};
  myImu.setOffsets(offsets);

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