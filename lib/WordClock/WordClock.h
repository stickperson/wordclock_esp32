#ifndef WORDCLOCK_H
#define WORDCLOCK_H
#include <NTPClient.h>
#include "OneButton.h"


class AbstractLayout;
class WordClock
{
public:
  WordClock(NTPClient& timeClient, uint8_t brightnessPin=5, uint8_t colorPin=4);
  void addLayout(AbstractLayout *layout);
  void addBirthday(uint8_t month, uint8_t day);
  void tick(bool force=false);

private:
  NTPClient _timeClient;
  AbstractLayout *_layout;
  int8_t _lastUpdatedMinute = -1;
  struct tm latestTime;
  struct tm _getTime();
  void _setTime(struct tm timeInfo, bool force = false);

  // Brightness button
  OneButton _brightnessButton;
  u_long _lastBrightness = 0;
  static void _handleBrightnessPressed(void *ptr);
  static void _resetBrightness(void *ptr);

  // Color button
  OneButton _colorButton;
  u_long _lastColorPressed = 0;
  static void _handleColorPressed(void *ptr);
  static void _resetColor(void *ptr);

};

#endif
