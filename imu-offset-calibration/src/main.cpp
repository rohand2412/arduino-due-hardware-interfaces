#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <imumaths.h>
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

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55);

/**************************************************************************/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
    */
/**************************************************************************/
void displaySensorDetails(void)
{
    sensor_t sensor;
    bno.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print("Sensor:       "); Serial.println(sensor.name);
    Serial.print("Driver Ver:   "); Serial.println(sensor.version);
    Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
    Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
    Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
    Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
}

/**************************************************************************/
/*
    Display some basic info about the sensor status
    */
/**************************************************************************/
void displaySensorStatus(void)
{
    /* Get the system status values (mostly for debugging purposes) */
    uint8_t system_status, self_test_results, system_error;
    system_status = self_test_results = system_error = 0;
    bno.getSystemStatus(&system_status, &self_test_results, &system_error);

    /* Display the results in the Serial Monitor */
    Serial.println("");
    Serial.print("System Status: 0x");
    Serial.println(system_status, HEX);
    Serial.print("Self Test:     0x");
    Serial.println(self_test_results, HEX);
    Serial.print("System Error:  0x");
    Serial.println(system_error, HEX);
    Serial.println("");
    delay(500);
}

/**************************************************************************/
/*
    Display sensor calibration status
    */
/**************************************************************************/
void displayCalStatus(const uint8_t& system, const uint8_t& gyro,
                      const uint8_t& accel, const uint8_t& mag)
{
    /* Get the four calibration values (0..3) */
    /* Any sensor data reporting 0 should be ignored, */
    /* 3 means 'fully calibrated" */
    // uint8_t system, gyro, accel, mag;
    // system = gyro = accel = mag = 0;
    // bno.getCalibration(&system, &gyro, &accel, &mag);

    /* The data should be ignored until the system calibration is > 0 */
    Serial.print("\t");
    if (!system)
    {
        Serial.print("! ");
    }

    /* Display the individual values */
    Serial.print("Sys:");
    Serial.print(system, DEC);
    Serial.print(" G:");
    Serial.print(gyro, DEC);
    Serial.print(" A:");
    Serial.print(accel, DEC);
    Serial.print(" M:");
    Serial.print(mag, DEC);
}

/**************************************************************************/
/*
    Display the raw calibration offset and radius data
    */
/**************************************************************************/
void displaySensorOffsets(const adafruit_bno055_offsets_t &calibData)
{
    Serial.print("Accelerometer: ");
    Serial.print(calibData.accel_offset_x); Serial.print(" ");
    Serial.print(calibData.accel_offset_y); Serial.print(" ");
    Serial.print(calibData.accel_offset_z); Serial.print(" ");

    Serial.print("\nGyro: ");
    Serial.print(calibData.gyro_offset_x); Serial.print(" ");
    Serial.print(calibData.gyro_offset_y); Serial.print(" ");
    Serial.print(calibData.gyro_offset_z); Serial.print(" ");

    Serial.print("\nMag: ");
    Serial.print(calibData.mag_offset_x); Serial.print(" ");
    Serial.print(calibData.mag_offset_y); Serial.print(" ");
    Serial.print(calibData.mag_offset_z); Serial.print(" ");

    Serial.print("\nAccel Radius: ");
    Serial.print(calibData.accel_radius);

    Serial.print("\nMag Radius: ");
    Serial.print(calibData.mag_radius);

    Serial.print("\n");
}

/**************************************************************************/
/*
    Get the raw calibration offset and radius data
    */
/**************************************************************************/
adafruit_bno055_offsets_t getSensorOffsets()
{
    sensors_event_t event;
    bno.getEvent(&event);
    /* always recal the mag as It goes out of calibration very often */
    Serial.println("Please Calibrate Sensor: ");

    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;

    while (!(system == 3 && gyro == 3 && accel == 3 && mag == 3))
    {
        bno.getEvent(&event);

        Serial.print("X: ");
        Serial.print(event.orientation.x, 4);
        Serial.print("\tY: ");
        Serial.print(event.orientation.y, 4);
        Serial.print("\tZ: ");
        Serial.print(event.orientation.z, 4);

        /* Wait the specified delay before requesting new data */
        delay(BNO055_SAMPLERATE_DELAY_MS);

        /* Optional: Display calibration status */
        bno.getCalibration(&system, &gyro, &accel, &mag);
        displayCalStatus(system, gyro, accel, mag);
        Serial.print(" R:");
        Serial.print(!(system == 3 && gyro == 3 && accel == 3 && mag == 3));

        /* New line for the next sample */
        Serial.println("");
    }

    Serial.println("\nFully calibrated!");

    //Fetch results
    adafruit_bno055_offsets_t newCalib;
    bno.getSensorOffsets(newCalib);

    //Return offsets
    return newCalib;
}

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
    /* Configure pins */
    const unsigned int RST = 43;
    pinMode(RST, OUTPUT);
    digitalWrite(RST, HIGH);

    /* Initalize serial */
    Serial.begin(115200);
    delay(1000);
    Serial.println("Orientation Sensor Test"); Serial.println("");

    /* Initialise the sensor */
    if (!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while (1);
    }

    /* Display some basic information on this sensor */
    displaySensorDetails();

    /* Optional: Display current status */
    displaySensorStatus();

    const size_t frames = 5;
    adafruit_bno055_offsets_t calibs[frames];
    for (size_t frame = 0; frame < frames; frame++)
    {
        digitalWrite(RST, LOW);
        delay(1);
        digitalWrite(RST, HIGH);
        delay(800);

        /* Crystal must be configured AFTER loading calibration data into BNO055. */
        bno.setExtCrystalUse(true);

        calibs[frame] = getSensorOffsets();
        Serial.println("--------------------------------");
    }

    Serial.println("Calibration Results: ");
    adafruit_bno055_offsets_t average = avgSensorOffsets(calibs, frames);
    displaySensorOffsets(average);

    Serial.println("--------------------------------");
    Serial.println("Individual Results: ");
    for (size_t frame = 0; frame < frames; frame++)
    {
        displaySensorOffsets(calibs[frame]);
    }
}

void loop(){};