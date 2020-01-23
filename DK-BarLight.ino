#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

Adafruit_NeoPixel strip = Adafruit_NeoPixel(28, 9, NEO_GRB + NEO_KHZ800);

#define REED_SWITCH 10

void setup() {
  pinMode(REED_SWITCH, INPUT_PULLUP);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  clearStrip();
}

void loop() {

  if(digitalRead(REED_SWITCH) == LOW) {
      clearStrip();
  } else {
      colorWipe(strip.Color(30, 10, 1), 50); // Warm white reveal
      warmWhiteCycle(80);

      if(digitalRead(REED_SWITCH) == HIGH) {
        colorWipe(strip.Color(255, 0, 0), 80); // Red reveal
        delay(2000);
        redCycle(80);
      }

      if(digitalRead(REED_SWITCH) == HIGH) {
        colorWipe(strip.Color(30, 10, 1), 80); // Warm white reveal
        warmWhiteCycle(80);
      }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    
    // Bright warm white wipe leader pxiel
    if(i < strip.numPixels())
      strip.setPixelColor(i+1, strip.Color(255, 40, 10));
    
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos, WheelPos / 3, 1);
  }
  if(WheelPos < 90) { // white chaser
    WheelPos -= 85;
    return strip.Color(255, 40, 30 - WheelPos);
  }
  WheelPos -= 90;
  return strip.Color(255, WheelPos / 3, 0);
}

void clearStrip() {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}

void warmWhiteCycle(uint8_t wait) {
  uint16_t i, j;
  
  for(j=0; j<128; j++) {
    for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color((i+j) / 2 + 30, (i+j) / 6 + 10, 1));
        //strip.setPixelColor(i, strip.Color(128, 40, 1)); // Warm white
    }
    strip.show();
    
    if(digitalRead(REED_SWITCH) == LOW) return;
    delay(wait);
  }
  for(j=128; j>0; j--) {
    for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color((i+j) / 2 + 30, (i+j) / 6 + 10, 1));
    }
    strip.show();
    
    if(digitalRead(REED_SWITCH) == LOW) return;
    delay(wait);
  } 
}

void redCycle(uint8_t wait) {
  uint16_t i, j;
  
  for(j=0; j<128; j++) {
    for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255 - ((i+j) / 3), (i+j) / 16, 0));
    }
    strip.show();
    
    if(digitalRead(REED_SWITCH) == LOW) return;
    delay(wait);
  }
  for(j=128; j>0; j--) {
    for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255 -((i+j) / 3), (i+j) / 16, 0));
    }
    strip.show();
    
    if(digitalRead(REED_SWITCH) == LOW) return;
    delay(wait);
  } 
}
