#include "WordClock.h"
#include <Arduino.h>


void WordClock::addLayout(AbstractLayout* layout){
  _layout = layout;
}

void WordClock::addBirthday(uint8_t month, uint8_t day){
  Birthday::setBirthday(month, day);
}

void WordClock::tick(){
  time_t current;
  time(&current);
  struct tm timeinfo;
  localtime_r(&current, &timeinfo);
  if (timeinfo.tm_min > _lastUpdatedMinute){
    _layout->setTime(timeinfo.tm_hour, timeinfo.tm_min);
    _lastUpdatedMinute = timeinfo.tm_min;
    if (timeinfo.tm_min == 59)
    {
      _lastUpdatedMinute = 0;
    }
  }

  if (Birthday::isBirthday(timeinfo.tm_mon, timeinfo.tm_mday)){
    _layout->setBirthday();
  }
    _layout->tick();
}


void WordClock::changeColor(){
  if (_layout && _layout->_display){
    _layout->_display->changeColor();
    time_t current;
    time(&current);
    struct tm timeinfo;
    localtime_r(&current, &timeinfo);
    _layout->setTime(timeinfo.tm_hour, timeinfo.tm_min);
    _lastUpdatedMinute = timeinfo.tm_min;
    if (timeinfo.tm_min == 59)
    {
      _lastUpdatedMinute = 0;
    }
    _layout->tick();
  }
}

void WordClock::changeBrightness(){
  if (_layout && _layout->_display){
    _layout->_display->changeBrightness();
    time_t current;
    time(&current);
    struct tm timeinfo;
    localtime_r(&current, &timeinfo);
    _layout->setTime(timeinfo.tm_hour, timeinfo.tm_min);
    _lastUpdatedMinute = timeinfo.tm_min;
    // if (timeinfo.tm_min == 59)
    // {
    //   _lastUpdatedMinute = 0;
    // }
    _layout->tick();
  }
}
