#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "ESP8266-Dragon";
const char* password = "DragonFruit";

WiFiUDP UDPTestServer;
unsigned int UDPPort = 5005;

const int packetSize = 2;
byte packetBuffer[packetSize];

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  UDPTestServer.begin(UDPPort);
 
}

int value = 0;

void loop() {
   handleUDPServer();
   delay(1);
}

void handleUDPServer() {
  int cb = UDPTestServer.parsePacket();
  if (cb) {
    Serial.println("hello");
    UDPTestServer.read(packetBuffer, packetSize);
    String myData = "";
    for(int i = 0; i < packetSize; i++) {
      myData += (char)packetBuffer[i];
    }
    Serial.println(myData);
  }
}
