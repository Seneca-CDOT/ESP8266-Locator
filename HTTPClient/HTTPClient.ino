/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>


// WiFi parameters
const char* ssid = "ESP8266-Dragon";
const char* password = "DragonFruit";

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int timestamp;
String mac;
String essid;
String strength;
String bssid;

// Declare functions to be exposed to the API
void getData();

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

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

void loop() {
  getData();

  // Handle REST calls
  delay(60*1000);

}

void getData(){
  //Disconnect to scan
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("disconnect");
  //scans for networks
  int n = WiFi.scanNetworks(); //n = number of networks found when scanning
  if (n == 0)
    Serial.println("no networks found");
  else{
    // Init variables and expose them to REST API
    timestamp = millis();
    mac = WiFi.macAddress();
    essid = "";
    for (int i = 0; i < n; ++i)
      {
        essid = essid + WiFi.SSID(i);
        if (i != n-1){
          essid = essid + ",";
        }   
      }
    strength = "";
    for (int i = 0; i < n; ++i)
      {
        strength = strength + String(WiFi.RSSI(i));
        if (i != n-1){
          strength = strength + ",";
        }   
      }
    bssid = "";
    for (int i = 0; i < n; ++i)
      {
        bssid = bssid + WiFi.BSSIDstr(i);
        if (i != n-1){
          bssid = bssid + ",";
        }   
      }


    delay(5000);

    //Connects  to WiFi
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

    wifi_request(String(WiFi.localIP()), "Hello Word!", mac, timestamp);
  }
}


void wifi_request(String end_pt, String msg, String mac, int timeStamp) {
    HTTPClient http;
    //if (end_pt == HTTP_DEV_WIFI_SCAN_ENDPT)
    //   http.setTimeout(30000);
    http.begin(end_pt);

    http.addHeader("Content-Type", "MAC: %s\nTimeStamp: %f", mac, timeStamp);
    //add headers as needed

    int httpCode = http.POST(msg);
    //DEBUG_PRINTF("HTTP CODE WAS: %d\n", httpCode);


    if (httpCode == HTTP_CODE_OK){
        String payload = http.getString();
    }   
    else if (httpCode > -1){
        String payload=http.getString();
    }   
    http.end();

}

