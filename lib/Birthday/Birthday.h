#ifndef BIRTHDAY_H
#define BIRTHDAY_H
#include <Arduino.h>


class Birthday
{
public:
  static bool isBirthday(uint8_t month, uint8_t day);
  static void setBirthday(uint8_t month, uint8_t day);

private:
  static int _determineOffset(uint8_t month, uint8_t day);

  // TODO persist this in case of power failure
  static uint64_t _birthdays;
};

#endif
