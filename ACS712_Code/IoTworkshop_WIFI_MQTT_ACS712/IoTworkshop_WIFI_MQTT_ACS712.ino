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
  //
  //  Adafruit invests time and resources providing this open source code,
  //  please support Adafruit and open-source hardware by purchasing
  //  products from Adafruit!
  //
  //  Written by Tony DiCola for Adafruit Industries.
  //  MIT license, all text above must be included in any redistribution

****************************************************/
#include "Config.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <Ticker.h>
#include "MQTT_Communication.h"
#include "CurrentSensor.h"

/******************************* Declarations *********************************/

Ticker  ServerUpdateInterval;

/******************************* Global variables *****************************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

bool WIFI_InitOK = false;

/******************************* Functions ************************************/
void  tickerUpdateHandler(void);
bool  checkForWIFIStatus(void);
void  configureWIFI(void);

/******************************* Functions Definitons *************************/

/*
   @Brief   ticker update handler for server ticker
   @Param   None
   @Return  None
*/
void tickerUpdateHandler(void)
{
  TriggerServerUpdate();
}

/*
   @Brief   Check the WIFI status 
   @Param   None
   @Return  None
*/
bool checkForWIFIStatus(void)
{
  if (WiFi.status() != WL_CONNECTED)
  { 
    if(WIFI_InitOK == true)
    {
      WiFi.reconnect();
    }
    DEBUG_PRINT(F("Wait for WIFI "));
    DEBUG_PRINT_LN(WLAN_SSID);
    while (WiFi.status() != WL_CONNECTED)
    {
      DEBUG_PRINT(F("."));
      delay(1000);
    }
    DEBUG_PRINT_LN(F(" "));
    DEBUG_PRINT_LN(F("Connected"));
    return false;
  }
  return true;
}

/*
   @Brief   Function to configure the WIFI
   @Param   None
   @Return  None
*/
void configureWIFI(void)
{
  // WIFI Connection
  DEBUG_PRINT(F("Connecting to "));
  DEBUG_PRINT_LN(WLAN_SSID);
  // Connect to WiFi access point.
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  checkForWIFIStatus();
  WIFI_InitOK = true;
  delay(100);
}

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

  configureWIFI();

  // configure the LED pin
  pinMode (LED_OUTPUT_PIN , OUTPUT);
  delay(100);

  // Setup MQTT subscription for onoff feed.
  ServerUpdateInterval.attach_ms(TICKER_SERVER_UPDATE_INTERVAL, tickerUpdateHandler);

  InitMQTT_Communication();
  SensorInit();
}

/**
  @brief  Loop Function
  @param  None
  @return None
*/
void loop()
{
  ObtainSensorData();
  MQTT_ServerTask();
  if(!checkForWIFIStatus())
  {
    ResetAvgValues();
  }
}

/* EOF */
