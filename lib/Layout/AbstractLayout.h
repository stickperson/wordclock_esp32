#ifndef WORDCLOCK_LAYOUT_H
#include "AbstractDisplay.h"
#define WORDCLOCK_LAYOUT_H


class AbstractLayout
{
public:
  virtual void tick() = 0;
  virtual void addDisplay(AbstractDisplay* display);
  virtual void setBirthday(bool flag) = 0;
  virtual void setTime(int hour, int minute) = 0;
  AbstractDisplay* display;
  int NUM_LEDS;
};

#endif
