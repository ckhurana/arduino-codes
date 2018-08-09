const int ledPin = 13;
const int soundPin = A0;
const int threshold = 300;

int soundVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(soundPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  soundVal = analogRead(soundPin);
  Serial.println(soundVal);

  if(soundVal >= threshold) {
    digitalWrite(ledPin, HIGH);
    delay(20);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
