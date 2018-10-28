uint8_t TD_PREV_HOUR = 0;
uint8_t TD_PREV_MINUTE = 0;

void loopTimeDisplay(bool forced) {

  Time t = rtc.time();

  uint8_t TD_HOUR = t.hr;
  uint8_t TD_MINUTE = t.min;

  if ((TD_HOUR != TD_PREV_HOUR || TD_MINUTE != TD_PREV_MINUTE) || forced == true) {
    TD_PREV_HOUR = TD_HOUR;
    TD_PREV_MINUTE = TD_MINUTE;

    pixelsDisplayTime(TD_HOUR, TD_MINUTE);
    sunsetSunriseLoop(TD_HOUR, TD_MINUTE);
  }
}

