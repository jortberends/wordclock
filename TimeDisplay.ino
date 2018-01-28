uint8_t TD_PREV_HOUR = 0;
uint8_t TD_PREV_MINUTE = 0;

void loopTimeDisplay(bool forced) {
  time_t TD_TIME = RTC.get();

  uint8_t TD_HOUR = hour(TD_TIME);
  uint8_t TD_MINUTE = minute(TD_TIME);

  if ((TD_HOUR != TD_PREV_HOUR || TD_MINUTE != TD_PREV_MINUTE) || forced == true) {
    TD_PREV_HOUR = TD_HOUR;
    TD_PREV_MINUTE = TD_MINUTE;

    pixelsDisplayTime(TD_HOUR, TD_MINUTE);
  }
}

