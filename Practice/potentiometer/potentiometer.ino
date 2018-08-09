const int ledPin = 3;
const int potPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(potPin);

  Serial.println(potVal);
  analogWrite(ledPin, potVal / 4);

  delay(20);
}
