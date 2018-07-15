/***************************************************
  @file   DHT_Sensor.h
  @brief  File provides APIs the functions for current DHT sensor
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose

***************************************************/

#ifndef _DHT_SENSOR_H_
#define _DHT_SENSOR_H_

void  ObtainSensorData(void);
void  SensorInit(void);
float GetTemperatureSensorData(void);
float GetHumiditySensorData(void);

#endif /* _DHT_SENSOR_H_ */
