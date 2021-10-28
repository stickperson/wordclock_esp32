#include "AbstractLayout.h"
#ifndef WORDCLOCK_LAYOUT_ENGLISH
#define WORDCLOCK_LAYOUT_ENGLISH

class EnglishLayout : public AbstractLayout
{
public:
	// void setup();
	// void update(int hour, int minute) override;
	// void addDisplay(AbstractDisplay* display) override;
	static const int NUM_LEDS = 130;

private:
	static int time_it_is[4];
	static int time_minutes[11][22];
	static int time_hours[12][10];
	// static const int NUM_LEDS = 130;
};

#endif
