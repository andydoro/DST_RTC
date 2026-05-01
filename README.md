# DST_RTC
library for automatically adjusting RTC time for daylight saving time (DST)

requires [RTClib](https://github.com/adafruit/RTClib/)

Function to figure out if we're in Daylight Saving Time, then adding an hour if we are in DST.
adapted from [Nathan Seidle](https://github.com/nseidle/Daylight_Savings_Time_Example/blob/master/Daylight_Savings_Time_Example.ino)
and further adapted from [Andy Doro](https://github.com/andydoro/DST_RTC)

The library works by keeping the RTC in Standard Time and then using the functions of the DST_RTC object to (1) determine if we are in DST and then (2) returning a new DST adjusted time as needed.

The library can accept different DST rulesets and currently is programmed for either US or EU DST rulessets.

In version 1.1.1 this ruleset selection was implemented poorly and required explicit definition of either "US" or "EU" ruleset. The new implementation in 1.2.0 uses integers to choose rulesets and defaults to "0" for the US ruleset. "1" can be entered for the EU ruleset. Version 1.2.0 is therefore backwards compatible with version 1.1.0.

The US algorithm is programmed to observe Daylight Saving Time in (most of) the United States, where as of the time
of writing DST is observed between the second Sunday in March and the first Sunday in November.

For most of Europe DST usually begins on the last Sunday of March at 2:00 AM local time and ends on the last Sunday of October at 2:00 AM local time. The last Sunday of the month of March and October must always be on or after the 25th.

The rules for DST vary by country and territory.
https://en.wikipedia.org/wiki/Daylight_saving_time_by_country


Addition Peter Bradley
- Added 2:00 AM time change for the USA.
- In the European Union, Summer Time begins and ends at 1:00 a.m. Universal Time (Greenwich Mean Time). 
- For most of Europe DST usually begins on the last Sunday of March at 2:00 AM local time and ends on the last Sunday of October at 2:00 AM local time. The last Sunday of the month of March and October must always be on or after the 25th.

## Installation
### From the Library Manager
1. Launch the Arduino IDE and navigate to *Sketch → Include Library → Manage Libraries*.
2. In the library manager, scroll to *DST_RTC* or enter the name into the search field.
3. Click on the library, then click on the Install button.

### From the ZIP file
1. Download the [ZIP file](https://github.com/andydoro/DST_RTC/archive/master.zip).
2. Launch the Arduino IDE and navigate to *Sketch → Include Library → Add .ZIP Library...*. From the prompt, select the ZIP just downloaded.