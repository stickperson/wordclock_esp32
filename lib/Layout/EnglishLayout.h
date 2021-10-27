#include "AbstractLayout.h"
#ifndef WORDCLOCK_LAYOUT_ENGLISH
#define WORDCLOCK_LAYOUT_ENGLISH

class EnglishLayout : public AbstractLayout<130>
{
public:
	void setup() override;
	void update(int hour, int minute) override;
	void addDisplay(AbstractDisplay& display) override;
private:
	static int time_it_is[4];
	static int time_minutes[11][22];
	static int time_hours[12][10];
};

#endif
