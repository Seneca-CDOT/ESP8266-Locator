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
  else {
    Serial.print("\nScan #");
    Serial.print(ScanNum);
    Serial.print("\n");
    for (int i = 0; i < n; ++i) {
      if ((WiFi.SSID(i).startsWith("SenecaNET")) || (WiFi.SSID(i).startsWith("SenecaGuest"))) {
        Serial.print(WiFi.SSID(i));
        Serial.print(", ");
        Serial.print((WiFi.BSSID(i)[5]),HEX);
        Serial.print(":");
        Serial.print((WiFi.BSSID(i)[4]),HEX);
        Serial.print(":");
        Serial.print((WiFi.BSSID(i)[3]),HEX);
        Serial.print(":");
        Serial.print((WiFi.BSSID(i)[2]),HEX);
        Serial.print(":");
        Serial.print((WiFi.BSSID(i)[1]),HEX);
        Serial.print(":");
        Serial.print((WiFi.BSSID(i)[0]),HEX);
        Serial.print(", ");
        Serial.print(WiFi.RSSI(i));
        Serial.print("\n");
      }
    }
  }
  ScanNum++;

  // Wait a bit before scanning again
  delay(100);
}
