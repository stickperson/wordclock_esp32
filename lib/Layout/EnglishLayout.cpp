#include "EnglishLayout.h"

void EnglishLayout::tick(){
    _display->tick();
}

void EnglishLayout::setBirthday(){
    _display->rainbowWord(HAPPY);
    _display->rainbowWord(BIRTHDAY);
}

void EnglishLayout::setTime(int hour, int minute){
    _display->updateWord(IT);
    _display->updateWord(IS);

    minute = minute / 5;
    for (uint8_t i = 0; i < 4; i++){
        if (EnglishLayout::minuteWords[minute][i] == SKIP_WORD){
            break;
        }
        _display->updateWord(EnglishLayout::minuteWords[minute][i]);
    }

    if (minute > 35){
        hour += 1;
    }
    hour = hour % 12;
    _display->updateWord(EnglishLayout::hourWords[hour % 12]);

    // Word first = {0, 1};
    // Word rainbow = {1, 4};
    // Word third = {5, 6};
    // Word rainbowTwo = {6, 10};
    // _display->updateWord(first);
    // _display->updateWord(third);
    // _display->rainbowWord(rainbow);
    // _display->rainbowWord(rainbowTwo);
}


Word EnglishLayout::minuteWords[12][4] = {
    {OCLOCK, SKIP_WORD, SKIP_WORD, SKIP_WORD},
    {MFIVE, MINUTES, PAST, SKIP_WORD},
    {MTEN, MINUTES, PAST, SKIP_WORD},
    {QUARTER, PAST, SKIP_WORD, SKIP_WORD},
    {TWENTY, MINUTES, PAST, SKIP_WORD},
    {TWENTY, MFIVE, MINUTES, PAST},
    {HALF, PAST, SKIP_WORD, SKIP_WORD},
    {TWENTY, MFIVE, MINUTES, TO},
    {TWENTY, MINUTES, TO, SKIP_WORD},
    {QUARTER, TO, SKIP_WORD, SKIP_WORD},
    {MTEN, MINUTES, TO, SKIP_WORD},
    {MFIVE, MINUTES, TO, SKIP_WORD},
};

Word EnglishLayout::hourWords[12] = {
    TWELVE,
    ONE,
    TWO,
    THREE,
    FOUR,
    HFIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    HTEN,
    ELEVEN,
};
