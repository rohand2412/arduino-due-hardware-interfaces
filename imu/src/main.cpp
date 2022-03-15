/**
 * IMU_Wrapper test cases/example code
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

bool once = true;
IMU_Wrapper localImu(43);
IMU_Wrapper totalImu(43);

adafruit_bno055_offsets_t offsets{13, -48, -25,
                                  -101, 127, 438,
                                  -2, -2, 0,
                                  1000, 835};

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
    Serial.begin(115200);
    while (!Serial)
        ;
    delay(300);

    const size_t wrapperNum = 3;
    IMU_Wrapper imus[wrapperNum];
    imus[0].createSensor(43);
    imus[0].setOffsets(offsets);
    imus[0].begin();
    imus[1].createSensor(43);
    imus[1].setOffsets(offsets);
    imus[1].begin();
    imus[2].createSensor(43);
    imus[2].setOffsets(offsets);
    imus[2].begin();

    Serial.print("Total Number of Initialized Imus: ");
    Serial.println(IMU_Wrapper::getTotalSensorNum());

    for (size_t wrapper = 0; wrapper < wrapperNum; wrapper++)
    {
        imus[wrapper].displayOffsets();
        imus[wrapper].displaySensorDetails();
        imus[wrapper].displaySensorStatus();
        imus[wrapper].displayCalStatus();
        imus[wrapper].displayOrientation();
    }

    delay(2000);
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
    if (once)
    {
        localImu.setOffsets(offsets);
        totalImu.setOffsets(offsets);
        localImu.begin();
        totalImu.begin();
    }

    /* Get a new sensor information */
    localImu.update();
    totalImu.update();

    Serial.print(localImu.getYaw());
    Serial.print("\t");
    Serial.print(localImu.getPitch());
    Serial.print("\t");
    Serial.print(localImu.getRoll());
    Serial.print("\t\t");
    Serial.print(totalImu.getYaw());
    Serial.print("\t");
    Serial.print(totalImu.getPitch());
    Serial.print("\t");
    Serial.print(totalImu.getRoll());
    Serial.print("\n");

    if (Serial.available())
    {
        Serial.read();
        Serial.println("Reset localImu");
        localImu.reset();
        localImu.resetSensor();
    }
}