
#include <Wire.h>
#include "RTClib.h"
#include "DST_RTC.h"

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
// Required for Serial on Zero based boards
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

RTC_DS1307 rtc; // clock object

DST_RTC dst_rtc; // DST object

// Define US or EU rules for DST comment out as required. More countries could be added with different rules in DST_RTC.cpp
const char rulesDST[] = "US"; // US DST rules
// const char rulesDST[] = "EU";   // EU DST rules

void setup() {
  Serial.begin(115200);

  Wire.begin();
  rtc.begin();


  /*
    This line sets the RTC with an explicit date & time (standard time - not DST), for example to set
    March 28, 2020 at 23:58:5 you would call:
    // rtc.adjust(DateTime(2020, 3, 28, 23, 58, 5));
    If used load the sketch a second time with this line commented out or the RTC will reset to
    this time on power up or reset.
  */

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
    // DST? If we're in it, let's subtract an hour from the RTC time to keep our DST calculation correct. This gives us
    // Standard Time which our DST check will add an hour back to if we're in DST.
    DateTime standardTime = rtc.now();
    if (dst_rtc.checkDST(standardTime) == true) { // check whether we're in DST right now. If we are, subtract an hour.
      standardTime = standardTime.unixtime() - 3600;
    }
    rtc.adjust(standardTime);
  }

}

void loop() {

  DateTime standardTime = rtc.now();

  Serial.println("Standard Time");
  printTheTime(standardTime);

  DateTime theTime = dst_rtc.calculateTime(standardTime); // takes into account DST

  Serial.println("time adjusted for Daylight Saving Time");
  printTheTime(theTime);

  delay(1000); // 1 second
}


// print time to serial
void printTheTime(DateTime theTimeP) {
  Serial.print(theTimeP.year(), DEC);
  Serial.print('/');
  Serial.print(theTimeP.month(), DEC);
  Serial.print('/');
  Serial.print(theTimeP.day(), DEC);
  Serial.print(' ');
  Serial.print(theTimeP.hour(), DEC);
  Serial.print(':');
  Serial.print(theTimeP.minute(), DEC);
  Serial.print(':');
  Serial.print(theTimeP.second(), DEC);
  Serial.println();
}
