
#include <Arduino.h>
#include "RTClib.h"

class DST_RTC
{
  private:
    byte _rulesDST; // define which ruleset to use for DST
  public:
    DST_RTC(byte rulesDST = 0); // defaults to 0, US DST rules.

    boolean checkDST(DateTime RTCTime);
    DateTime calculateTime(DateTime RTCTime);
};