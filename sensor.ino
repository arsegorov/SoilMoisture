#include "rgb.h"
#include "sensor.h"


void sensor_setup() {
  Serial.print("Setting up moisture sensor...");
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  blink(PURPLE, BRIGHT, TENTH, 5);
  Serial.println("Done\n");
}


float sensor_value() {
  float value = 0.0;

  digitalWrite(SENSOR_POWER_PIN, HIGH);
  // average of 100 readings over a second,
  // calibrated to be b/w 0 and 100
  for (int i = 0; i < 100; i++) {
    value += analogRead(SENSOR_READING_PIN);
    delay(10);
  }
  digitalWrite(SENSOR_POWER_PIN, LOW);
  blink(PURPLE, BRIGHT, QUARTER, 2);

  Serial.print("Moisture sensor cumulative raw value over 100 measurements: ");
  Serial.println(value);
  return (value / 100.0 - DRY_READING) / SCALE_FACTOR;
}
