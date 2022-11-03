#include "utils.h"


void serial_up() {
  Serial.begin(BAUD_RATE);
  while (!Serial) {}  // wait for serial to start up
}


void delay_secs(unsigned long secs) {
  delay(1000uL * secs);
}
