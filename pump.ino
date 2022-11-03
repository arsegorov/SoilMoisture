#include "rgb.h"
#include "pump.h"

void pump_setup() {
  Serial.print("Settting up water pump...");
  pinMode(PUMP_POWER_PIN, OUTPUT);
  blink(YELLOW, BRIGHT, TENTH, 5);
  Serial.println("Done\n");
}


void pump_on() {
  Serial.println("Turning the pump on.\n");
  digitalWrite(PUMP_POWER_PIN, HIGH);
  blink(YELLOW, BRIGHT, QUARTER, 2);
}


void pump_off() {
  Serial.println("Turning the pump off.\n");
  digitalWrite(PUMP_POWER_PIN, LOW);
  blink(YELLOW, BRIGHT, TENTH, 5);
}
