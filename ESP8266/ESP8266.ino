/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


#define END_POINT       "http://206.47.241.9:8090/"
// WiFi parameters
const char* ssid = "peapod";
const char* password = "geolocation";

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
  

  

  wifi_request(END_POINT, "213291\n5C:CF:7F:1A:06:1F\nSenecaGuest,SenecaNET,DIRECT-eb-HP M102 LaserJet,hpsetup,Opilio,SenecaNET,SenecaGuest,twinster\n-64,-63,-78,-85,-73,-73,-73,-85\n0C:27:24:93:CA:D0,0C:27:24:93:CA:D3,92:CD:B6:07:E8:EB,00:14:38:DA:50:15,00:21:79:C8:52:50,0C:27:24:93:61:C3,0C:27:24:93:61:C0,00:21:79:C8:29:70");
  Serial.print("sent post on ");
  Serial.println(END_POINT);

  delay(10000);

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


