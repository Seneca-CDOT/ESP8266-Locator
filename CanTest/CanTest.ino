#include "ESP8266WiFi.h"

int ScanNum = 0;

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100); 
}

void loop() {
  int w = WiFi.scanNetworks(); //w=number of networks found

  int n = 0;

  for (int i = 0; i < w; ++i) {
    if ((WiFi.SSID(i).startsWith("X")) || (WiFi.SSID(i).startsWith("Y"))) {
      ++n;
    }
  }


  
  if (n == 0)
    Serial.println("no networks found");
  else {
    Serial.println(millis());
    Serial.println(WiFi.macAddress());
    for (int i = 0; i < n; ++i) {
      if ((WiFi.SSID(i).startsWith("X")) || (WiFi.SSID(i).startsWith("Y"))) {
        Serial.print(WiFi.SSID(i));
        if (i != n-1) {
          Serial.print(",");
        }
      }
    }
    Serial.println("");
    for (int i = 0; i < n; ++i) {
      if ((WiFi.SSID(i).startsWith("X")) || (WiFi.SSID(i).startsWith("Y"))) {
      Serial.print(WiFi.RSSI(i));
      if (i != n-1) {
        Serial.print(",");
      } 
    }
    }
    Serial.println("");
    for (int i = 0; i < n; ++i) {
      if ((WiFi.SSID(i).startsWith("X")) || (WiFi.SSID(i).startsWith("Y"))) {
      Serial.print(WiFi.BSSIDstr(i));
      if (i != n-1) {
        Serial.print(",");
      } 
    }
    }
     Serial.println("");


      }
  ScanNum++;

  // Wait a bit before scanning again
  delay(10000);
}
