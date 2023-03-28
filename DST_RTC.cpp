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

  boolean dst = false; //Assume we're not in DST
  if (strcmp(rulesDST, "US") == 0) {
    // Serial.print("test of rulesDST: ");
    // Serial.println(rulesDST);
    if (RTCTime.month() > 3 && RTCTime.month() < 11) dst = true; //DST is happening in America!
    //In the USA in March we are DST if the previous Sunday was on or after the 8th (and on or before the 14th).
    if (RTCTime.month() == 3)
    {
      if (RTCTime.dayOfTheWeek() == 0) {  // if today is Sunday
        if (previousSunday >= 8    // on or after 8th
            && previousSunday <= 14     // but on or before 14th
            && RTCTime.hour() >= 2)  // and at or after 2:00 AM
          dst = true;
        else if (previousSunday >= 15)  // it is a Sunday after the second Sunday
          dst = true;
      }
      else if (previousSunday >= 8) // it is not Sunday and we are after the change to DST
        dst = true;
    }
    //In November we must be before the first Sunday to be dst for USA.
    //In this case we are changing time at 2:00 AM so since the change to the previous Sunday
    //happens at midnight the previous Sunday is actually this Sunday at 2:00 AM
    //That means the previous Sunday must be on or before the 7th.
    if (RTCTime.month() == 11)   // November for the USA
    {
      if (RTCTime.dayOfTheWeek() == 0)   // if today is Sunday
      {
        if (previousSunday <= 7  // and it is also the first Sunday
            && RTCTime.hour() <= 1)  // less than 2:00 AM
          dst = true;
      }
      else if (previousSunday <= 0)   // it is not yet the first Sunday and the previous Sunday was before Nov 1
        dst = true;
    }
  }

  if (strcmp(rulesDST, "EU") == 0) {
    // Serial.print("test of rulesDST: ");
    // Serial.println(rulesDST);
    if (RTCTime.month() > 3 && RTCTime.month() < 10) dst = true; //DST is happening in Europe!
    //In Europe in March, we are DST if the previous Sunday was on or after the 25th.
    if (RTCTime.month() == 3)
    {
      if (RTCTime.dayOfTheWeek() == 0)    // Today is Sunday
      {
        if (previousSunday >= 25  // and it is a Sunday on or after 25th (there can't be a Sunday in March after this)
            && RTCTime.hour() >= 1)  // 1:00 AM for Europe
          dst = true;
      }
      else if (previousSunday >= 25) // if not Sunday and the last Sunday has passed
        dst = true;
    }
    //In October we must be before the last Sunday to be in DST for Europe.
    //In this case we are changing time at 2:00 AM so since the change to the previous Sunday
    //happens at midnight the previous Sunday is actually this Sunday at 2:00 AM
    //That means the previous Sunday must be on or before the 31st but after the 25th.
    if (RTCTime.month() == 10) // October for Europe
    {
      if (RTCTime.dayOfTheWeek() == 0)   // if today is Sunday
      {
        if (previousSunday >= 25  // and it is also on or after 25th
            && RTCTime.hour() <= 0)  // less than 2:00 AM for Europe
          dst = true;
        else if (previousSunday < 25)   // it is not yet the last Sunday
          dst = true;
      }
      else if // it is not Sunday
      (previousSunday < 25)
        dst = true;
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
