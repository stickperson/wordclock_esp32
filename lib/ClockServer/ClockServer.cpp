#include <Arduino.h>
#include <ArduinoJson.h>
#include <Update.h>
#include <WebServer.h>
#include "ClockServer.h"
#include "Templates.h"
#include "WordClock.h"

ClockServer::ClockServer(int port)
: WebServer(port)
{
}

void ClockServer::addClock(WordClock* clock){
  _clock = clock;
}

void ClockServer::_handleRoot() {
  send(200, "text/html", FPSTR(rootContent));
}


void ClockServer::_handleBirthday(){
  String data = arg("plain");
  StaticJsonDocument<64> doc;
  DeserializationError error = deserializeJson(doc, data);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    send(400, "text/plain", "JSON deserialization failed");
    return;
  }
  // Serial.println(doc["month"]);
  int month = doc["month"];
  int day = doc["day"];
  _clock->addBirthday(month, day);
  send(200, "text/plain", "Yay");
}


void ClockServer::_handleDate() {
  if (method() != HTTP_POST) {
    send(405, "text/plain", "Method Not Allowed");
  } else {

    String data = arg("plain");
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, data);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      send(400, "text/plain", "JSON deserialization failed");
      return;
    }
    // Update timezone
    setenv("TZ", doc["timezone"], 1);
    tzset();

    // Set the system time to the unix timestamp (seconds)
    struct timeval tv;
    tv.tv_sec = doc["unix"];
    tv.tv_usec = 0;
    settimeofday(&tv, NULL);
    _clock->tick(true);

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
