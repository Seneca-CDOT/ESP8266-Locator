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

void setup(void)
{
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

void loop() {
  

  

  wifi_request(String(WiFi.localIP()), "Hola me llamo Ethan");
  Serial.print("sent post on ");
  Serial.println(WiFi.localIP());

  delay(10000);

}







void wifi_request(String end_pt, String msg) {
    HTTPClient http;
    //if (end_pt == HTTP_DEV_WIFI_SCAN_ENDPT)
    //   http.setTimeout(30000);
    http.begin(end_pt);

    http.addHeader("Content-Type", "yo dope");
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


