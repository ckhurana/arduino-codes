#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    6
//#define CLK_PIN   4
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    26


#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120


#define SOUND_PIN A0

#define MAX_SOUND 800.0
#define MIN_SOUND 8.0


#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


CRGB leds[NUM_LEDS];
int soundVal = 0;

CRGB lastColor;
int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SOUND_PIN, INPUT);
  delay(3000); // 3 second delay for recovery
  lastColor = randomColor();
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
typedef void (*SingleParamPatternList[])(int sountVal);
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

SingleParamPatternList sPatterns = { intensityReact };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


char led_mode = '0';
void loop()
{
  if (Serial.available() > 0) {
    led_mode = Serial.read();
    Serial.println(led_mode);
  }
  if (led_mode >= '0' && led_mode <= '9') {
    soundVal = analogRead(SOUND_PIN);
    int led_smode = (led_mode - '0') % ARRAY_SIZE(sPatterns);
    sPatterns[led_smode](soundVal);
    //      Serial.println("Sound Mode: &d : SVal = &d", led_smode, soundVal);
  } else {
    if (led_mode == 'a') {
      gPatterns[gCurrentPatternNumber]();
      EVERY_N_SECONDS( 10 ) {
        nextPattern();  // change patterns periodically
      }
    } else {
      int led_gmode = (led_mode - 'b') % ARRAY_SIZE(gPatterns);
      // Call the current pattern function once, updating the 'leds' array
      gPatterns[led_gmode]();
    }
    // send the 'leds' array out to the actual LED strip
    FastLED.show();
    // insert a delay to keep the framerate modest
    FastLED.delay(1000 / FRAMES_PER_SECOND);
    // do some periodic updates
    EVERY_N_MILLISECONDS( 20 ) {
      gHue++;  // slowly cycle the "base color" through the rainbow
    }
  }
  FastLED.show();

}

void intensityReact(int sVal) {
  if (++counter > 6000) {
    lastColor = randomColor();
    counter = 0;
  }
  float perc = (float) sVal / MAX_SOUND;

  CRGB colV;
  if ( perc > 0.1) {
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

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter)
{
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS - 1 );
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16( i + 7, 0, NUM_LEDS - 1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
