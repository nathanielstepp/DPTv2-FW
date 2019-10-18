int CD_PIN = 9;
int VAL = 0;

void setup() {
  pinMode(CD_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  VAL = digitalRead(9);
  Serial.println(VAL);
  delay(10);
}
