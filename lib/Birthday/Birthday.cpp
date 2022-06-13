#include "Birthday.h"


int Birthday::_determineOffset(uint8_t month, uint8_t day){
  int offset = 0;
  switch (month)
  {
    case 0:
      offset = 0;
      break;
    case 1:
      // Jan == 31 days
      offset = 31;
      break;
    case 2:
      // Feb == 29 days
      offset = 60;
      break;
    case 3:
      // March == 31
      offset = 91;
      break;
    case 4:
      // April == 30 days
      offset = 121;
      break;
    case 5:
      // May == 31 days
      offset = 152;
      break;
    case 6:
      // June == 30 days
      offset = 182;
      break;
    case 7:
      // July == 31 days
      offset = 213;
      break;
    case 8:
      // August == 31 days
      offset = 244;
      break;
    case 9:
      // September ==  274
      break;
    case 10:
      // October == 305
      break;
    case 11:
      // November == 335
      break;
    default:
      break;
  }
  offset += day - 1;
  return offset;
}

void Birthday::setBirthday(uint8_t month, uint8_t day){
  int offset = _determineOffset(month, day);
  Birthday::_birthdays |= 1 << offset;
}

bool Birthday::isBirthday(uint8_t month, uint8_t day){
  int offset = _determineOffset(month, day);
  return Birthday::_birthdays & (1 << offset);
}

uint64_t Birthday::_birthdays = 0;
