#include <SPI.h>
#include <WiFiNINA.h>
#include <EasyNTPClient.h>
#include <WiFiUDP.h>
#include <TimeLib.h>
#include <Timezone.h>

#include "rgb.h"
#include "time.h"


WiFiUDP ntpUDP;
EasyNTPClient eNTPclient(ntpUDP, NTP_POOL);

time_t get_ntp_time() {
  // time_t t = eNTPclient.getUnixTime();
  // Serial.print("Time since UNIX epoch: ");
  // Serial.println(t);

  // return t;
  return eNTPclient.getUnixTime();
}


void time_setup() {
  unsigned long offset = millis(), wait;
  // Serial.print("Time since boot-up: ");
  // Serial.println(offset / 1000UL);
  // Serial.println();

  Serial.println("Syncing time from the internet...");
  setSyncProvider(get_ntp_time);
  time_t t = now();

  while (t < 3600UL) {
    // Serial.println("Too low, trying again");
    blink(CYAN, REALLY_DIM, ONE, 1, 0);

    setSyncProvider(get_ntp_time);
    t = now();
    wait = millis() - offset;
  }
  // Serial.print("Wait time: ");
  // Serial.println(wait / 1000UL);
  // Serial.println();
  setTime(now() + wait / 1000UL);
  setSyncInterval(86400UL);

  Serial.println("Internet time sync complete.");
  blink(CYAN, BRIGHT, TENTH, 5);

  Serial.print("Current UTC time: ");
  Serial.println(utc_time_string());
  Serial.println();
}


tmElements_t utc_time_tuple(time_t unix_timestamp) {
  tmElements_t utc_tuple;
  breakTime(unix_timestamp, utc_tuple);

  return utc_tuple;
}


String utc_time_string() {
  tmElements_t utc_tuple = utc_time_tuple(now());

  return DAY_OF_WEEK[utc_tuple.Wday - 1]
         + ", " + String(utc_tuple.Year + 1970)
         + "-" + (utc_tuple.Month < 10 ? "0" : "") + String(utc_tuple.Month)
         + "-" + (utc_tuple.Day < 10 ? "0" : "") + String(utc_tuple.Day)
         + ", " + (utc_tuple.Hour < 10 ? "0" : "") + String(utc_tuple.Hour)
         + ":" + (utc_tuple.Minute < 10 ? "0" : "") + String(utc_tuple.Minute)
         + ":" + (utc_tuple.Second < 10 ? "0" : "") + String(utc_tuple.Second)
         + " UTC";
}


TimeChangeRule pdt = {"PDT", Second, Sun, Mar, 2, PDT_TZ_OFFSET},
               pst = {"PST", First, Sun, Nov, 2, PST_TZ_OFFSET};
Timezone pacific = Timezone(pdt, pst);

tmElements_t local_time_tuple(time_t unix_timestamp) {
  tmElements_t local_tuple;
  breakTime(pacific.toLocal(unix_timestamp), local_tuple);

  return local_tuple;
}


String local_time_string() {
  time_t t = now();
  tmElements_t local_tuple = local_time_tuple(t);

  return DAY_OF_WEEK[local_tuple.Wday - 1]
         + ", " + String(local_tuple.Year + 1970)
         + "-" + (local_tuple.Month < 10 ? "0" : "") + String(local_tuple.Month)
         + "-" + (local_tuple.Day < 10 ? "0" : "") + String(local_tuple.Day)
         + ", " + (local_tuple.Hour < 10 ? "0" : "") + String(local_tuple.Hour)
         + ":" + (local_tuple.Minute < 10 ? "0" : "") + String(local_tuple.Minute)
         + ":" + (local_tuple.Second < 10 ? "0" : "") + String(local_tuple.Second)
         + " " + (pacific.locIsDST(t) ? pdt.abbrev : pst.abbrev);
}
