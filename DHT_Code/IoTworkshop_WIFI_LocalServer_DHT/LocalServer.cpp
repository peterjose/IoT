/***************************************************
  @file   LocalServer.cpp
  @brief  File provides APIs the functions for Local Server
  @Author TeamRoboCET

  // IoT Workshop 2018
  // This is a demo code and shouldn't be used for any long term use or commercial purpose

***************************************************/
#include "Arduino.h"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include "DHT_Sensor.h"
#include "Config.h"

/******************************* Declarations ***********************************/

extern WiFiClient client;

// TCP server at port 80 will respond to HTTP requests
WiFiServer server(80);

String mDNSstring = "team";

bool LEDstate = false;

/******************************* Functions Definitons ***************************/
/*
   @Brief   Fucntion to Intialise Local server
   @Param   None
   @Return  None
*/
void InitLocalServer(void)
{
  pinMode(LED_OUTPUT_PIN, OUTPUT);
  digitalWrite(LED_OUTPUT_PIN, LEDstate);
  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is "localserverX.local"
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  mDNSstring += String(TEAM_NUMBER);
  if (!MDNS.begin(mDNSstring.c_str()))
  {
    DEBUG_PRINT_LN("Error setting up MDNS responder!");
    while (1)
    {
      delay(1000);
    }
  }
  DEBUG_PRINT_LN("mDNS responder started");

  // Start TCP (HTTP) server
  server.begin();
  DEBUG_PRINT_LN("TCP server started");

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);

  // print available URL
  DEBUG_PRINT_LN(F("Supported URL's : "));
  DEBUG_PRINT(F("http://"));
  DEBUG_PRINT(mDNSstring);
  DEBUG_PRINT_LN(F(".local/temperature"));
  DEBUG_PRINT(F("http://"));
  DEBUG_PRINT(mDNSstring);
  DEBUG_PRINT_LN(F(".local/humidity"));
  DEBUG_PRINT(F("http://"));
  DEBUG_PRINT(mDNSstring);
  DEBUG_PRINT_LN(F(".local/led_toggle"));
  DEBUG_PRINT_LN(F(""));
}

/*
   @Brief   Function for server Task
   @Param   None
   @Return  None
*/
void ServerTask(void)
{
  long int previousTime = 0;
  // Check if a client has connected
  client = server.available();
  if (!client) {
    return;
  }
  previousTime = millis();
  // Wait for data from client to become available
  while ((client.connected() && !client.available()) && (millis() - previousTime) < 1000)
  {
    delay(1);
  }

  // Read the first line of HTTP request
  String req = client.readStringUntil('\r');

  // First line of HTTP request looks like "GET /path HTTP/1.1"
  // Retrieve the "/path" part by finding the spaces
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if (addr_start == -1 || addr_end == -1) {
    return;
  }
  req = req.substring(addr_start + 1, addr_end);
  DEBUG_PRINT("Request: ");
  DEBUG_PRINT_LN(req);
  client.flush();

  String s;
  if (req == "/temperature")
  {
    ObtainSensorData();
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Temperature : ";
    s += String(GetTemperatureSensorData(), 1);
    s += "</html>\r\n\r\n";
    DEBUG_PRINT_LN("Sending 200");
  }
  else if (req == "/humidity")
  {
    ObtainSensorData();
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Humidity : ";
    s += String(GetHumiditySensorData(), 1);
    s += "</html>\r\n\r\n";
//    DEBUG_PRINT_LN("Sending 200");
  }
  else if (req == "/led_toggle")
  {
    LEDstate = !LEDstate;
    digitalWrite(LED_OUTPUT_PIN, LEDstate);
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>LED : ";
    s += String(LEDstate == true ? "ON" : "OFF");
    s += "</html>\r\n\r\n";
//    DEBUG_PRINT_LN("Sending 200");
  }
  else
  {
    s = "HTTP/1.1 404 Not Found\r\n\r\n";
    DEBUG_PRINT_LN("Sending 404");
  }

  client.print(s);

  DEBUG_PRINT_LN("Done with client\n");
}

/* EOF */
