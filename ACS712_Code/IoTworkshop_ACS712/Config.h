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

/************************* MACRO DEFINITIONS *********************************/

#define LED_TOGGLE_LIMIT                      0.2

/************************* Sensor Calibration ********************************/

// Uncomment the line to get the calibration information
//#define CALIBRATION_ENABLED

/************************* SENSOR RELATED MACRO ******************************/

#define RMS_AVG_COUNTER_MAX                   20
#define ACS_712_SENSOR_PIN                    34

#define SENSOR_ZERO_POINT                     2880

#define ZERO_ERROR_THLD                       0.08

/************************* Calibration Factors for ACS712 *********************/

#define CAL_MIN_CURRENT_APPLIED               0               // Calibration min is the value to be obtained when 0.00 A current flows through the Sensor
#define CAL_MAX_CURRENT_APPLIED               440             // Calibration max is the value to be obtained when 0.44 A current flows through the Sensor
#define SENSOR_MIN_CAL_VAL                    150             // Sensor value obtained when 0.00 A is passed through the sensor
#define SENSOR_MAX_CAL_VAL                    530             // Sensor value obtained when 0.44 A is passed through the sensor

/************************* GPIO Setup ****************************************/

// OUTPUT control Led
#define LED_OUTPUT_PIN                        14

#endif /* _CONFIG_H_ */
