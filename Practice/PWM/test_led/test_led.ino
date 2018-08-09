
const int LED_PIN = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i <= 255; i++) {
    analogWrite(LED_PIN, i);
    delay(5);
  }
  delay(200);
}
