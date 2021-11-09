#ifndef WORDCLOCK_H
#define WORDCLOCK_H
#include "AbstractLayout.h"
#include "Birthday.h"

class WordClock
{
public:
  void addLayout(AbstractLayout* layout);
  void addBirthday(uint8_t month, uint8_t day);
  void changeColor();
  void changeBrightness();
  void tick(bool force=false);

private:
  AbstractLayout* _layout;
  int8_t _lastUpdatedMinute = -1;
};

#endif
