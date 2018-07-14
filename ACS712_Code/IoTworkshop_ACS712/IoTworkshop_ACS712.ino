/***************************************************
  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose

  // ACS 712 Current sensor PinOut
  //      _______
  //      | O O |
  //      |     |
  //      |. . .|
  //      |_____|
  //       | | |
  //       1 2 3
  //
  //       1. Vcc
  //       2. Out
  //       3. Gnd

  // Circuit provided for ACS 712 interfacing should only be used to measure current upto 1 Amps
  // To measure higher current please use a voltage divider circuit

  //  Adafruit MQTT Library
   
  //  Adafruit invests time and resources providing this open source code,
  //  please support Adafruit and open-source hardware by purchasing
  //  products from Adafruit!
  
  //  Written by Tony DiCola for Adafruit Industries.
  //  MIT license, all text above must be included in any redistribution

****************************************************/
#include "Config.h"
#include "CurrentSensor.h"

/******************************* Global variables *******************************/

double sensorValue = 0;

/******************************* Functions Definitons ***************************/

/**
  @brief  Setup Function 
  @param  None
  @return None
*/
void setup(void)
{
#ifdef DEBUG_PRINT_ENABLE
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  DEBUG_PRINT_LN(F(" "));
#endif /* DEBUG_PRINT_ENABLE */
  DEBUG_PRINT_LN(F("IoT Workshop"));
  delay(1000);
  // Init the current sensor
  SensorInit();
  pinMode(LED_OUTPUT_PIN , OUTPUT);
  digitalWrite(LED_OUTPUT_PIN,LOW);
}

/**
  @brief  Loop Function
  @param  None
  @return None
*/
void loop()
{
  ObtainSensorData();
  sensorValue = GetSensorData();
  digitalWrite(LED_OUTPUT_PIN,(sensorValue > LED_TOGGLE_LIMIT));
}

/* EOF */
