#include "EnglishLayout.h"


void EnglishLayout::setup(){
  if (_display)
}

void EnglishLayout::update(int hour, int minute){
  minute = minute / 5;
}

void EnglishLayout::addDisplay(AbstractDisplay& display){
  _display = display;
}


int EnglishLayout::time_it_is[4] = {0, 1, 3, 4};

int EnglishLayout::time_minutes[11][22] = {
    {124, 125, 126, 127, 128, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {26, 27, 28, 29, 31, 32, 33, 34, 35, 36, 37, 48, 49, 50, 51, -1, -1, -1, -1, -1, -1, -1},
    {6, 7, 8, 31, 32, 33, 34, 35, 36, 37, 38, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {13, 14, 15, 16, 17, 18, 19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {124, 125, 126, 127, 128, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {124, 125, 126, 127, 128, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {124, 125, 126, 127, 128, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {124, 125, 126, 127, 128, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {124, 125, 126, 127, 128, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {124, 125, 126, 127, 128, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {124, 125, 126, 127, 128, 129, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

int EnglishLayout::time_hours[12][10] = {
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
};
