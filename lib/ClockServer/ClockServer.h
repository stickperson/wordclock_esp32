#include <WebServer.h>
#include "Birthday.h"


class ClockServer;

class ClockServer : public WebServer {
  public:
    ClockServer(int port = 80) : WebServer(port) {}

    void begin();
    static const uint8_t MAX_BIRTHDAYS = 10;
    Birthday birthdays[MAX_BIRTHDAYS];
    uint8_t birthdayIdx = 0;

  private:

    WebServer _server;

    void _handleRoot();
    void _handleBirthday();
    void _handleDate();
};
