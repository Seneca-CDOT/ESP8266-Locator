#include <ESP8266WiFi.h>

//////////////////////
// WiFi Definitions //
//////////////////////

/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = 5; // Thing's onboard, green LED
const int ANALOG_PIN = A0; // The only analog pin on the Thing
const int DIGITAL_PIN = 12; // Digital pin to be read

WiFiServer server(80);

void setup() 
{
  initHardware();
  setupWiFi();
  server.begin();
}

void loop() 
{
  Serial.println("123456789");
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("/led/") == -1)
  {
    digitalWrite(0, HIGH);
  }
  else
  {
    digitalWrite(0, LOW);
  }
  
  client.flush();

  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";

  s += "Hello";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP8266-Dragon", "DragonFruit");
}

void initHardware()
{
  Serial.begin(115200);
  pinMode(0, OUTPUT);
  // Don't need to set ANALOG_PIN as input, 
  // that's all it can be.
}
