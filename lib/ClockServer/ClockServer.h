#ifndef CLOCKSERVER_H
#define CLOCKSERVER_H
#include <ArduinoJson.h>
#include <Update.h>
#include <WebServer.h>
#include "WordClock.h"


class ClockServer;

class ClockServer : public WebServer {
  public:
    ClockServer(int port);

    // Maybe it would make sense to have the WordClock aware of the server since it (the clock) is basically a
    // mediator.
    void addClock(WordClock *clock);
    void begin();

  private:
    WordClock* _clock;
    void _handleRoot();
    void _handleBirthday();
    void _handleDate();
    void _completeUpdate();
    void _startUpdate();
};

#endif
