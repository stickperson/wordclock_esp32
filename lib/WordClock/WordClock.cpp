#include <Arduino.h>
#include <sys/time.h>
#include "AbstractLayout.h"
#include "Birthday.h"
#include "WordClock.h"



WordClock::WordClock(NTPClient& timeClient, uint8_t brightnessPin, uint8_t colorPin)
: _timeClient(timeClient),
  _brightnessButton(brightnessPin, true, true),
  _colorButton(colorPin, true, true)
{
  _brightnessButton.attachDuringLongPress(WordClock::_handleBrightnessPressed, this);
  _brightnessButton.attachClick(WordClock::_resetBrightness, this);
  _colorButton.attachDuringLongPress(WordClock::_handleColorPressed, this);
  _colorButton.attachClick(WordClock::_resetColor, this);
}


void WordClock::_handleColorPressed(void *ptr){
  WordClock *instance = (WordClock *)ptr;
  u_long now = millis();
  if ((now - instance->_lastColorPressed) > 100){
    instance->_lastColorPressed = now;
    if (instance->_layout && instance->_layout->display)
    {
      instance->_layout->display->changeColor();
      struct tm currentTime = instance->_getTime();
      instance->_layout->display->off();
      instance->_layout->setTime(currentTime.tm_hour, currentTime.tm_min);
    }
  }
}


void WordClock::_resetColor(void *ptr) {
  WordClock *instance = (WordClock *)ptr;
  Serial.println("restting color");
  if (instance->_layout && instance->_layout->display)
  {
    instance->_layout->display->resetColor();
    struct tm currentTime = instance->_getTime();
    instance->_layout->display->off();
    instance->_layout->setTime(currentTime.tm_hour, currentTime.tm_min);
  }
}

void WordClock::_handleBrightnessPressed(void *ptr) {

  WordClock *instance = (WordClock *)ptr;
  u_long now = millis();
  if ((now - instance->_lastBrightness) > 100){
    instance->_lastBrightness = now;
    if (instance->_layout && instance->_layout->display){
      instance->_layout->display->changeBrightness();
    }
  }
}

void WordClock::_resetBrightness(void *ptr) {
  WordClock *instance = (WordClock *)ptr;
  if (instance->_layout && instance->_layout->display){
    instance->_layout->display->resetBrightness();
  }
}

void WordClock::addLayout(AbstractLayout* layout){
  _layout = layout;
}

void WordClock::addBirthday(uint8_t month, uint8_t day){
  Birthday::setBirthday(month, day);
}

void WordClock::tick(bool force){
  _brightnessButton.tick();
  _colorButton.tick();
  struct tm currentTime = WordClock::_getTime();
  _setTime(currentTime, force);
  _layout->tick();
}

struct tm WordClock::_getTime(){
  time_t current;
  time(&current);
  struct tm timeinfo;
  localtime_r(&current, &timeinfo);
  return timeinfo;
}

void WordClock::_setTime(struct tm timeInfo, bool force){
  if (force || timeInfo.tm_min > _lastUpdatedMinute){

    // Call out to the NTP server every minute and sync time
    bool updateSuccessful = _timeClient.forceUpdate();
    if (updateSuccessful){
      Serial.println("Successful");
      struct timeval tv;
      tv.tv_sec = _timeClient.getEpochTime();
      tv.tv_usec = 0;
      time_t current;
      settimeofday(&tv, NULL);
      time(&current);
      localtime_r(&current, &timeInfo);
      Serial.println(timeInfo.tm_hour);
    } else {
      Serial.println("Not successful");
    }

    _layout->display->off();
    _layout->setTime(timeInfo.tm_hour, timeInfo.tm_min);
    _lastUpdatedMinute = timeInfo.tm_min;
    if (timeInfo.tm_min == 59)
    {
      _lastUpdatedMinute = 0;
    }
  }

  if (Birthday::isBirthday(timeInfo.tm_mon, timeInfo.tm_mday))
  {
    _layout->setBirthday();
  }
}
