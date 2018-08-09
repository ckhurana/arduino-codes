const int ledPin = 3;
const int ldrPin = A0;
int ldrValue = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
  analogWrite(ledPin, ldrValue / 2);

  delay(20);
}
