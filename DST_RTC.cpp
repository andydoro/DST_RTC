/*
    Function to figure out if we're in Daylight Saving Time, then adding an hour if we are in DST.
    adapted from nseidle
    https://github.com/nseidle/Daylight_Savings_Time_Example/blob/master/Daylight_Savings_Time_Example.ino
    This algorithm is programmed to observe Daylight Saving Time in the United States, where as of the time 
    of writing  DST is observed between the second Sunday in March and the first Sunday in November. 
    The rules for DST vary by country and territory.
    https://en.wikipedia.org/wiki/Daylight_saving_time_by_country

    If you're in a territory which observes DST differently this code will need to be modified. 
    If you're lucky enough to not observe DST then you would not use this library!
    This method checks whether its 2am or not when the time change officially occurs (this addition by Peter Bradley).   
    Addition Peter Bradley
    Added 2:00 AM time change for the USA.
    In the European Union, Summer Time begins and ends at 1:00 a.m. Universal Time (Greenwich Mean Time). 
    For most of Europe DST usually begins on the last Sunday of March at 2:00 AM local time and ends on 
    the last Sunday of October at 2:00 AM local time.
    The last Sunday of the month of March and October must always be on or after the 25th.
*/

#include "Arduino.h"
#include "DST_RTC.h"

DST_RTC::DST_RTC()
{

}

boolean DST_RTC::checkDST(DateTime RTCTime)
{

  // Get the day of the week. 0 = Sunday, 6 = Saturday
  int previousSunday = RTCTime.day() - RTCTime.dayOfTheWeek();

  boolean dst = false; // Assume we're not in DST

  if (strcmp(rulesDST, "US") == 0) {
    Serial.print("test of rulesDST: ");
    Serial.println(rulesDST);
    if (RTCTime.month() > 3 && RTCTime.month() < 11) dst = true; // DST is happening in America!
    // In March, we are DST if our previous Sunday was on or after the 8th for USA.
    if (RTCTime.month() == 3)
    {
      if (previousSunday >= 8 && RTCTime.hour() >= 2) dst = true; // 2:00 AM for USA
    }
    // In November we must be before the first Sunday to be dst for USA.
    // In this case we are changing time at 2:00 AM so the change to the previous Sunday
    // happens at midnight so the previous Sunday is actually this Sunday at 2:00 AM
    // That means the previous Sunday must be on or before the 7th.
    if (RTCTime.month() == 11) {// for USA
      if (previousSunday <= 7  && RTCTime.hour() <= 1) dst = true; // Changes at 2:00 AM for USA
    }
  }

  if (strcmp(rulesDST, "EU") == 0) {
    Serial.print("test of rulesDST: ");
    Serial.println(rulesDST);
    if (RTCTime.month() > 3 && RTCTime.month() < 10) dst = true; // DST is happening in Europe!
    // In March, we are DST if our previous Sunday was on or after the 25th for Europe.
    if (RTCTime.month() == 3)
    {
      if (previousSunday >= 25 && RTCTime.hour() >= 2) dst = true; // 2:00 AM for Europe
    }
    // In October we must be before the last Sunday to be dst for Europe.
    // In this case we are changing time at 2:00 AM so the change to the previous Sunday
    // happens at midnight so the previous Sunday is actually this Sunday at 2:00 AM
    // That means the previous Sunday must be on or before the 31st.
    if (RTCTime.month() == 10) // for Europe
    {
      if (previousSunday <= 31 && RTCTime.hour() <= 1) dst = true; // Changes at 2:00 AM for Europe
    }
  }
  return dst;
}

DateTime DST_RTC::calculateTime(DateTime RTCTime)
{
  if (checkDST(RTCTime) == true) {
    RTCTime = RTCTime.unixtime() + 3600; // add 1 hour or 3600 seconds to the time
  }
  return RTCTime;
}