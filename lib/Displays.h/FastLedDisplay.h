#include "AbstractDisplay.h"

#ifndef WORDCLOCK_DISPLAY_FASTLED
#define WORDCLOCK_DISPLAY_FASTLED

class FastLedDisplay : public AbstractDisplay
{
public:
  void setup(int NUM_LEDS) override;
};

#endif
