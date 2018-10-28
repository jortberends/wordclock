#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <Adafruit_NeoPixel.h>

bool inClockModus = true;

/*
 *  1 = Central European Standard Time
 *  2 = Central European Summer Time
*/
const int TIMEZONE = 1;

uint8_t statusPixel = 0;

void setup() {
  Serial.begin(115200);
  pixelsSetup();
  setupMacAddress();
  setupWifi();
  setupServer();
  setupTime();
  pixelsFireSetup();
  sunsetSunriseSetup();
}

void loop() {
  statusPixel=0;
  loopWifi();
  loopServer();
  if (inClockModus == true) {
    loopTimeDisplay(false);
  } else {
    loopPixelsFire();  
  }
}

void toggleFire() {
  inClockModus = !inClockModus;
  if (inClockModus) {
    loopTimeDisplay(true);
  }
}

