#include <Adafruit_NeoPixel.h>

#define PIXELS_PIN 2 // D4 on NodeMCU
#define PIXELS_COUNT 114 //  Total number of pixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS_COUNT, PIXELS_PIN, NEO_GRB + NEO_KHZ800);

// Matrix size
const uint8_t PIXELS_COLUMNS = 11;
const uint8_t PIXELS_ROWS = 10;

// Default / saved color
uint32_t c = pixels.Color(127,127,127);

void pixelsSetup() {
  pixels.begin();
}

void pixelsSetBrightness(int brightness) {
  if (brightness > 0 && brightness <= 255) {
    Serial.print("Set brightness: ");
    Serial.println(brightness);
    pixels.setBrightness(brightness);
    pixels.show();
  }
}

void pixelsSetColor(uint32_t colorR, uint32_t colorG, uint32_t colorB) {
    c = pixels.Color(colorR,colorG,colorB);
    loopTimeDisplay(true);
}

void pixelsDisplayTime(uint8_t HOUR, uint8_t MINUTE) {
  pixels.clear();

  pixelsWordHet(c);
  pixelsWordIs(c);

  if (MINUTE >= 20) {
    HOUR = HOUR+1;
  }
  
  if (HOUR >= 12) {
    HOUR = HOUR-12;
  }
  
  if (HOUR == 0) {
    pixelsHourTwaalf(c);
  } else if (HOUR == 1) {
    pixelsHourEen(c);
  } else if (HOUR == 2) {
    pixelsHourTwee(c);
  } else if (HOUR == 3) {
    pixelsHourDrie(c);
  } else if (HOUR == 4) {
    pixelsHourVier(c);
  } else if (HOUR == 5) {
    pixelsHourVijf(c);
  } else if (HOUR == 6) {
    pixelsHourZes(c);
  } else if (HOUR == 7) {
    pixelsHourZeven(c);
  } else if (HOUR == 8) {
    pixelsHourAcht(c);
  } else if (HOUR == 9) {
    pixelsHourNegen(c);
  } else if (HOUR == 10) {
    pixelsHourTien(c);
  } else if (HOUR == 11) {
    pixelsHourElf(c);
  }
  
  if (MINUTE >= 0 && MINUTE < 5) {
    pixelsWordHour(c);
  } else if (MINUTE >= 5 && MINUTE < 10) {
    pixelsMinutesVijf(c);pixelsWordOver1(c);
  } else if (MINUTE >= 10 && MINUTE < 15) {
    pixelsMinutesTien(c);pixelsWordOver2(c);
  } else if (MINUTE >= 15 && MINUTE < 20) {
    pixelsMinutesKwart(c);pixelsWordOver2(c);
  } else if (MINUTE >= 20 && MINUTE < 25) {
    pixelsMinutesTien(c);pixelsWordVoor1(c);pixelsMinutesHalf(c);
  } else if (MINUTE >= 25 && MINUTE < 30) {
    pixelsMinutesVijf(c);pixelsWordVoor1(c);pixelsMinutesHalf(c);
  } else if (MINUTE >= 30 && MINUTE < 35) {
    pixelsMinutesHalf(c);
  } else if (MINUTE >= 35 && MINUTE < 40) {
    pixelsMinutesVijf(c);pixelsWordOver1(c);pixelsMinutesHalf(c);
  } else if (MINUTE >= 40 && MINUTE < 45) {
    pixelsMinutesTien(c);pixelsWordOver1(c);pixelsMinutesHalf(c);
  } else if (MINUTE >= 45 && MINUTE < 50) {
    pixelsMinutesKwart(c);pixelsWordVoor2(c);
  } else if (MINUTE >= 50 && MINUTE < 55) {
    pixelsMinutesTien(c);pixelsWordVoor1(c);
  } else if (MINUTE >= 55 && MINUTE < 60) {
    pixelsMinutesVijf(c);pixelsWordVoor1(c);
  }

  if (MINUTE % 5 == 1) {
    pixelsMinute1(c);
  } else if (MINUTE % 5 == 2) {
    pixelsMinute1(c);pixelsMinute2(c);
  } else if (MINUTE % 5 == 3) {
    pixelsMinute1(c);pixelsMinute2(c);pixelsMinute3(c);
  } else if (MINUTE % 5 == 4) {
    pixelsMinute1(c);pixelsMinute2(c);pixelsMinute3(c);pixelsMinute4(c);
  }
  
  pixels.show();
}

void pixelsWordHet(uint32_t c)
{
  pixels.setPixelColor(0,c);
  pixels.setPixelColor(1,c);
  pixels.setPixelColor(2,c);
}

void pixelsWordIs(uint32_t c)
{
  pixels.setPixelColor(4,c);
  pixels.setPixelColor(5,c);
}

void pixelsMinutesVijf(uint32_t c)
{
  pixels.setPixelColor(7,c);
  pixels.setPixelColor(8,c);
  pixels.setPixelColor(9,c);
  pixels.setPixelColor(10,c);
}

