#include <ESP8266WiFi.h>


//////////////////
//Super Basic AP//
//////////////////

WiFiServer server(80);

void setup() 
{
  setupWiFi();
  server.begin();
}

void loop() 
{

}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP8266-Dragon", "DragonFruit");
}

