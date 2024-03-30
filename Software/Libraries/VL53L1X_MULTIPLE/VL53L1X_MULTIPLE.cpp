/*
  Reading distance from the laser based VL53L1X
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  SparkFun labored with love to create this code. Feel like supporting open source hardware?
  Buy a board from SparkFun! https://www.sparkfun.com/products/14667

  This example prints the distance to an object.

  Are you getting weird readings? Be sure the vacuum tape has been removed from the sensor.
*/

#include <Arduino.h>
#include <Wire.h>
#include "SparkFun_VL53L1X.h" //Click here to get the library: http://librarymanager/All#SparkFun_VL53L1X
#include "VL53L1X.h"

// Optional interrupt and shutdown pins.
#define LRF1_SHUTDOWN_PIN 13
#define LRF2_SHUTDOWN_PIN 14

extern SFEVL53L1X lrf1;
extern SFEVL53L1X lrf2;

// Uncomment the following line to use the optional shutdown and interrupt pins.
// SFEVL53L1X distanceSensor(Wire, SHUTDOWN_PIN, INTERRUPT_PIN);

void init_2_VL53L1X(void)
{
  Wire.begin(9, 8);
  Serial.begin(115200);
  Serial.println("VL53L1X Qwiic Test");

  pinMode(LRF1_SHUTDOWN_PIN, OUTPUT); // Set the pin to output
  pinMode(LRF2_SHUTDOWN_PIN, OUTPUT); // Set the pin to output

  digitalWrite(LRF1_SHUTDOWN_PIN, LOW); // Pull pin low to power off the sensor
  digitalWrite(LRF2_SHUTDOWN_PIN, LOW); // Pull pin low to power off the sensor

  pinMode(LRF2_SHUTDOWN_PIN, INPUT); // Set pin back to input
  delay(10);
  if (lrf2.begin() != 0) // Begin returns 0 on a good init
  {
    Serial.println("lrf2 failed to begin. Please check wiring. Freezing...");
    while (1)
      ;
  }
  Serial.println("Sensor online!");

  lrf2.setI2CAddress(0x40); // Change address of sensor 2 to 0x40
  if (lrf2.begin() != 0)    // Begin returns 0 on a good init
  {
    Serial.println("lrf2 failed to begin. Please check wiring. Freezing...");
    while (1)
      ;
  }

  lrf2.setIntermeasurementPeriod(50); // Set the intermeasurement period to 50 ms
  Serial.println(lrf2.getIntermeasurementPeriod()); // Print the intermeasurement period

  pinMode(LRF1_SHUTDOWN_PIN, INPUT); // Set pin back to input
  delay(10);
  if (lrf1.begin() != 0) // Begin returns 0 on a good init, address is the default 0x29
  {
    Serial.println("lrf1 failed to begin. Please check wiring. Freezing...");
    while (1)
      ;
  }
  {
    Serial.println("lrf1 failed to begin. Please check wiring. Freezing...");
    while (1)
      ;
  }

  lrf1.setIntermeasurementPeriod(50); // Set the intermeasurement period to 50 ms
  Serial.println(lrf1.getIntermeasurementPeriod()); // Print the intermeasurement period

  lrf1.startRanging(); // Start only once (and never call stop)
  lrf2.startRanging(); // Start only once (and never call stop)
}

float getLrfDistanceCm(uint8_t lrfNum)
{
  if (lrfNum == 1) // Check if the sensor number is 1
  {
    while (!lrf1.checkForDataReady()) // Check if the data is ready
    {
      delay(1); 
    }

    float lrf1Cm = lrf1.getDistance() / 10.0; // Get the result of the measurement from the sensor in cm
    lrf1.clearInterrupt(); // Clear the interrupt
    return lrf1Cm;
  }
  else if (lrfNum == 2) // Check if the sensor number is 2
  {
    while (!lrf2.checkForDataReady())
    {
      delay(1);
    }

    float lrf2Cm = lrf2.getDistance() / 10.0; // Get the result of the measurement from the sensor in cm
    lrf2.clearInterrupt(); // Clear the interrupt
    return lrf2Cm;
  }
  else
  {
    return -1;
  }
}
