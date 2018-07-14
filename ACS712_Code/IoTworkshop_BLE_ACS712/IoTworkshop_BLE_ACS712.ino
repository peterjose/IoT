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
#include <Ticker.h>
#include "SimpleBLE.h"
#include "esp_bt_device.h"
#include "CurrentSensor.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

/******************************* Declarations *********************************/

Ticker  ServerUpdateInterval;

/******************************* Global variables *****************************/
// Ticker
Ticker BLE_BroadcastInterval;
bool BLE_BroadcastFlag = false;

// BLE related variables
SimpleBLE ble;
String BLE_LocalID = "BLE:";

String sensorData;
double sensorValue = 0;

/******************************* Functions ************************************/
void  tickerUpdateHandler(void);
void  printDeviceAddress(void);
void  configureBLE(void);
void  BLE_SensorBroadcastTask(void);

/******************************* Functions Definitons *************************/

/*
   @Brief
   @Param   None
   @Return  None
*/
void tickerUpdateHandler(void)
{
  BLE_BroadcastFlag = true;
}

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
  if (BLE_BroadcastFlag ==  true)                          // If the Broadcast interval has expired
  {
    BLE_BroadcastFlag = false;
    sensorData = "**C";
    sensorData += String(sensorValue, 2);
    sensorData += String("C");
    DEBUG_PRINT(F("Sensor Data : "));
    DEBUG_PRINT_LN(&sensorData[2]);
    // Advertise the new sensor information
    ble.advertiseData((uint8_t *)sensorData.c_str(), BLE_SERVICE_DATA_LENGTH);
  }
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

  configureBLE();

  // Broadcast Update handler
  BLE_BroadcastInterval.attach_ms(TICKER_BLE_BROADCAST_INTERVAL, tickerUpdateHandler);

  // configure the LED pin
  delay(100);
  // Init the current sensor
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
  sensorValue = GetSensorData();
  BLE_SensorBroadcastTask();
}

/* EOF */
