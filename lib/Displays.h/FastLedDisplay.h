#ifndef WORDCLOCK_DISPLAY_FASTLED
#include "AbstractDisplay.h"
#include <FastLED.h>
#define WORDCLOCK_DISPLAY_FASTLED

template <int NUM_LEDS>
class FastLedDisplay : public AbstractDisplay
{
public:
  FastLedDisplay<NUM_LEDS>(){
    FastLED.addLeds<APA102, 26, 27, BGR>(leds, NUM_LEDS);
    FastLED.setBrightness(64);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 2200);
  }

  void tick(){
    FastLED.show();
  }

  void updatePosition(int position){
    leds[position] = position;
  }

private:
  CRGB leds[NUM_LEDS];
};

#endif
