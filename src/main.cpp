#include <Arduino.h>
#include <ESPmDNS.h>
#include <FastLED.h>
#include <WiFi.h>
#include "ClockServer.h"
#include "credentials.h"
#include "Templates.h"
#define ALL_LEDS leds(0, 10 - 1)


ClockServer server(80);


CHSV color = CHSV(0, 0, 255);
CRGBArray<10> leds;


void setup() {
  delay(1000);
  Serial.begin(9600);
  FastLED.addLeds<APA102, 26, 27, BGR>(leds, 10);
  FastLED.setBrightness(64);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2200);

  Serial.println("Configuring access point...");
  WiFi.mode(WIFI_AP);
  /* You can remove the password parameter if you want the AP to be open. */
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
  FastLED.show();
}

void loop() {
  // Handle all the web stuff
  server.handleClient();

  time_t current;
  time(&current);
  struct tm timeinfo;
  Serial.println(localtime_r(&current, &timeinfo));
  Serial.println(timeinfo.tm_hour);
  Serial.println(timeinfo.tm_min);
  Serial.println(timeinfo.tm_sec);
  String message = "";
  for (uint8_t i = 0; i < server.birthdayIdx; i++)
  {
    message += server.birthdays[i].month + ": " + server.arg(i) + "\n";
    Serial.print("bday");
    Serial.println();
    Serial.print(server.birthdays[i].month);
    Serial.println();
  }
  static uint8_t hue = 0;
  ALL_LEDS.fill_rainbow(hue++);
  FastLED.show();
  delay(50);
}
