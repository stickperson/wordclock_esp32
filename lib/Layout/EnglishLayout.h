#ifndef WORDCLOCK_TEST_LAYOUT_H
#define WORDCLOCK_TEST_LAYOUT_H
#include "AbstractLayout.h"

#define IT Word{11, 13}
#define IS Word{8, 10}
#define MTEN Word{4, 7}
#define HALF Word{0, 4}
#define QUARTER Word{13, 20}
#define TWENTY Word{20, 26}
#define MFIVE Word{35, 39}
#define MINUTES Word{27, 34}
#define HAPPY Word{39, 44}
#define TO Word{45, 47}
#define PAST Word{48, 52}
#define ONE Word{62, 65}
#define BIRTHDAY Word{53, 61}
#define ELEVEN Word{65, 71}
#define THREE Word{72, 77}
#define SIX Word{88, 91}
#define NINE Word{83, 87}
#define FOUR Word{79, 83}
#define SEVEN Word{91, 96}
#define HFIVE Word{96, 100}
#define TWO Word{100, 103}
#define EIGHT Word{111, 116}
#define HTEN Word{106, 109}
#define TWELVE Word{117, 123}
#define OCLOCK Word{124, 130}
#define SKIP_WORD Word{0, 0}
// #define IT Word{0, 2}
// #define IS Word{0, 2}
// #define MTEN Word{0, 2}
// #define HALF Word{0, 2}
// #define QUARTER Word{0, 2}
// #define TWENTY Word{0, 2}
// #define MFIVE Word{0, 2}
// #define MINUTES Word{0, 2}
// #define HAPPY Word{6, 8}
// #define TO Word{0, 2}
// #define PAST Word{0, 2}
// #define ONE Word{4, 5}
// #define BIRTHDAY Word{9, 10}
// #define ELEVEN Word{0, 2}
// #define THREE Word{0, 2}
// #define SIX Word{0, 2}
// #define NINE Word{4, 5}
// #define FOUR Word{5, 6}
// #define SEVEN Word{0, 2}
// #define HFIVE Word{6, 7}
// #define TWO Word{0, 2}
// #define EIGHT Word{3, 4}
// #define HTEN Word{5, 7}
// #define TWELVE Word{0, 2}
// #define OCLOCK Word{0, 2}
// #define SKIP_WORD Word{0, 2}

class EnglishLayout : public AbstractLayout
{
public:
  void setBirthday(bool flag) override;
  void setTime(int hour, int minute) override;
  void tick() override;

  // static const int NUM_LEDS = 11;
  static const int NUM_LEDS = 130;

private:
  static Word minuteWords[12][4];
  static Word hourWords[12];
  bool _birthdaySet = false;
};

#endif
