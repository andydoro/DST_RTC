# DST_RTC
library for automatically adjusting RTC time for daylight saving time (DST)

requires [RTClib](https://github.com/adafruit/RTClib/)

Function to figure out if we're in Daylight Saving Time, then adding an hour if we are in DST.
adapted from nseidle    https://github.com/nseidle/Daylight_Savings_Time_Example/blob/master/Daylight_Savings_Time_Example.ino
and further adapted from Andy Doro    https://github.com/andydoro/DST_RTC

This algorithm is programmed to observe Daylight Saving Time in the United States, where as of the time 
of writing DST is observed between the second Sunday in March and the first Sunday in November. 

The rules for DST vary by country and territory.
https://en.wikipedia.org/wiki/Daylight_saving_time_by_country

This method checks whether its 2am or not when the time change officially occurs (this addition by Peter Bradley).   
Addition Peter Bradley
Added 2:00 AM time change for the USA.
In the European Union, Summer Time begins and ends at 1:00 a.m. Universal Time (Greenwich Mean Time). 
For most of Europe DST usually begins on the last Sunday of March at 2:00 AM local time and ends on 
the last Sunday of October at 2:00 AM local time.
The last Sunday of the month of March and October must always be on or after the 25th.
