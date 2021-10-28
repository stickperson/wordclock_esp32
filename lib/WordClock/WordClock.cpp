#include "WordClock.h"
#include <Arduino.h>


void WordClock::addLayout(AbstractLayout* layout){
  _layout = layout;
}


void WordClock::tick(){
  Serial.println("*Checking LAYOUT");
  if (_layout){
    Serial.println("*HAS A LAYOUT");
    _layout->tick();
  }
}
