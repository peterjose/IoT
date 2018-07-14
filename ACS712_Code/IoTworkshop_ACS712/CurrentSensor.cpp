/***************************************************
  @file   CurrentSensor.cpp
  @brief  File provides APIs the functions for current sensor
  @Author TeamRoboCET

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


***************************************************/

#include "Arduino.h"
#include "ACS712.h"
#include "Config.h"

/******************************* Declarations *********************************/
ACS712 sensor(ACS712_05B, 34);

double  AmpsRMS = 0;

double  AmpsRMSAvg      = 0;
int     AmpsRMSAvgCount = 0;
double  avgSensorValue  = 0;

unsigned long previousMillis = 0;

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
  pinMode(ACS_712_SENSOR_PIN  , INPUT);
  delay(10);
  sensor.setZeroPoint(SENSOR_ZERO_POINT);
}

/**
   @brief   Function to get Sensor Data
   @param   None
   @Return  double, SensorData
*/
double GetSensorData(void)
{
  return avgSensorValue;
}

/**
   @brief   Function Obtain Sensor Data
   @param   None
   @Return  None
*/
void ObtainSensorData(void)
{
  sensorCalibration();
  computeRMS_Current();
  if ((AmpsRMSAvgCount == RMS_AVG_COUNTER_MAX) || ((millis()-previousMillis)> 2000))
  {
    AmpsRMSAvg = 0;
    AmpsRMSAvgCount = 0;
  }
  previousMillis = millis();
  AmpsRMSAvg += AmpsRMS;
  AmpsRMSAvgCount++;
  avgSensorValue = AmpsRMSAvg / AmpsRMSAvgCount;
  DEBUG_PRINT(F("Rms Current : "));
  DEBUG_PRINT_LN(avgSensorValue);
}

/**
   @brief   Function to reset average 
   @param   None
   @Return  None
*/
void ResetAvgValues(void)
{
  AmpsRMSAvg = 0;
  AmpsRMSAvgCount = 0;
}

/**
   @brief   Function to compute the RMS current
   @param   None
   @Return  None
*/
void computeRMS_Current(void)
{
  AmpsRMS = sensor.getCurrentAC();
  AmpsRMS = AmpsRMS * 1000;
  // Map the sensor output value based on the calibration
  AmpsRMS = map(AmpsRMS, SENSOR_MIN_CAL_VAL, SENSOR_MAX_CAL_VAL, CAL_MIN_CURRENT_APPLIED, CAL_MAX_CURRENT_APPLIED );
  // Cap the value within the limits
  AmpsRMS = constrain(AmpsRMS, 0, 5000);
  AmpsRMS = AmpsRMS / 1000;
  if(AmpsRMS < ZERO_ERROR_THLD)
    AmpsRMS = 0.0;
}

/**
   @brief   Function to get calibration points
   @param   None
   @Return  None
*/
void sensorCalibration(void)
{
#ifdef CALIBRATION_ENABLED
  // Subtract min from max
  DEBUG_PRINT(F("Calibration Cycle Value : "));
  DEBUG_PRINT_LN(sensor.calibrate());
  DEBUG_PRINT(F("Calibration Cycle Zero Point Value : "));
  DEBUG_PRINT_LN(sensor.getCurrentAC());
#endif /* CALIBRATION_ENABLED */
}

/* EOF */

