#include <Arduino.h>
#include <ESPmDNS.h>
// #include <FastLED.h>
#include <WiFi.h>
#include "ClockServer.h"
#include "credentials.h"
// #include "EnglishLayout.h"
#include "TestLayout.h"
#include "FastLedDisplay.h"
#include "WordClock.h"

#define ALL_LEDS leds(0, 10 - 1)
#define IT leds(11, 12)
#define IS leds(8, 9)
#define MTEN leds(4, 6)
#define HALF leds(0, 3)
#define QUARTER leds(13, 19)
#define TWENTY leds(20, 25)
#define MFIVE leds(35, 38)
#define MINUTES leds(27, 33)
#define HAPPY leds(39, 43)
#define TO leds(45, 46)
#define PAST leds(48, 51)
#define BIRTHDAY leds(53, 60)
#define ONE leds(62, 64)
#define ELEVEN leds(65, 70)
#define THREE leds(72, 76)
#define FOUR leds(79, 82)
#define NINE leds(83, 86)
#define SIX leds(88, 90)
#define SEVEN leds(91, 95)
#define HFIVE leds(96, 99)
#define TWO leds(100, 102)
#define HTEN leds(106, 108)
#define EIGHT leds(111, 115)
#define TWELVE leds(117, 122)
#define OCLOCK leds(124, 129)

ClockServer server(80);
WordClock wordclock;

// CHSV color = CHSV(0, 0, 255);
// CRGBArray<10> leds;


void setup() {
  delay(1000);
  // EnglishLayout layout;
  TestLayout layout;
  FastLedDisplay<layout.NUM_LEDS> display;
  layout.addDisplay(&display);
  wordclock.addLayout(&layout);
  Serial.begin(9600);
  // FastLED.addLeds<APA102, 26, 27, BGR>(leds, 10);
  // FastLED.setBrightness(64);
  // FastLED.setMaxPowerInVoltsAndMilliamps(5, 2200);

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
  // FastLED.show();
}

void loop(){
  Serial.println("hello");
  wordclock.tick();
}

// void displayTime(){
//   time_t current;
//   time(&current);
//   struct tm timeinfo;
//   localtime_r(&current, &timeinfo);

//   int roundedMinute = timeinfo.tm_min / 5;
//   switch (roundedMinute)
//   {
//   case 0:
//     OCLOCK = color;
//     break;
//   case 1:
//     MFIVE = color;
//     MINUTES = color;
//     PAST = color;
//     break;
//   case 2:
//     MTEN = color;
//     MINUTES = color;
//     PAST = color;
//     break;
//   case 3:
//     QUARTER = color;
//     PAST = color;
//     break;
//   case 4:
//     TWENTY = color;
//     MINUTES = color;
//     PAST = color;
//     break;
//   case 5:
//     TWENTY = color;
//     MFIVE = color;
//     MINUTES = color;
//     PAST = color;
//     break;
//   case 6:
//     HALF = color;
//     PAST = color;
//     break;
//   case 7:
//     TWENTY = color;
//     MFIVE = color;
//     MINUTES = color;
//     TO = color;
//     break;
//   case 8:
//     TWENTY = color;
//     MINUTES = color;
//     TO = color;
//     break;
//   case 9:
//     QUARTER = color;
//     TO = color;
//     break;
//   case 10:
//     MTEN = color;
//     MINUTES = color;
//     TO = color;
//     break;
//   case 11:
//     MFIVE = color;
//     MINUTES = color;
//     TO = color;
//     break;
//   default:
//     break;
//   }

//   uint8_t hour = timeinfo.tm_hour;
//   if (timeinfo.tm_min > 35){
//     hour += 1;
//   }
//   hour = hour % 12;
//   switch (hour)
//   {
//     case 0:
//       TWELVE = color;
//       // Serial.println("One ");
//       break;
//     case 1:
//       ONE = color;
//       // Serial.println("One ");
//       break;
//     case 2:
//       TWO = color;
//       // Serial.println("Two ");
//       break;
//     case 3:
//       THREE = color;
//       // Serial.println("Three ");
//       break;
//     case 4:
//       FOUR = color;
//       // Serial.println("Four ");
//       break;
//     case 5:
//       HFIVE = color;
//       // Serial.println("Hour five ");
//       break;
//     case 6:
//       SIX = color;
//       // Serial.println("Six ");
//       break;
//     case 7:
//       SEVEN = color;
//       // Serial.println("Seven ");
//       break;
//     case 8:
//       EIGHT = color;
//       // Serial.println("Eight ");
//       break;
//     case 9:
//       NINE = color;
//       // Serial.println("Nine ");
//       break;
//     case 10:
//       HTEN = color;
//       // Serial.println("Ten ");
//       break;
//     case 11:
//       ELEVEN = color;
//       // Serial.println("Eleven ");
//       break;
//     case 12:
//       TWELVE = color;
//       // Serial.println("Twelve ");
//       break;
//     default:
//       break;
//   }
// }

// void loop() {
//   // Handle all the web stuff
//   server.handleClient();

//   time_t current;
//   time(&current);
//   struct tm timeinfo;
//   Serial.println(localtime_r(&current, &timeinfo));
//   Serial.println(timeinfo.tm_hour);
//   Serial.println(timeinfo.tm_min);
//   Serial.println(timeinfo.tm_sec);
//   String message = "";
//   for (uint8_t i = 0; i < server.birthdayIdx; i++)
//   {
//     message += server.birthdays[i].month + ": " + server.arg(i) + "\n";
//     Serial.print("bday");
//     Serial.println();
//     Serial.print(server.birthdays[i].month);
//     Serial.println();
//   }
//   // static uint8_t hue = 0;
//   // ALL_LEDS.fill_rainbow(hue++);
//   // FastLED.show();
//   // delay(50);
//   wordclock.tick();
// }
