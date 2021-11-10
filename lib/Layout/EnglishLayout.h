#ifndef WORDCLOCK_TEST_LAYOUT_H
#define WORDCLOCK_TEST_LAYOUT_H
#include "AbstractLayout.h"

// #define IT Word{2, 3}
// #define IS Word{3, 4}
// #define MTEN Word{6, 8}
// #define HALF Word{9, 12}
// #define QUARTER Word{13, 19}
// #define TWENTY Word{20, 25}
// #define MFIVE Word{26, 29}
// #define MINUTES Word{31, 37}
// #define HAPPY Word{39, 43}
// #define TO Word{45, 46}
// #define PAST Word{48, 51}
// #define ONE Word{52, 54}
// #define BIRTHDAY Word{56, 63}
// #define ELEVEN Word{65, 70}
// #define THREE Word{72, 76}
// #define SIX Word{78, 80}
// #define NINE Word{82, 85}
// #define FOUR Word{86, 89}
// #define SEVEN Word{91, 95}
// #define HFIVE Word{96, 99}
// #define TWO Word{100, 102}
// #define EIGHT Word{105, 109}
// #define HTEN Word{112, 114}
// #define TWELVE Word{117, 122}
// #define OCLOCK Word{124, 129}
// #define ALL Word{0, 130}
// #define SKIP_WORD Word{0, 0}
#define IT Word{0, 2}
#define IS Word{0, 2}
#define MTEN Word{0, 2}
#define HALF Word{0, 2}
#define QUARTER Word{0, 2}
#define TWENTY Word{0, 2}
#define MFIVE Word{0, 2}
#define MINUTES Word{0, 2}
#define HAPPY Word{6, 8}
#define TO Word{0, 2}
#define PAST Word{0, 2}
#define ONE Word{4, 5}
#define BIRTHDAY Word{9, 10}
#define ELEVEN Word{0, 2}
#define THREE Word{0, 2}
#define SIX Word{0, 2}
#define NINE Word{4, 5}
#define FOUR Word{5, 6}
#define SEVEN Word{0, 2}
#define HFIVE Word{6, 7}
#define TWO Word{0, 2}
#define EIGHT Word{3, 4}
#define HTEN Word{3, 4}
#define TWELVE Word{0, 2}
#define OCLOCK Word{0, 2}
#define ALL Word{0, 2}
#define SKIP_WORD Word{0, 2}

class EnglishLayout : public AbstractLayout
{
public:
  void setBirthday() override;
  void setTime(int hour, int minute) override;
  void tick() override;

  static const int NUM_LEDS = 11;

private:
  static Word minuteWords[12][4];
  static Word hourWords[12];
};

#endif
