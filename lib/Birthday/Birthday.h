#ifndef BIRTHDAY_H
#define BIRTHDAY_H
#include <Arduino.h>


class Birthday
{
public:
  static bool isBirthday(uint8_t month, uint8_t day);
  static void setBirthday(uint8_t month, uint8_t day);

private:
  // TODO persist this in case of power failure
  static bool _birthdays[12][31];
};

#endif
