#ifndef WORDCLOCK_ABSTRACT_DISPLAY_H
#define WORDCLOCK_ABSTRACT_DISPLAY_H

class AbstractDisplay
{
public:
  virtual void setup(int NUM_LEDS) = 0;
  virtual void update() = 0;
};

#endif
