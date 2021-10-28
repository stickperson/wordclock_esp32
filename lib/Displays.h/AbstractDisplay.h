#ifndef WORDCLOCK_ABSTRACT_DISPLAY_H
#define WORDCLOCK_ABSTRACT_DISPLAY_H

class AbstractDisplay
{
public:
  virtual void tick() = 0;
  virtual void updatePosition(int position) = 0;

protected:

};

#endif
