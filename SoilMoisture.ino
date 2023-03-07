#include "rgb.h"
#include "time.h"
#include "wifi.h"
#include "sensor.h"
#include "server.h"
#include "pump.h"
#include "utils.h"


time_t last_time_sync_time;
const time_t TIME_SYNC_INTERVAL = 86400UL;

void setup() {
  serial_up();
  rgb_setup();

  // If WiFi setup fails (returns a non-zero value),
  //  loop indefinitely
  while (!wifi_setup()) {
    blink(RED, BRIGHT, HALF);
  }

  time_setup();
  last_time_sync_time = now();

  sensor_setup();
  pump_setup();
  server_setup();
  blink(GREEN, BRIGHT, TENTH, 10);
}


time_t last_measurement_time = 0UL;
const time_t MEASUREMENT_INTERVAL = 3600UL;
const time_t LOOP_INTERVAL = 15UL;

float value = 0.0;

String local_time = "Ddd, 0000-00-00, 00:00:00 ZZZ";

void loop() {
  time_t t = now(), t1;

  if (t - last_time_sync_time >= TIME_SYNC_INTERVAL) {
    time_sync();
    last_time_sync_time = now();
  }

  if (
    last_measurement_time == 0UL
    || t - last_measurement_time >= MEASUREMENT_INTERVAL
  ) {
    value = sensor_value();
    last_measurement_time = t;
    local_time = local_time_string();
  }

  listen_for_clients(value, local_time);

  t1 = now();
  delay_secs(LOOP_INTERVAL - (t1 - t) % LOOP_INTERVAL);
}
