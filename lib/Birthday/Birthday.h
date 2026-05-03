#ifndef BIRTHDAY_H
#define BIRTHDAY_H
#include <Arduino.h>

#define MAX_BIRTHDAYS 20

struct BirthdayEntry {
  uint8_t month;
  uint8_t day;
  uint16_t year;
};

struct BirthdayStore {
  uint8_t count;
  BirthdayEntry entries[MAX_BIRTHDAYS];
};

class Birthday
{
public:
  static bool isBirthday(uint8_t month, uint8_t day);
  static void setBirthday(uint8_t month, uint8_t day, uint16_t year);
  static void load();
  static void clear();
  static const BirthdayStore& store();

private:
  static void _save();
  static BirthdayStore _store;
};

#endif
