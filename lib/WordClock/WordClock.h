#ifndef WORDCLOCK_H
#define WORDCLOCK_H
#include <NTPClient.h>
#include "AbstractLayout.h"
#include "Birthday.h"

class WordClock
{
public:
  WordClock(NTPClient& timeClient);
  void addLayout(AbstractLayout *layout);
  void addBirthday(uint8_t month, uint8_t day);
  void changeColor();
  void changeBrightness();
  void tick(bool force=false);

private:
  NTPClient _timeClient;
  AbstractLayout *_layout;
  int8_t _lastUpdatedMinute = -1;
};

#endif
