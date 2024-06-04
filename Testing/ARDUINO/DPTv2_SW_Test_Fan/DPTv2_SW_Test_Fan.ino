int FAN_PIN = 5;

void setup() {
  pinMode(FAN_PIN, OUTPUT);
}

void loop() {
  digitalWrite(FAN_PIN,LOW);
  delay(2000);
  digitalWrite(FAN_PIN,HIGH);
  delay(5000);
}
