#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *SERVER_WIFI_SSID = "ESP8266-Dragon";
const char *SERVER_WIFI_PASS = "DragonFruit";



void setupWiFi()
{
   Serial.print("Connecting to WiFi ");
   WiFi.begin(SERVER_WIFI_SSID,SERVER_WIFI_PASS);
   while(WiFi.status() != WL_CONNECTED)
   {
     delay(500);
     Serial.print(".");
   }

   Serial.println("Connected");
}

void setup() {
  Serial.begin(115200);
  setupWiFi();

}

void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient http;

  //Let is try a GET request first 
  http.begin("http://192.168.0.104:8080/webappfordemo/Version");

  int httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK)
  {
      Serial.print("HTTP response code ");
      Serial.println(httpCode);
      String response = http.getString();
      Serial.println(response);
    
  }
  else
  {
    Serial.println("Error in HTTP request");
  }

  http.end();

  delay(3000);

}
