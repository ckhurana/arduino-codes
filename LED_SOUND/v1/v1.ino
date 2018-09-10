const int ledPin = 3;
const int soundPin = A0;
const int soundDPin = 8;
const int threshold = 300;

int soundVal = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(soundPin, INPUT);
  pinMode(soundDPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  soundVal = analogRead(soundPin);

  int soundDVal = digitalRead(soundDPin);
  Serial.print(soundVal);
  Serial.print(" : ");
  Serial.println(soundDVal);

//  analogWrite(ledPin, soundVal / 4);

  if(soundVal >= threshold) {
    digitalWrite(ledPin, HIGH);
//    delay(20);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
