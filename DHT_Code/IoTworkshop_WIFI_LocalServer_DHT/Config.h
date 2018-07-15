/***************************************************
  @file   Config.h
  @brief  Cofiguration Parameters
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose
***************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/************************* TEAM Info *****************************************/

#define TEAM_NUMBER                           "0"       // Should be 0 to 9

/************************* Debug *********************************************/
// Enable / Disable Debug statements
// Comment the below line "#define DEBUG_PRINT_ENABLE" to disable debug statements
#define DEBUG_PRINT_ENABLE

#include "Debug.h"

/************************* WIFI Setup ****************************************/
#define WLAN_SSID                             "SSID"
#define WLAN_PASS                             "password"

/************************* SENSOR PIN ***************************************/
// Define Sensor related macros
#define DHTPIN                                15        // Pin which is connected to the DHT sensor.
#define DHTTYPE                               DHT11     // DHT 11 Sensor

/************************* GPIO Setup ***************************************/
// OUTPUT control Led
#define LED_OUTPUT_PIN                        14

#endif /* _CONFIG_H_ */
