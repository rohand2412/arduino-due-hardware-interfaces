#include <Arduino.h>
#include <Wire.h>
#include <IMU_Wrapper.h>
#include <Utilities.h>

/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.

   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3-5V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
   2015/AUG/27  - Added calibration and system status helpers
   2015/NOV/13  - Added calibration save and restore
   */

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

IMU_Wrapper myImu(43);

/**************************************************************************/
/*
    Average the raw calibration offset and radius data
    */
/**************************************************************************/
adafruit_bno055_offsets_t avgSensorOffsets(adafruit_bno055_offsets_t* buffer, int len)
{
    AverageSign accel_offset_x(len);
    AverageSign accel_offset_y(len);
    AverageSign accel_offset_z(len);
    AverageSign mag_offset_x(len);
    AverageSign mag_offset_y(len);
    AverageSign mag_offset_z(len);
    AverageSign gyro_offset_x(len);
    AverageSign gyro_offset_y(len);
    AverageSign gyro_offset_z(len);
    AverageSign accel_radius(len);
    AverageSign mag_radius(len);

    for (size_t i = 0; i < unsigned(len); i++)
    {
        accel_offset_x.setInt(buffer[i].accel_offset_x);
        accel_offset_y.setInt(buffer[i].accel_offset_y);
        accel_offset_z.setInt(buffer[i].accel_offset_z);
        mag_offset_x.setInt(buffer[i].mag_offset_x);
        mag_offset_y.setInt(buffer[i].mag_offset_y);
        mag_offset_z.setInt(buffer[i].mag_offset_z);
        gyro_offset_x.setInt(buffer[i].gyro_offset_x);
        gyro_offset_y.setInt(buffer[i].gyro_offset_y);
        gyro_offset_z.setInt(buffer[i].gyro_offset_z);
        accel_radius.setInt(buffer[i].accel_radius);
        mag_radius.setInt(buffer[i].mag_radius);
    }

    adafruit_bno055_offsets_t average;
  
    average.accel_offset_x = accel_offset_x.getAverage();
    average.accel_offset_y = accel_offset_y.getAverage();
    average.accel_offset_z = accel_offset_z.getAverage();
    average.mag_offset_x = mag_offset_x.getAverage();
    average.mag_offset_y = mag_offset_y.getAverage();
    average.mag_offset_z = mag_offset_z.getAverage();
    average.gyro_offset_x = gyro_offset_x.getAverage();
    average.gyro_offset_y = gyro_offset_y.getAverage();
    average.gyro_offset_z = gyro_offset_z.getAverage();
    average.accel_radius = accel_radius.getAverage();
    average.mag_radius = mag_radius.getAverage();

    return average;
}

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
    */
/**************************************************************************/
void setup(void)
{
    /* Initalize serial */
    Serial.begin(115200);
    while (!Serial)
        ;
    delay(300);

    Serial.println("Orientation Sensor Test\n");

    myImu.beginWithoutOffsets();

    /* Display some basic information on this sensor */
    myImu.displaySensorDetails();

    /* Optional: Display current status */
    myImu.displaySensorStatus();

    const size_t frames = 5;
    adafruit_bno055_offsets_t calibs[frames];
    for (size_t frame = 0; frame < frames; frame++)
    {
        myImu.resetSensor();

        /* Crystal must be configured AFTER loading calibration data into BNO055. */
        myImu.setExtCrystalUse(true);

        calibs[frame] = myImu.generateOffsets();
        Serial.println("--------------------------------");
    }

    Serial.println("Calibration Results: ");
    adafruit_bno055_offsets_t average = avgSensorOffsets(calibs, frames);
    IMU_Wrapper::displayOffsets(average);

    Serial.println("--------------------------------");
    Serial.println("Individual Results: ");
    for (size_t frame = 0; frame < frames; frame++)
    {
        IMU_Wrapper::displayOffsets(calibs[frame]);
    }
}

void loop(){};