/***************************************************
  @file   Config.h
  @brief  Cofiguration Parameters
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose
***************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/************************* Debug *********************************************/
// Enable / Disable Debug statements
// Comment the below line "#define DEBUG_PRINT_ENABLE" to disable debug statements
#define DEBUG_PRINT_ENABLE

#include "Debug.h"

/************************* SENSOR PIN ****************************************/
// Define Sensor related macros
#define DHTPIN                                    15        // Pin which is connected to the DHT sensor.
#define DHTTYPE                                   DHT11     // DHT 11 Sensor

/************************* LED Limit *********************************************/
#define LED_TOGGLE_LIMIT                          80

/************************* GPIO Setup ***************************************/
// OUTPUT control Led
#define LED_OUTPUT_PIN                            14

#endif /* _CONFIG_H_ */
