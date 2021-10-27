#include <Arduino.h>
#include "AbstractDisplay.h"
#ifndef WORDCLOCK_LAYOUT_H
#define WORDCLOCK_LAYOUT_H


template <size_t NUM_LEDS>
class AbstractLayout
{
public:
  virtual void setup() = 0;
  virtual void addDisplay(AbstractDisplay &display) = 0;
  virtual void update(int hour, int minute) = 0;

protected:
  AbstractDisplay& _display;
};

#endif
