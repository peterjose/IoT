/***************************************************
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

///******* DEMO CODE *******///

#include "Config.h"
#include "DHT_Sensor.h"

/******************************* Functions Definitons ***************************/

/**
   @brief   Setup Function
   @param   None
   @Return  None
*/
void setup()
{
#ifdef DEBUG_PRINT_ENABLE
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  DEBUG_PRINT_LN(F(" "));
#endif /* DEBUG_PRINT_ENABLE */

  DEBUG_PRINT_LN(F("IoT Workshop 2018"));
  pinMode(LED_OUTPUT_PIN , OUTPUT);
  digitalWrite(LED_OUTPUT_PIN,LOW);
  delay(5000);
}

/**
   @brief   Loop Function
   @param   None
   @Return  None
*/
void loop()
{
  ObtainSensorData();
  digitalWrite(LED_OUTPUT_PIN,(GetHumiditySensorData() > LED_TOGGLE_LIMIT));
  delay(100);
}

/* EOF */
