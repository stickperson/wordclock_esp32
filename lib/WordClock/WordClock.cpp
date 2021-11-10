#include "WordClock.h"
#include <Arduino.h>
#include <sys/time.h>


WordClock::WordClock(NTPClient& timeClient)
:  _timeClient(timeClient)
{

}

void WordClock::addLayout(AbstractLayout* layout){
  _layout = layout;
}

void WordClock::addBirthday(uint8_t month, uint8_t day){
  Birthday::setBirthday(month, day);
}

void WordClock::tick(bool force){
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

void WordClock::changeColor(){
  if (_layout && _layout->display){
    _layout->display->changeColor();
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
  if (_layout && _layout->display){
    _layout->display->changeBrightness();
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
