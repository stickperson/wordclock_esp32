#ifndef WORDCLOCK_H
#define WORDCLOCK_H
#include "AbstractDisplay.h"

class WordClock
{
public:
  void addDisplay(AbstractDisplay &display);

private:
  AbstractDisplay &_display;
};

#endif
