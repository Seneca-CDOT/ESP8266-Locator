#include <ESP8266WiFi.h>


//////////////////
//Super Basic AP//
//////////////////

WiFiServer server(80);

void setup() 
{
  pinMode(2, OUTPUT);
  setupWiFi();
  server.begin();
}

void loop() 
{
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(1);                       // wait for a second
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("X9", "DragonFruit");
}

