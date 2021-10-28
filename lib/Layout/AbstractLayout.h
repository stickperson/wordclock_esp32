#include <Arduino.h>
#include "AbstractDisplay.h"
#ifndef WORDCLOCK_LAYOUT_H
#define WORDCLOCK_LAYOUT_H


class AbstractLayout
{
public:
  virtual void tick() = 0;
  virtual void addDisplay(AbstractDisplay* display);
  // virtual void update(int hour, int minute) = 0;
  AbstractDisplay* _display;
  static const int NUM_LEDS = 130;

protected:
};

#endif
