#ifndef WORD_H
#define WORD_H
#include <Arduino.h>

struct Word {
  uint8_t startIndex;
  uint8_t endIndex;
};

inline bool operator==(const Word& w1, const Word& w2){
  return (w1.startIndex == w2.startIndex && w1.endIndex == w2.endIndex);
};

#endif
