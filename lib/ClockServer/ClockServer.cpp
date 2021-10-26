#include <Arduino.h>
#include <WebServer.h>
#include "ClockServer.h"
#include "Templates.h"


void ClockServer::_handleRoot() {
  ClockServer::send(200, "text/html", FPSTR(uploadContent));
}


void ClockServer::_handleBirthday(){
  birthdays[birthdayIdx] = (Birthday) {ClockServer::arg("month").toInt(), ClockServer::arg("day").toInt()};
  birthdayIdx++;
  send(200, "text/plain", "Yay");
}


void ClockServer::_handleDate() {
  if (ClockServer::method() != HTTP_POST) {
    ClockServer::send(405, "text/plain", "Method Not Allowed");
  } else {
    String message = "POST form was:\n";
    for (uint8_t i = 0; i < ClockServer::args(); i++) {
      message += " " + ClockServer::argName(i) + ": " + ClockServer::arg(i) + "\n";
    }
    Serial.println();
    Serial.print("Getting some stuff");

    // Update timezone
    setenv("TZ", ClockServer::arg("timezone").c_str(), 1);
    tzset();

    // Set the system time to the unix timestamp (seconds)
    struct timeval tv;
    tv.tv_sec = ClockServer::arg("unix").toInt();
    tv.tv_usec = 0;
    settimeofday(&tv, NULL);

    // Return
    send(200, "text/plain", "Yay");
  }
}


void ClockServer::begin(){
  Serial.println("Beginning server");
  on("/", [this]{ _handleRoot(); });
  on("/setBirthday", [this]{ _handleBirthday(); });
  on("/setDate", [this]{ _handleDate(); });
  WebServer::begin();
}
