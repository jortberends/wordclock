#include "ArduinoJson.h"

WiFiClientSecure httpsClient;

uint8_t sunrise_hour = 0;
uint8_t sunrise_minute = 0;
uint8_t sunset_hour = 0;
uint8_t sunset_minute = 0;

uint8_t night_brightness = 20;
uint8_t overday_brightness = 170;

const char* sunset_host = "api.sunrise-sunset.org";

void sunsetSunriseLoop(uint8_t current_hour, uint8_t current_minute) {

  Serial.println("sunsetSunriseLoop");
  Serial.print(current_hour);
  Serial.println(current_minute);

  // At UTC time 1:00 get new sunset/sunrise data
  if (current_hour == (TIMEZONE+1) && current_minute == 0) {
    retrieveNewData();
  }

  if (current_hour == sunrise_hour && current_minute == sunrise_minute) {
    Serial.println("Good morning!");
    pixelsSetBrightness(overday_brightness);
  } else if (current_hour == sunset_hour && current_minute == sunset_minute) {
    // Good night
    Serial.println("Good night!");
    pixelsSetBrightness(night_brightness);
  }
  
}

void sunsetSunriseSetup() {
  retrieveNewData();
}

void retrieveNewData() {
  httpsClient.setInsecure();
  
  if (!httpsClient.connect(sunset_host, 443)) {
    Serial.println("Connection failed");
    return;
  }
  Serial.println("Connected");

  String url = "/json?lat=52.3082089&lng=4.8637064&date=today&formatted=0";
  httpsClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + sunset_host + "\r\n" + 
               "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
  while (httpsClient.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      httpsClient.stop();
      return;
    }
  }

  // Check HTTP status
  char status[32] = {0};
  httpsClient.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    Serial.print("Unexpected response: ");
    Serial.println(status);
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!httpsClient.find(endOfHeaders)) {
    Serial.println("Invalid response");
    return;
  }
    // Allocate JsonBuffer
  // Use arduinojson.org/assistant to compute the capacity.
  const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(10) + 490;
  DynamicJsonBuffer jsonBuffer(capacity);

  String weirdStuff = httpsClient.readStringUntil('\r');
  //Serial.println(weirdStuff);

  // Parse JSON object
  JsonObject& root = jsonBuffer.parseObject(httpsClient);
  if (!root.success()) {
    Serial.println("Parsing failed!");
    return;
  }

  JsonObject& results = root["results"];
  const char* results_sunrise = results["sunrise"]; // "2018-04-07T04:59:45+00:00"
  const char* results_sunset = results["sunset"]; // "2018-04-07T18:25:21+00:00"

  sunrise_hour = ((results_sunrise[11]-'0')*10)+(results_sunrise[12]-'0')+TIMEZONE;
  sunrise_minute = ((results_sunrise[14]-'0')*10)+(results_sunrise[15]-'0');

  sunset_hour = ((results_sunset[11]-'0')*10)+(results_sunset[12]-'0')+TIMEZONE;
  sunset_minute = ((results_sunset[14]-'0')*10)+(results_sunset[15]-'0');

  Serial.print("Sunrise: ");
  Serial.print(sunrise_hour);
  Serial.print(":");
  Serial.println(sunrise_minute);
  
  Serial.print("Sunset: ");
  Serial.print(sunset_hour);
  Serial.print(":");
  Serial.println(sunset_minute);

  // Disconnect
  httpsClient.stop();
}
