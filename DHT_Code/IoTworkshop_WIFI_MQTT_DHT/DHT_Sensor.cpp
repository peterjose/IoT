/***************************************************
  @file   DHT_Sensor.cpp
  @brief  File provides APIs the functions for DHT sensor
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose

  // DHT11 Pin out

  //    -------
  //    |:::::|
  //    |:::::|
  //    -------
  //    | | | |
  //    1 2 3 4
  //
  //    1 - Vcc
  //    2 - Out
  //    3 - NC
  //    4 - GND

  // DHT 11 Out should be connected to Vcc (PullUp) through 3.3 K Ohm
  // DHT 11 Out should be connected directly to pin 15 of ESP32

***************************************************/

#include "Arduino.h"

// Include sensor headers
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "Config.h"

/******************************* Declarations **********************************/
// Sensor Related
DHT_Unified dht(DHTPIN, DHTTYPE);

float humiSensor = 0;
float tempSensor = 0;

/******************************* Functions **************************************/
void  computeRMS_Current(void);
void  sensorCalibration(void);

/******************************* Functions Definitons ***************************/

/**
   @brief   Function is used to initialise the sensor
   @param   None
   @Return  None
*/
void SensorInit(void)
{
  // No special initialisation required for this sensor
}

/**
   @brief   Function to get temperature Sensor Data
   @param   None
   @Return  float, temperature value
*/
float GetTemperatureSensorData(void)
{
  return tempSensor;
}

/**
   @brief   Function to get Humidity Sensor Data
   @param   None
   @Return  float, Humidity
*/
float GetHumiditySensorData(void)
{
  return humiSensor;
}

/**
   @brief   Function Obtain Sensor Data
   @param   None
   @Return  None
*/
void ObtainSensorData(void)
{
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    tempSensor = 0;
    DEBUG_PRINT_LN(F("Error reading temperature!"));
  }
  else
  {
    tempSensor = event.temperature;
    DEBUG_PRINT(F("Temperature: "));
    DEBUG_PRINT(event.temperature);
    DEBUG_PRINT_LN(F(" *C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity))
  {
    humiSensor = 0;
    DEBUG_PRINT_LN(F("Error reading humidity!"));
  }
  else
  {
    humiSensor = event.relative_humidity;
    DEBUG_PRINT(F("Humidity: "));
    DEBUG_PRINT(event.relative_humidity);
    DEBUG_PRINT_LN(F(" %"));
  }
}

/* EOF */
