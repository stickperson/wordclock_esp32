/*
Definition file for FastLedDisplay. Note: All methods must be implemented here because of the template
*/
#ifndef WORDCLOCK_DISPLAY_FASTLED
#define WORDCLOCK_DISPLAY_FASTLED
#include <Arduino.h>
#include <FastLED.h>
#include <Preferences.h>
#include "AbstractDisplay.h"
#define MAX_BRIGHTNESS 64


template <int NUM_LEDS>
class FastLedDisplay : public AbstractDisplay
{
public:
  // Something weird happens if all this setup is done in the constructor
  // TODO: look int FastLED.setCorrection
  void setup(){
    FastLED.addLeds<APA102, 26, 27, BGR>(leds, NUM_LEDS);
    Preferences prefs;
    prefs.begin("display", true);
    currentBrightness = prefs.getUChar("brightness", MAX_BRIGHTNESS);
    prefs.end();
    FastLED.setBrightness(currentBrightness);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 2200);
    off();
    FastLED.show();
    for (int i = 0; i < 3; i++) {
      leds[12] = CRGB(255, 165, 0);
      FastLED.show();
      delay(200);
      leds[12] = CRGB::Black;
      FastLED.show();
      delay(200);
    }
  }

  void off(){
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = CRGB::Black;
    }
  }

  void tick(){
    FastLED.show();
  }

  void rainbowWord(Word word){
    fill_rainbow(
      &leds[word.startIndex], word.endIndex - word.startIndex, initialRainbow += currentRainbow, deltaRainbow
    );

    // Using EVERY_N_MILLISECONDS doesn't quite work (only a single word is displayed). This does the trick though.
    FastLED.delay(50);
  }

  void reset(){
    color = WHITE;
    FastLED.setBrightness(MAX_BRIGHTNESS);
  }

  void updateWord(Word word) override {
    int position;
    for (position = word.startIndex; position < word.endIndex; position++){
      updatePosition(position);
    }
  }

  void updatePosition(int position){
    leds[position] = color;
  }

  void changeColor(){
    color = CHSV(hue++, 255, 255);
  }

  void changeBrightness(){
    currentBrightness -= 1;
    if (currentBrightness > MAX_BRIGHTNESS){
      currentBrightness = MAX_BRIGHTNESS;
    }
    FastLED.setBrightness(currentBrightness);
    _saveBrightness();
  }

  void resetBrightness(){
    currentBrightness = MAX_BRIGHTNESS;
    FastLED.setBrightness(currentBrightness);
    FastLED.show();
    _saveBrightness();
  }

  void resetColor(){
    color = WHITE;
    FastLED.show();
  }

private:
  void _saveBrightness(){
    Preferences prefs;
    prefs.begin("display", false);
    prefs.putUChar("brightness", currentBrightness);
    prefs.end();
  }

  CRGB leds[NUM_LEDS];
  CHSV WHITE = CHSV(255, 0, 255);
  CHSV color = WHITE;
  uint8_t currentBrightness = MAX_BRIGHTNESS;
  uint8_t hue = 255;

  // Rainbow variables
  uint8_t initialRainbow = 0;
  uint8_t deltaRainbow = 16;
  uint8_t currentRainbow = 4;
};

#endif
