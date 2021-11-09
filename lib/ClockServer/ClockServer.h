#ifndef CLOCKSERVER_H
#define CLOCKSERVER_H
#include <Update.h>
#include <WebServer.h>
#include "WordClock.h"


class ClockServer;

class ClockServer : public WebServer {
  public:
    ClockServer(int port, WordClock& clock);

    void begin();

  private:
    WordClock _clock;
    void _handleRoot();
    void _handleBirthday();
    void _handleDate();
    void _completeUpdate();
    void _startUpdate();
};

#endif
