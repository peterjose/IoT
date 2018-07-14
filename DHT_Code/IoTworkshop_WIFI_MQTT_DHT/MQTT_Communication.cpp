/***************************************************
  @file   MQTT_Communication.cpp
  @brief  File provides APIs the functions for MQTT Communication
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose

***************************************************/
#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "DHT_Sensor.h"
#include "Config.h"

extern WiFiClient client;
bool ServerUpdateFlag = false;


// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/******************************* Feeds ******************************************/

// Setup a feed called 'TemperatureSensor' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish TempSensorData = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/TemperatureSensor");

// Setup a feed called 'HumiditySensor' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish HumiSensorData = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/HumiditySensor");

// Setup a feed called 'OnOff' for subscribing to changes.
Adafruit_MQTT_Subscribe OnOffButton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/OnOff");

/******************************* Functions Definitons ***************************/

/*
   @Brief   Function to notify the Server update
   @Param   None
   @Return  None
*/
void TriggerServerUpdate(void)
{
  ServerUpdateFlag = true;
}

/*
   @Brief   On and Off call back function
   @Param   data, data pointer
   @Param   len, length of data received
   @Return  None
*/
void onoffcallback(char *data, uint16_t len)
{
  digitalWrite(LED_OUTPUT_PIN, ((data[0] == '0') ? LOW : HIGH));
}

/*
   @Brief   Fucntion to Intialise MQTT Communication
   @Param   None
   @Return  None
*/
void InitMQTT_Communication(void)
{
  OnOffButton.setCallback(onoffcallback);
  mqtt.subscribe(&OnOffButton);
}

/**
   @brief   Function to connect and reconnect as necessary to the MQTT server.
   @param   None
   @return  None
*/
bool MQTT_connect(void)
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return true;
  }

  DEBUG_PRINT(F("Connecting to MQTT... "));

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0 && retries != 0) { // connect will return 0 for connected
    DEBUG_PRINT_LN(mqtt.connectErrorString(ret));
    DEBUG_PRINT_LN(F("Retrying MQTT connection in 5 seconds..."));
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
  }
  if (mqtt.connected() != 0)
  {
    DEBUG_PRINT_LN(F("MQTT Connected!"));
  }
  return (mqtt.connected());
}

/*
   @Brief   Function for MQTT task
   @Param   None
   @Return  None
*/
void MQTT_ServerTask(void)
{
  mqtt.processPackets(100);
  if (ServerUpdateFlag == true)
  {
    ServerUpdateFlag = false;
    if (WiFi.status() == WL_CONNECTED)
    {
      DEBUG_PRINT(F("wifi OK "));
      // Ensure the connection to the MQTT server is alive (this will make the first
      // connection and automatically reconnect when disconnected).  See the MQTT_connect
      // function definition further below.
      if (MQTT_connect())
      {
        DEBUG_PRINT_LN(F("MQTT OK "));

        // this is our 'wait for incoming subscription packets' busy subloop
        // try to spend your time here

        // Now we can publish
        if ( !(TempSensorData.publish(GetTemperatureSensorData())))
        {
          DEBUG_PRINT_LN(F("Failed"));
        }
        else
        {
          DEBUG_PRINT_LN(F("Temperature Sensor Data send status OK!"));
        }
        delay(100);
        if ( !(HumiSensorData.publish(GetHumiditySensorData())))
        {
          DEBUG_PRINT_LN(F("Failed"));
        }
        else
        {
          DEBUG_PRINT_LN(F("Humidity Sensor Data send status OK!"));
        }
      }

      // ping the server to keep the mqtt connection alive
      // NOT required if you are publishing once every KEEPALIVE seconds
      /*
        if(! mqtt.ping()) {
        mqtt.disconnect();
        }
      */
    }
  }
}

/* EOF */
