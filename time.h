#ifndef __TIME_H__
#define __TIME_H__

#include <TimeLib.h>
#include <Timezone.h>

const long PDT_TZ_OFFSET = -7L * 60L, PST_TZ_OFFSET = -8L * 60L;
const TimeChangeRule PDT = {"PDT", Second, Sun, Mar, 2, PDT_TZ_OFFSET},
                     PST = {"PST", First, Sun, Nov, 2, PST_TZ_OFFSET},
                     UTC = {"UTC", First, Sun, Jan, 0, 0L};

const String DAY_OF_WEEK[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

const char NTP_POOL[] = "time.nist.gov";
const unsigned long NTP_UPDATE_IMTERVAL = 86400UL;

void time_setup();
String utc_time_string();
String local_time_string();

#endif
