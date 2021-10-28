#ifndef WORDCLOCK_H
#define WORDCLOCK_H
#include "AbstractLayout.h"

class WordClock
{
public:
  void addLayout(AbstractLayout* layout);
  void tick();

private:
  AbstractLayout* _layout;
};

#endif
