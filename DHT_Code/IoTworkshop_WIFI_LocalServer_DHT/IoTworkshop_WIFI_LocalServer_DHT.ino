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

****************************************************/
#include "Config.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include "LocalServer.h"
#include "DHT_Sensor.h"

/******************************* Global variables *****************************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

bool WIFI_InitOK = false;

/******************************* Functions ************************************/
bool  checkForWIFIStatus(void);
void  configureWIFI(void);

/******************************* Functions Definitons *************************/

/*
   @Brief   Check the WIFI status
   @Param   None
   @Return  None
*/
bool checkForWIFIStatus(void)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    if (WIFI_InitOK == true)
    {
      // if connection is lost after first connection the reconnect
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
    DEBUG_PRINT(F("IP address: "));
    DEBUG_PRINT_LN(WiFi.localIP());
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
  // Print WIFI Connection
  DEBUG_PRINT(F("Connecting to "));
  DEBUG_PRINT_LN(WLAN_SSID);
  // Connect to WiFi access point.
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  // check for WIFI status
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

  // Initialise MQTT
  InitLocalServer();
  // Initialise Sensor
  SensorInit();
}

/**
  @brief  Loop Function
  @param  None
  @return None
*/
void loop()
{
  ServerTask();
  checkForWIFIStatus();
}

/* EOF */
