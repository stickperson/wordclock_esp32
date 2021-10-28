#ifndef WORDCLOCK_TEST_LAYOUT_H
#define WORDCLOCK_TEST_LAYOUT_H
#include "AbstractLayout.h"

class TestLayout : public AbstractLayout
{
public:
  void tick() override {
    x = 1;
  };

  int x;

  // void update(int hour, int minute) override;
  static const int NUM_LEDS = 10;
};

#endif
