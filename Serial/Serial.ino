

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(13) == LOW) Serial.println(":(");
  if(digitalRead(12) == LOW) Serial.println(":|");
  if(digitalRead(14) == LOW) Serial.println(":)");
  delay(20);
}
