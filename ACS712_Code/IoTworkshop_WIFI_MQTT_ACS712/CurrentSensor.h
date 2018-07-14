/***************************************************
  @file   CurrentSensor.h
  @brief  File provides APIs the functions for current sensor
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose
***************************************************/

#ifndef _CURRENT_SENSOR_H_
#define _CURRENT_SENSOR_H_

void    ObtainSensorData(void);
void    SensorInit(void);
void    ResetAvgValues(void);
double  GetSensorData(void);

#endif /* _CURRENT_SENSOR_H_ */
