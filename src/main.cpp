#include <Arduino.h>
#include <ESPmDNS.h>
#include <NTPClient.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "ClockServer.h"
#include "credentials.h"
#include "FastLedDisplay.h"
#include "EnglishLayout.h"
#include "WordClock.h"


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

WordClock wordclock(timeClient);
// WordClock wordclock;
ClockServer server(80);
EnglishLayout layout;
FastLedDisplay<layout.NUM_LEDS> display;



void setup() {
  delay(1000);
  Serial.begin(9600);
  WiFiManager wifiManager;
  WiFi.mode(WIFI_STA);

  // Reset settings during development
  // wifiManager.resetSettings();

  bool res = wifiManager.autoConnect(APssid, APpassword);
  if (res){
    Serial.println("Connected");
  } else {
    Serial.println("Not connected");
  }

  display.setup();
  layout.addDisplay(&display);
  wordclock.addLayout(&layout);

  // The clock can't be added when the server is instantiated because the display isn't added to the clock yet
  server.addClock(&wordclock);

  Serial.println("Configuring access point...");
  if (!MDNS.begin("wordclock")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  server.begin();
  MDNS.addService("http", "tcp", 80);
  timeClient.begin();
}

void loop(){
  // Write to internal LED during testing
  digitalWrite(2, HIGH);
  server.handleClient();
  wordclock.tick();
}
