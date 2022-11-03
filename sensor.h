#ifndef __SENSOR_H__
#define __SENSOR_H__

#define SENSOR_READING_PIN A0
const int SENSOR_POWER_PIN = 2;
const float DRY_READING = 545.0;  // 600 if connected directly to the 5V power pin
const float SCALE_FACTOR = -2.4;  // 1.6 if connected directly to the 5V power pin

void sensor_setup();
float sensor_value();

#endif
