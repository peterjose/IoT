/***************************************************
  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose
  // Following Library files are updated for the current project.
  //    SimpleBle.h and SimpleBle.c files
  
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
***************************************************/

///******* DEMO CODE *******///

#include "Config.h"
#include "SimpleBLE.h"
#include <Ticker.h>
#include "esp_bt_device.h"
#include "DHT_Sensor.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/******************************* Declarations *********************************/
// Ticker
Ticker BLE_BroadcastInterval;
bool BLE_BroadcastFlag = false;

// BLE related variables
SimpleBLE ble;
String BLE_LocalID = "BLE:";

// Sensor data variable
String sensorData;

/******************************* Functions ************************************/
void  tickerUpdateHandler(void);
void  printDeviceAddress(void);
void  configureBLE(void);
void  BLE_SensorBroadcastTask(void);

/******************************* Functions Definitons *************************/

/**
   @brief   Function to print the device MAC address
   @param   None
   @Return  None
*/
void printDeviceAddress(void)
{
  const uint8_t* point = esp_bt_dev_get_address();
  DEBUG_PRINT(F("Device Mac Address : "));
  for (int i = 0; i < 6; i++)
  {
    char str[3];
    sprintf(str, "%02X", (int)point[i]);
    DEBUG_PRINT(str);
    if (i < 5)
    {
      DEBUG_PRINT(F(":"));
    }
  }
  DEBUG_PRINT_LN(F(" "));
}

/**
   @brief   Ticker Update Handler
   @param   None
   @Return  None
*/
void tickerUpdateHandler(void)
{
  BLE_BroadcastFlag = true;
}

/*
   @Brief   Function to configure the BLE
   @Param   None
   @Return  None
*/
void configureBLE(void)
{
  BLE_LocalID += String(TEAM_NUMBER);
  ble.begin(BLE_LocalID);
  delay(100);
  printDeviceAddress();
  delay(100);
}


/**
   @brief   Function Do the periodic BLE broadcasting
   @param   None
   @Return  None
*/
void BLE_SensorBroadcastTask(void)
{
  sensorData = "**T";
  // Get Temperature value
  if (GetTemperatureSensorData() < 10)
  {
    sensorData += String("0");
  }
  sensorData += String(GetTemperatureSensorData(), 1);
  sensorData += String("T");
  // Get humidity value.
  sensorData += String("H");
  if (GetHumiditySensorData() < 10)
  {
    sensorData += String("0");
  }
  sensorData += String(GetHumiditySensorData(), 1);
  sensorData += String("H");
  DEBUG_PRINT(F("Sensor Data : "));
  DEBUG_PRINT_LN(&sensorData[2]);
  // Advertise the new sensor information
  ble.advertiseData((uint8_t *)sensorData.c_str(), BLE_SERVICE_DATA_LENGTH);
}

/**
   @brief   Setup Function
   @param   None
   @Return  None
*/
void setup()
{
#ifdef DEBUG_PRINT_ENABLE
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  DEBUG_PRINT_LN(F(" "));
#endif /* DEBUG_PRINT_ENABLE */

  // Broadcast Update handler
  BLE_BroadcastInterval.attach_ms(TICKER_BLE_BROADCAST_INTERVAL, tickerUpdateHandler);

  DEBUG_PRINT_LN(F("IoT Workshop 2018"));
  configureBLE();
}

/**
   @brief   Loop Function
   @param   None
   @Return  None
*/
void loop()
{
  if (BLE_BroadcastFlag ==  true)                           // If the Broadcast interval has expired
  {
    BLE_BroadcastFlag = false;
    ObtainSensorData();
    BLE_SensorBroadcastTask();
  }
}

/* EOF */
