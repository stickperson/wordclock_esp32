#ifndef WORDCLOCK_ABSTRACT_DISPLAY_H
#define WORDCLOCK_ABSTRACT_DISPLAY_H
#include "Word.h"


class AbstractDisplay
{
public:
  virtual void tick() = 0;
  virtual void changeBrightness(){};
  virtual void changeColor(){};
  virtual void setup(){};
  virtual void off(){};
  virtual void updatePosition(int position) = 0;
  virtual void rainbowWord(Word word) = 0;
  virtual void resetBrightness(){};
  virtual void resetColor(){};
  virtual void updateWord(Word word) = 0;

protected:

};

#endif