void pixelsMinutesTien(uint32_t c)
{
  pixels.setPixelColor(18,c);
  pixels.setPixelColor(19,c);
  pixels.setPixelColor(20,c);
  pixels.setPixelColor(21,c);
}

void pixelsWordVoor1(uint32_t c)
{
  pixels.setPixelColor(11,c);
  pixels.setPixelColor(12,c);
  pixels.setPixelColor(13,c);
  pixels.setPixelColor(14,c);
}

void pixelsWordOver1(uint32_t c)
{
  pixels.setPixelColor(22,c);
  pixels.setPixelColor(23,c);
  pixels.setPixelColor(24,c);
  pixels.setPixelColor(25,c);
}

void pixelsMinutesKwart(uint32_t c)
{
  pixels.setPixelColor(28,c);
  pixels.setPixelColor(29,c);
  pixels.setPixelColor(30,c);
  pixels.setPixelColor(31,c);
  pixels.setPixelColor(32,c);
}

void pixelsMinutesHalf(uint32_t c)
{
  pixels.setPixelColor(40,c);
  pixels.setPixelColor(41,c);
  pixels.setPixelColor(42,c);
  pixels.setPixelColor(43,c);
}

void pixelsWordOver2(uint32_t c)
{
  pixels.setPixelColor(33,c);
  pixels.setPixelColor(34,c);
  pixels.setPixelColor(35,c);
  pixels.setPixelColor(36,c);
}

void pixelsWordVoor2(uint32_t c)
{
  pixels.setPixelColor(44,c);
  pixels.setPixelColor(45,c);
  pixels.setPixelColor(46,c);
  pixels.setPixelColor(47,c);
}

void pixelsHourEen(uint32_t c)
{
  pixels.setPixelColor(51,c);
  pixels.setPixelColor(52,c);
  pixels.setPixelColor(53,c);
}

void pixelsHourTwee(uint32_t c)
{
  pixels.setPixelColor(62,c);
  pixels.setPixelColor(63,c);
  pixels.setPixelColor(64,c);
  pixels.setPixelColor(65,c);
}

void pixelsHourDrie(uint32_t c)
{
  pixels.setPixelColor(55,c);
  pixels.setPixelColor(56,c);
  pixels.setPixelColor(57,c);
  pixels.setPixelColor(58,c);
}

void pixelsHourVier(uint32_t c)
{
  pixels.setPixelColor(66,c);
  pixels.setPixelColor(67,c);
  pixels.setPixelColor(68,c);
  pixels.setPixelColor(69,c);
}

void pixelsHourVijf(uint32_t c)
{
  pixels.setPixelColor(70,c);
  pixels.setPixelColor(71,c);
  pixels.setPixelColor(72,c);
  pixels.setPixelColor(73,c);
}

void pixelsHourZes(uint32_t c)
{
  pixels.setPixelColor(74,c);
  pixels.setPixelColor(75,c);
  pixels.setPixelColor(76,c);
}

void pixelsHourZeven(uint32_t c)
{
  pixels.setPixelColor(83,c);
  pixels.setPixelColor(84,c);
  pixels.setPixelColor(85,c);
  pixels.setPixelColor(86,c);
  pixels.setPixelColor(87,c);
}

void pixelsHourNegen(uint32_t c)
{
  pixels.setPixelColor(77,c);
  pixels.setPixelColor(78,c);
  pixels.setPixelColor(79,c);
  pixels.setPixelColor(80,c);
  pixels.setPixelColor(81,c);
}

void pixelsHourAcht(uint32_t c)
{
  pixels.setPixelColor(88,c);
  pixels.setPixelColor(89,c);
  pixels.setPixelColor(90,c);
  pixels.setPixelColor(91,c);
}

void pixelsHourTien(uint32_t c)
{
  pixels.setPixelColor(92,c);
  pixels.setPixelColor(93,c);
  pixels.setPixelColor(94,c);
  pixels.setPixelColor(95,c);
}

void pixelsHourElf(uint32_t c)
{
  pixels.setPixelColor(96,c);
  pixels.setPixelColor(97,c);
  pixels.setPixelColor(98,c);
}

void pixelsHourTwaalf(uint32_t c)
{
  pixels.setPixelColor(104,c);
  pixels.setPixelColor(105,c);
  pixels.setPixelColor(106,c);
  pixels.setPixelColor(107,c);
  pixels.setPixelColor(108,c);
  pixels.setPixelColor(109,c);
}

void pixelsWordHour(uint32_t c)
{
  pixels.setPixelColor(99,c);
  pixels.setPixelColor(100,c);
  pixels.setPixelColor(101,c);
}

void pixelsMinute1(uint32_t c)
{
  pixels.setPixelColor(113,c);
}

void pixelsMinute2(uint32_t c)
{
  pixels.setPixelColor(112,c);
}

void pixelsMinute3(uint32_t c)
{
  pixels.setPixelColor(111,c);
}

void pixelsMinute4(uint32_t c)
{
  pixels.setPixelColor(110,c);
}
