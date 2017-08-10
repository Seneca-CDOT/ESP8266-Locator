#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(9600);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  const char* SSID = "ESP8266-Dragon";
  const char* password = "DragonFruit"; 
}

void loop() {

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print("Time since boot: ");
    Serial.println(millis());
    Serial.print(n);
    Serial.println(" networks found");
    Serial.print("MAC of ESP8266: ");
    Serial.println(WiFi.macAddress());
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.println(WiFi.SSID(i));
      Serial.println(WiFi.RSSI(i));
      Serial.println(WiFi.BSSIDstr(i));
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(1000*60);
}



