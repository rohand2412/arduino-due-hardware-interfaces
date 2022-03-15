/**
 * Finds the most optimal calibration offset for a BNO055 IMU
 * Copyright (C) 2022  Rohan Dugad
 * 
 * Contact info:
 * https://docs.google.com/document/d/17IhBs4cz7FXphE0praCaWMjz016a7BFU5IQbm1CNnUc/edit?usp=sharing
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <Arduino.h>
#include <Wire.h>
#include <IMU_Wrapper.h>
#include <Utilities.h>

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