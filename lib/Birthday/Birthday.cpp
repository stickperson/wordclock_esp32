#include "Birthday.h"


void Birthday::setBirthday(uint8_t month, uint8_t day){
  Birthday::_birthdays[month][day - 1] = true;
}

bool Birthday::isBirthday(uint8_t month, uint8_t day){
  return Birthday::_birthdays[month][day - 1] == true;
}

bool Birthday::_birthdays[12][31] = {};
