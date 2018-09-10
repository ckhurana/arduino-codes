#include <FastLED.h>

#define NUM_LEDS 26

// Data pin that led data will be written out over
#define DATA_PIN 6
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

#define SOUND_PIN A0

#define MAX_SOUND 786.0
#define MIN_SOUND 8.0

CRGB leds[NUM_LEDS];
int soundVal = 0;

CRGB lastColor;
int counter = 0;


void setup() {
  Serial.begin(9600);
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  pinMode(SOUND_PIN, INPUT);
  delay(3000);
  lastColor = randomColor();
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {

  soundVal = analogRead(SOUND_PIN);
  //  Serial.println(soundVal);

  //  audio_1(soundVal);

  audio_2(soundVal);
}

void audio_2(int sVal) {
  if (++counter > 6000) {
    lastColor = randomColor();
    counter = 0;
  }
  float perc = (float) sVal / MAX_SOUND;

  CRGB colV;
  if( perc > 0.1) {
//   Serial.println(sVal);
    Serial.println(perc); 
    colV = dimColor(lastColor, perc);
  } else {
    colV = dimColor(lastColor, (5 + random(5)) / 100.0);
  }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = colV;
  }
  FastLED.show();
  delay(10);
}

CRGB dimColor(CRGB c, float perc) {
  return CRGB (c.r * perc, c.g * perc, c.b * perc);
}

void audio_1(int sVal) {
  Serial.println(sVal);
  if (sVal < 250) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
    }
  } else if (sVal >= 250 && sVal < 450) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i < 1)
        leds[i] = CRGB(0, 255, 255);
      else
        leds[i] = CRGB(0, 0, 0);
    }
  } else if (sVal >= 450 && sVal < 650) {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i < 2)
        leds[i] = CRGB(255, 0, 255);
      else
        leds[i] = CRGB(0, 0, 0);
    }
  } else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(255, 255, 0);
    }
  }
  FastLED.show();
  delay(10);
}

void lightning(CRGB c, int simultaneous, int cycles, int speed) {
  int flashes[simultaneous];

  for (int i = 0; i < cycles; i++) {
    for (int j = 0; j < simultaneous; j++) {
      int idx = random(NUM_LEDS);
      flashes[j] = idx;
      leds[idx] = c ? c : randomColor();
    }
    FastLED.show();
    delay(speed);
    for (int s = 0; s < simultaneous; s++) {
      leds[flashes[s]] = CRGB::Black;
    }
    delay(speed);
  }
}

void rainbowCycle(int wait, int cycles, int dim) {

  //loop several times with same configurations and same delay
  for (int cycle = 0; cycle < cycles; cycle++) {

    byte dir = random(0, 2);
    int k = 255;

    //loop through all colors in the wheel
    for (int j = 0; j < 256; j++, k--) {

      if (k < 0) {
        k = 255;
      }

      //Set RGB color of each LED
      for (int i = 0; i < NUM_LEDS; i++) {

        CRGB ledColor = wheel(((i * 256 / NUM_LEDS) + (dir == 0 ? j : k)) % 256, dim);
        leds[i] = ledColor;

      }

      FastLED.show();
      FastLED.delay(wait);
    }
  }

}

CRGB wheel(int WheelPos, int dim) {
  CRGB color;
  if (85 > WheelPos) {
    color.r = 0;
    color.g = WheelPos * 3 / dim;
    color.b = (255 - WheelPos * 3) / dim;;
  }
  else if (170 > WheelPos) {
    color.r = WheelPos * 3 / dim;
    color.g = (255 - WheelPos * 3) / dim;
    color.b = 0;
  }
  else {
    color.r = (255 - WheelPos * 3) / dim;
    color.g = 0;
    color.b = WheelPos * 3 / dim;
  }
  return color;
}

CRGB Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

CRGB randomColor() {
  return Wheel(random(256));
}
