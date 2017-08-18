void setup() {
  Serial.begin(115200);
 
}

void loop() {
  while (!Serial){}

  Serial.println("sleeptime");
  ESP.deepSleep(1e7);
  delay(2000);
  Serial.println("woke up");

}
