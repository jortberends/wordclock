#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void setupServer() {
  server.on("/", serverHandleMessage);
  server.begin();
}

void loopServer() {
  server.handleClient();
}

void serverHandleMessage() {
  server.send(200,"text/html","{success:true}");

  String brightnessString = server.arg("brightness");
  int brightness = brightnessString.toInt();
  pixelsSetBrightness(brightness);

  String fireString = server.arg("fire");
  int fire = fireString.toInt();
  if (fire == 1) {
    toggleFire();  
  }
 
  String colorRs = server.arg("r");
  String colorGs = server.arg("g");
  String colorBs = server.arg("b");
  uint8_t colorR = colorRs.toInt();
  uint8_t colorG = colorGs.toInt();
  uint8_t colorB = colorBs.toInt();

  if (colorR || colorG || colorB) {
    Serial.print("Set color: RGB(");
    Serial.print(colorR);
    Serial.print(",");
    Serial.print(colorG);
    Serial.print(",");
    Serial.print(colorB);
    Serial.println(")");

    pixelsSetColor(colorR, colorG, colorB);
  }
}

