#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <DS1302RTC.h>
#include <Adafruit_NeoPixel.h>

bool inClockModus = true;

void setup() {
  Serial.begin(115200);
  setupMacAddress();
  setupWifi();
  setupServer();
  setupTime();
  pixelsSetup();
  pixelsFireSetup();
}

void loop() {
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

