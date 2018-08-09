/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

const int NUM_LEDS = 4;
const int LEDS[] = {2, 3, 4, 5};



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
    for (int i = 0; i < NUM_LEDS; i++) {
      pinMode(LEDS[i], OUTPUT);
    }
}

// the loop function runs over and over again forever
void loop() {

  // Pattern Left to Right  
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LEDS[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(LEDS[i], LOW);    // turn the LED off by making the voltage LOW
  }

  // Pattern Right to Left
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    digitalWrite(LEDS[i], HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(LEDS[i], LOW);    // turn the LED off by making the voltage LOW
  }

//  dah();
//  dit();
//  dah();
//  delay(1200);
//  dah();
//  dit();
//  dah();
//  dit();
//  delay(1200);
}

void dah() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LEDS[i], HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  delay(400);                       // wait for a second
  for (int i = 0; i < 3; i++) {
    digitalWrite(LEDS[i], LOW);   // turn the LED on (HIGH is the voltage level)
  }
  delay(400); 
}

void dit() {
  digitalWrite(LEDS[0], HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(400);                       // wait for a second
  digitalWrite(LEDS[0], LOW);   // turn the LED on (HIGH is the voltage level)
  delay(400); 
}

