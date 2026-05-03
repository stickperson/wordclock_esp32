#include <Preferences.h>
#include "Birthday.h"

static const char* NVS_NS  = "birthdays";
static const char* NVS_KEY = "data";

BirthdayStore Birthday::_store = {};

void Birthday::load() {
  Preferences prefs;
  prefs.begin(NVS_NS, true);
  prefs.getBytes(NVS_KEY, &_store, sizeof(_store));
  prefs.end();
}

void Birthday::_save() {
  Preferences prefs;
  prefs.begin(NVS_NS, false);
  prefs.putBytes(NVS_KEY, &_store, sizeof(_store));
  prefs.end();
}

void Birthday::clear() {
  _store = {};
  _save();
}

void Birthday::setBirthday(uint8_t month, uint8_t day, uint16_t year) {
  if (_store.count >= MAX_BIRTHDAYS) return;
  _store.entries[_store.count++] = { month, day, year };
  _save();
}

bool Birthday::isBirthday(uint8_t month, uint8_t day) {
  for (uint8_t i = 0; i < _store.count; i++) {
    if (_store.entries[i].month == month && _store.entries[i].day == day) return true;
  }
  return false;
}

const BirthdayStore& Birthday::store() {
  return _store;
}
