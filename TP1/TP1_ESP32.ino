void setup() {
  Serial.begin(115200);
}

void loop() {
  int valeur = random(0, 100);
  Serial.println(valeur);
  delay(2000);
}
