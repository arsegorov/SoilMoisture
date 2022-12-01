#include "rgb.h"
#include "time.h"
#include "wifi.h"
#include "sensor.h"
#include "server.h"
#include "pump.h"
#include "utils.h"


void setup() {
  serial_up();
  rgb_setup();

  // If WiFi setup fails (returns a non-zero value),
  //  loop indefinitely
  while (!wifi_setup()) {
    blink(RED, BRIGHT, HALF);
  }

  time_setup();

  sensor_setup();
  pump_setup();
  server_setup();
  blink(GREEN, BRIGHT, TENTH, 10);
}


time_t last_measurement_time = 0UL;
const time_t MEASUREMENT_INTERVAL = 3600UL;

float value = 0.0;
String local_time = "Ddd, 0000-00-00, 00:00:00 ZZZ";

void loop() {
  time_t t = now();
  if (
    last_measurement_time == 0UL
    || t - last_measurement_time >= MEASUREMENT_INTERVAL
  ) {
    last_measurement_time = t;
    value = sensor_value();
    local_time = local_time_string();
  } else {
    delay_secs(1);
  }
  listen_for_clients(value, local_time);

  delay_secs(14);
}
