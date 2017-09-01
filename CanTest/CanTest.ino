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

  int n = WiFi.scanNetworks(); //n=number of networks found
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print("Scan #");
    Serial.print(ScanNum);
    Serial.print("  ");
    for (int i = 0; i < n; ++i)
    {
      if(WiFi.SSID(i) == "ESP8266-Dragon")
      {
        Serial.print("Dragon ");
        Serial.print(WiFi.RSSI(i));
        if(WiFi.RSSI(i) > -42)
        {
          Serial.println("In front of Can");
        }
        else
        {
          Serial.println("Not In front of Can");
        }
      }
      if(WiFi.SSID(i) == "ESP8266-Eagle")
      {
        Serial.print("Eagle ");
        Serial.print(WiFi.RSSI(i));
        if(WiFi.RSSI(i) > -42)
        {
          Serial.println("In front of Can");
        }
        else
        {
          Serial.println("Not In front of Can");
        }
      }
      if(WiFi.SSID(i) == "ESP8266-Ardvark")
      {
        Serial.print("Ardvark ");
        Serial.print(WiFi.RSSI(i));
        if(WiFi.RSSI(i) > -42)
        {
          Serial.println("In front of Can");
        }
        else
        {
          Serial.println("Not In front of Can");
        }
      }
    }
  }
  
  ScanNum++;

  // Wait a bit before scanning again
  delay(100);
}



