#ifndef __TIME_H__
#define __TIME_H__

#include <TimeLib.h>

const long PDT_TZ_OFFSET = -7L * 60L, PST_TZ_OFFSET = -8L * 60L;
const String DAY_OF_WEEK[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
const char NTP_POOL[] = "time.nist.gov";

void time_setup();
tmElements_t utc_time_tuple(time_t unix_timestamp);
String utc_time_string();
tmElements_t local_time_tuple(time_t unix_timestamp);
String local_time_string();

#endif
