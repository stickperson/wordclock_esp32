#include "WordClock.h"
#include <Arduino.h>
#include <sys/time.h>


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
  if ((now - instance->_lastColorPressed) > 20){
    instance->_lastColorPressed = now;
    if (instance->_layout && instance->_layout->display)
    {
      instance->_layout->display->changeColor();
      instance->_setTime(true);
    }
  }
}


// TODO: stop setting the time since this makes an external call. Instead, persist the time and then call display update
void WordClock::_resetColor(void *ptr) {
  WordClock *instance = (WordClock *)ptr;
  Serial.println("restting color");
  if (instance->_layout && instance->_layout->display)
  {
    instance->_layout->display->resetColor();
  }
  instance->_setTime(true);
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
  _setTime(force);
}

void WordClock::_setTime(bool force){
  time_t current;
  time(&current);
  struct tm timeinfo;
  localtime_r(&current, &timeinfo);
  if (force || timeinfo.tm_min > _lastUpdatedMinute){

    // Call out to the NTP server every minute and sync time
    bool updateSuccessful = _timeClient.forceUpdate();
    if (updateSuccessful){
      Serial.println("Successful");
      struct timeval tv;
      tv.tv_sec = _timeClient.getEpochTime();
      tv.tv_usec = 0;
      settimeofday(&tv, NULL);
      time(&current);
      localtime_r(&current, &timeinfo);
      Serial.println(timeinfo.tm_hour);
    } else {
      Serial.println("Not successful");
    }

    _layout->display->off();
    _layout->setTime(timeinfo.tm_hour, timeinfo.tm_min);
    _lastUpdatedMinute = timeinfo.tm_min;
    if (timeinfo.tm_min == 59)
    {
      _lastUpdatedMinute = 0;
    }
  }

  if (Birthday::isBirthday(timeinfo.tm_mon, timeinfo.tm_mday))
  {
    _layout->setBirthday();
  }
  _layout->tick();
}
