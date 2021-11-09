#include <Arduino.h>
#include <WebServer.h>
#include "ClockServer.h"
#include "Templates.h"

ClockServer::ClockServer(int port, WordClock& wordclock)
: WebServer(port)
, _clock(wordclock)
{
}


void ClockServer::_handleRoot() {
  send(200, "text/html", FPSTR(rootContent));
}


void ClockServer::_handleBirthday(){
  int month, day;
  month = arg("month").toInt();
  day = arg("day").toInt();
  _clock.addBirthday(month, day);
  send(200, "text/plain", "Yay");
}


void ClockServer::_handleDate() {
  if (method() != HTTP_POST) {
    send(405, "text/plain", "Method Not Allowed");
  } else {
    String message = "POST form was:\n";
    for (uint8_t i = 0; i < args(); i++) {
      message += " " + argName(i) + ": " + arg(i) + "\n";
    }

    // Update timezone
    setenv("TZ", arg("timezone").c_str(), 1);
    tzset();

    // Set the system time to the unix timestamp (seconds)
    struct timeval tv;
    tv.tv_sec = arg("unix").toInt();
    tv.tv_usec = 0;
    settimeofday(&tv, NULL);

    // Return
    send(200, "text/plain", "Yay");
  }
}

void ClockServer::_completeUpdate() {
  Serial.println("Update completing");
  sendHeader("Connection", "close");
  send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
  // Add a delay so that the request can be completed before the ESP restarts
  delay(1000);
  ESP.restart();
}

void ClockServer::_startUpdate() {
  Serial.println("Update starting");
  HTTPUpload &upload = this->upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.printf("Update: %s\n", upload.filename.c_str());
    if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    /* flashing firmware to ESP*/
    if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
      Update.printError(Serial);
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    if (Update.end(true)) { //true to set the size to the current progress
      Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
    } else {
      Update.printError(Serial);
    }
  }
}

void ClockServer::begin(){
  Serial.println("Beginning server");
  on("/", [this]{ _handleRoot(); });
  on("/setBirthday", [this]{ _handleBirthday(); });
  on("/setDate", [this]{ _handleDate(); });
  on("/test", [this]{ _completeUpdate(); });
  on(
    "/update",
    HTTP_ANY,
    [this]{ _completeUpdate(); },
    [this]{ _startUpdate(); }
  );
  WebServer::begin();
}
