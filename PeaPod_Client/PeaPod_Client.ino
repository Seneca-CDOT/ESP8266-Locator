#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>

#define END_POINT       "http://206.47.241.9:8090/"
// WiFi parameters
const char* ssid = "peapod";
const char* password = "geolocation";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

#define HAPPY      14
#define SAD        13
#define MEH        12

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API

void setup() {
  
  pinMode(HAPPY, INPUT_PULLUP);
  pinMode(SAD, INPUT_PULLUP);
  pinMode(MEH, INPUT_PULLUP);

  // put your main code here, to run repeatedly:
 


  // Start Serial
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void DeepSleep(unsigned int seconds)
{
  ESP.deepSleep(1e6*seconds);
}

void wifi_request(String end_pt, String msg) {
    HTTPClient http;
    //if (end_pt == HTTP_DEV_WIFI_SCAN_ENDPT)
    //   http.setTimeout(30000);
    http.begin(end_pt);

    http.addHeader("Content-Type", "text/plain");
    //add headers as needed

    int httpCode = http.POST(msg);
    //DEBUG_PRINTF("HTTP CODE WAS: %d\n", httpCode);

    Serial.print("HTTP Code = ");
    Serial.println(httpCode);

    if (httpCode == HTTP_CODE_OK){
        String payload = http.getString();
    }   
    else if (httpCode > -1){
        String payload=http.getString();
    }   
    http.end();

}

void POST(String msg)
{
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  
  wifi_request(END_POINT, msg);
}

String getPostMSG()
{
  String TimeStamp;
  String mac;
  String MacList;
  String Signals;
  String SSIDs;
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  int n = WiFi.scanNetworks();
  if(n == 0)
    Serial.println("no networks found");
  else
  {
    TimeStamp = (String)millis();
    mac = WiFi.macAddress();

    for(int i = 0; i < n; i++)
    {
      if(i != n-1)
      {
        SSIDs = SSIDs + WiFi.SSID(i) + ",";
        MacList = MacList + WiFi.BSSIDstr(i) + ",";
        Signals = Signals + WiFi.RSSI(i) + ",";
      }
      else
      {
        SSIDs = SSIDs + WiFi.SSID(i);
        MacList = MacList + WiFi.BSSIDstr(i);
        Signals = Signals + WiFi.RSSI(i);
      }
    }
  }
  return TimeStamp + "\n" + mac + "\n" + SSIDs + "\n" + Signals + "\n" + MacList;
  
}

void loop() {
  if(digitalRead(13) == LOW) Serial.println(":(");
  if(digitalRead(12) == LOW) Serial.println(":|");
  if(digitalRead(14) == LOW) Serial.println(":)");
  
  POST(getPostMSG());
  DeepSleep(300);
}



