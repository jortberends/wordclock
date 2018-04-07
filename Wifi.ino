#include <ESP8266WiFi.h>

char ssid[] = "";
char pass[] = "";

void setupWifi() {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loopWifi() {
  if(WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    setupWifi();
  }
}

