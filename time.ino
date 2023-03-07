#include <SPI.h>
#include <WiFiNINA.h>
#include <EasyNTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <Timezone.h>

#include "rgb.h"
#include "time.h"


WiFiUDP ntpUDP;
EasyNTPClient eNTPclient(ntpUDP, NTP_POOL);

/**
 * An NTP time provider
*/
time_t get_ntp_time() {
  return eNTPclient.getUnixTime();
}


Timezone local_tz = Timezone(UTC);

/**
 * Sets up an NTP client and syncs the time from the internet.
*/
void time_setup() {
  time_t t = 0UL;
  unsigned long offset = millis(), wait;

  Serial.println("Syncing time from the internet...");
  setSyncProvider(get_ntp_time);
  t = now();

  // TODO: update this logic to a more elegant failure handling
  // If the time didn't sync, try for an hour before giving up
  while (t < 3600UL) {
    blink(CYAN, REALLY_DIM, ONE, 1, ZERO);

    setSyncProvider(get_ntp_time);
    t = now();
    wait = millis() - offset;
  }

  setTime(now() + wait / 1000UL);
  setSyncInterval(NTP_UPDATE_IMTERVAL);

  Serial.println("Internet time sync complete.");

  Serial.print("Current UTC time: ");
  Serial.println(utc_time_string());
  Serial.println();
  blink(CYAN, BRIGHT, TENTH, 5);

  local_tz = Timezone(PDT, PST);
}


/**
 * Syncs time from the internet except for the initial setup.
*/
void time_sync() {
  time_t t, curr_time;
  unsigned long offset = millis(), wait;

  Serial.println("Syncing time from the internet...");
  blink(CYAN, REALLY_DIM, ONE, 1, ZERO);

  curr_time = now();
  setSyncProvider(get_ntp_time);
  t = now();

  // Checking if the time is way off
  if (abs(t - curr_time) > 15 * 60UL) {
    Serial.println("Internet time sync failed. Trying again tomorrow.");
  } else {
    setTime(t);
    Serial.println("Internet time sync complete.");

    Serial.print("Current UTC time: ");
    Serial.println(utc_time_string());
    Serial.println();
  }

  blink(CYAN, BRIGHT, TENTH, 5);
}


/**
 * Breaks down a Unix timestamp into date-time components. Assumes UTC.
 *
 * @param unix_timestamp the seconds count from the Unix epoch in GMT
*/
tmElements_t utc_time_tuple(time_t unix_timestamp) {
  tmElements_t utc_tuple;
  breakTime(unix_timestamp, utc_tuple);

  return utc_tuple;
}


/**
 * Generates a date-time string for the current time in UTC.
*/
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


/**
 * Breaks down a Unix timestamp into date-time components. Assumes local timezone.
 *
 * @param unix_timestamp the seconds count from the Unix epoch in GMT
*/
tmElements_t local_time_tuple(time_t unix_timestamp) {
  tmElements_t local_tuple;
  breakTime(local_tz.toLocal(unix_timestamp), local_tuple);

  return local_tuple;
}


/**
 * Generates a date-time string for the current time in local timezone.
*/
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
         + " " + (local_tz.locIsDST(t) ? PDT.abbrev : PST.abbrev);
}
