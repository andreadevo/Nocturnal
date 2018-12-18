#include <Adafruit_NeoPixel.h>

// declare pins
const int neoPinA = 6;
const int neoPinB = 7;
const int neoPinM = 8;
const int pirPin = 3;

// declare number of lights for each strip
const int numLightsA = 6;
const int numLightsB = 5;
const int numLightsM = 5;

// declare variable to track time
unsigned long startTime;

// declare on/off state
int onA;
int onB;
int onM;
int offA;
int offB;
int offM;

// declare random varibales for flicker
int randA;
int randB;

// declare instances of each strip
Adafruit_NeoPixel stripA = Adafruit_NeoPixel(numLightsA, neoPinA, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripB = Adafruit_NeoPixel(numLightsB, neoPinB, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripM = Adafruit_NeoPixel(numLightsM, neoPinM, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // initialize motion sensor as an input
  pinMode(pirPin, INPUT);

  // initialize pixels
  stripA.begin();
  stripB.begin();
  stripM.begin();

  // initlize pixels to be off
  stripA.show();
  stripB.show();
  stripM.show();

  // save on state for each strand
  onA = stripA.Color(248, 228, 182);
  onB = stripB.Color(248, 228, 182);
  onM = stripB.Color(255, 255, 255);

  // save off state for each strand
  offA = stripA.Color(0, 0, 0);
  offB = stripB.Color(0, 0, 0);
  offM = stripM.Color(0, 0, 0);
}

void loop() {
  if (digitalRead(pirPin) == HIGH) {
    // set colors for all neopixels
    setColorsA(onA);
    setColorsB(onB);
    setColorsM(onM);

    // start clock to track time
    startTime = millis();

    // first turn on moon
    stripM.setBrightness(250);
    stripM.show();

    // then start tracking time and flicker lights
    while (millis() - startTime < 30000) {
      stripA.setBrightness(50);
      stripB.setBrightness(150);
      stripA.show();
      stripB.show();
      delay(100);
      flicker();
    }

    // after 30 seconds, turn off all lights
    setColorsA(offA);
    setColorsB(offB);
    setColorsM(offM);
    stripA.show();
    stripB.show();
    stripM.show();
  }
}

void flicker() {
  randA = random(0, 7);   // 6 total neopixels
  randB = random(0, 6);   // 5 total neopixels
  // turn blue
  stripA.setPixelColor(randA, 42, 62, 88);
  stripB.setPixelColor(randB, 42, 62, 88);
  stripA.show();
  stripB.show();
  delay(100);
  // turn red
  stripA.setPixelColor(randA, 219, 92, 78);
  stripB.setPixelColor(randB, 219, 92, 78);
  stripA.show();
  stripB.show();
  delay(100);
  // turn blue
  stripA.setPixelColor(randA, 248, 228, 182);
  stripB.setPixelColor(randB, 248, 228, 182);
  stripA.show();
  stripB.show();
  delay(50);
}

void setColorsA(uint32_t c) {
  for (uint16_t i = 0; i < stripA.numPixels(); i++) {
    stripA.setPixelColor(i, c);
  }
}

void setColorsB(uint32_t c) {
  for (uint16_t i = 0; i < stripB.numPixels(); i++) {
    stripB.setPixelColor(i, c);
  }
}

void setColorsM(uint32_t c) {
  for (uint16_t i = 0; i < stripM.numPixels(); i++) {
    stripM.setPixelColor(i, c);
  }
}
