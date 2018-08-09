#define piezoPin 3
int del = 500;
void setup() {
  // put your setup code here, to run once:
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(piezoPin, 200);
  delay(del);
  digitalWrite(piezoPin, LOW);
  delay(del);
}
