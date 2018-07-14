/***************************************************
  @file   MQTT_Communication.h
  @brief  File provides APIs the functions for MQTT communication
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose
***************************************************/

#ifndef _MQTT_COMMUNICATION_H_
#define _MQTT_COMMUNICATION_H_

void  InitMQTT_Communication(void);
void  MQTT_ServerTask(void);
void  TriggerServerUpdate(void);

#endif /* _MQTT_COMMUNICATION_H_ */


