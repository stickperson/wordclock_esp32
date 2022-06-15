#include "Birthday.h"


int16_t Birthday::_determineOffset(uint8_t month, uint8_t day){
  int16_t offset = 0;
  return month * 31 + day - 1;
}

void Birthday::setBirthday(uint8_t month, uint8_t day){
  int offset = _determineOffset(month, day);
  Birthday::_birthdays |= 1 << offset;
}

bool Birthday::isBirthday(uint8_t month, uint8_t day){
  int16_t offset = _determineOffset(month, day);
  return Birthday::_birthdays & (1 << offset);
}

int16_t Birthday::_birthdays = 0;
