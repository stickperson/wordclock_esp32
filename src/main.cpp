#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include "ClockServer.h"
#include "credentials.h"
#include "FastLedDisplay.h"
#include "EnglishLayout.h"
#include "WordClock.h"


WordClock wordclock;
ClockServer server(80);
EnglishLayout layout;
FastLedDisplay<layout.NUM_LEDS> display;

void setup() {
  delay(1000);
  Serial.begin(9600);
  display.setup();
  layout.addDisplay(&display);
  wordclock.addLayout(&layout);

  // The clock can't be added when the server is instantiated because the display isn't added to the clock yet
  server.addClock(&wordclock);

  Serial.println("Configuring access point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(APssid, APpassword);
  if (!MDNS.begin("wordclock")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  server.begin();
  Serial.println("Server started");

  // Print the IP address ---------------------------------------------------
  Serial.println(WiFi.softAPIP());

  MDNS.addService("http", "tcp", 80);
}

void loop(){
  // if (color < 50){
  //   Serial.println(color);
    // wordclock.changeColor();
  // }
  // if (brightness < 5){
  //   wordclock.changeBrightness();
  // }
  server.handleClient();
  wordclock.tick();
}
