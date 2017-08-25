/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

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
    rest.variable("timestamp",&timestamp);
    rest.variable("ESSID",&essid);
    rest.variable("Signal",&strength);
    rest.variable("BSSID",&bssid);
    rest.variable("MAC",&mac);
    
    // Function to be exposed
  
    // Give name & ID to the device (ID should be 6 characters long)
    rest.set_id("1");
    rest.set_name("esp8266");
    Serial.println("rest set");

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

    WiFiClient client = server.available();
    if (!client) { 
      return;
    }
    while(!client.available()){ //while there is no data from the client
      delay(1);
    }
    rest.handle(client); //sends stuff to the server?
    Serial.println("sending?");
  }
}

