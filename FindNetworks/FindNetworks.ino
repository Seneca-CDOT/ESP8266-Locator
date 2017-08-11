#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  const char* SSID = "ESP8266-Dragon";
  const char* password = "DragonFruit"; 
}

void loop() {

  int n = WiFi.scanNetworks(); //n=number of networks found
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.println(millis());
    Serial.println(WiFi.macAddress());
    for (int i = 0; i < n; ++i)
    {
      Serial.print(WiFi.SSID(i));
      if (i != n-1){
        Serial.print(",");
      }   
    }
    Serial.println("");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(WiFi.RSSI(i));
      if (i != n-1){
        Serial.print(",");
      } 
    }
    Serial.println("");
    for (int i = 0; i < n; ++i)
    {
      Serial.print(WiFi.BSSIDstr(i));
      if (i != n-1){
        Serial.print(",");
      } 
    }
     Serial.print("");
    delay(10);
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(10000);
}



