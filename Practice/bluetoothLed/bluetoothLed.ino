const int ledPin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    char data = Serial.read();
    switch(data) {
      case '0':
        digitalWrite(ledPin, LOW); break;
      case '1':
        analogWrite(ledPin, 25); break;
      case '2':
        analogWrite(ledPin, 50); break;
      case '3':
        analogWrite(ledPin, 75); break;
      case '4':
        analogWrite(ledPin, 100); break;
      case '5':
        analogWrite(ledPin, 125); break;
      case '6':
        analogWrite(ledPin, 150); break;
      case '7':
        analogWrite(ledPin, 175); break;
      case '8':
        analogWrite(ledPin, 200); break;
      case '9':
        analogWrite(ledPin, 255); break;
      default:
        digitalWrite(ledPin, LOW);
    }

    Serial.println(data);
  }
  delay(50);
}
