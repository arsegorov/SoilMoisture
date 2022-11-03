#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

#include "rgb.h"


void rgb_setup() {
  Serial.println("Setting up RGB LED...");

  WiFiDrv::pinMode(RED_PIN, OUTPUT);
  WiFiDrv::pinMode(GREEN_PIN, OUTPUT);
  WiFiDrv::pinMode(BLUE_PIN, OUTPUT);

  Serial.println("Red...");
  blink(RED, BRIGHT, ONE, 1, ZERO);
  Serial.println("Green...");
  blink(GREEN, BRIGHT, ONE, 1, ZERO);
  Serial.println("Blue...");
  blink(BLUE, BRIGHT, ONE, 1, ZERO);

  Serial.println("RGB setup done.");
  Serial.println("");
}


void color_on(uint8_t pin, uint8_t intensity) {
  WiFiDrv::analogWrite(pin, intensity);
}


void color_off(uint8_t pin) {
  color_on(pin, (uint8_t)0);
}


/**
 * Turns the RGB LED on with the 3-bit color and 8-bit intensity.
 * 
 * @param color 3-bit color, the high 5 bits are ignored
 * @param intensity 8-bit intensity
*/
void rgb(uint8_t color, uint8_t intensity) {
  if (color & RED) {
    color_on(RED_PIN, intensity);
  } else {
    color_off(RED_PIN);
  }

  if (color & BLUE) {
    color_on(BLUE_PIN, intensity);
  } else {
    color_off(BLUE_PIN);
  }

  if (color & GREEN) {
    color_on(GREEN_PIN, intensity);
  } else {
    color_off(GREEN_PIN);
  }
}


/**
 * Blinks the RGB LED with the given 3-bit color, 8-bit intensity, time on, time off, and number of repeats.
 * 
 * @param color 3-bit color, the high 5 bits are ignored
 * @param intensity 8-bit intensity
 * @param ms_on the time in ms the LED should be on
 * @param repeat how many times to blink
 * @param ms_off the time in ms the LED should be off
*/
void blink(uint8_t color, uint8_t intensity, unsigned long ms_on, int repeat = 1, unsigned long ms_off = INT32_MAX) {
  if (ms_off == INT32_MAX) {
    ms_off = ms_on;
  }
  for (int i = 0; i < repeat; i++) {
    rgb(color, intensity);
    delay(ms_on);
    rgb(color, 0);
    delay(ms_off);
  }
}


void rgb_16k(int color) {
  uint8_t red_intensity = (color >> 8) & 0b1111,
          green_intensity = (color >> 4) & 0b1111,
          blue_intensity = color & 0b1111,
          alpha = color >> 12;
  color_on(RED_PIN, red_intensity * alpha);
  color_on(GREEN_PIN, green_intensity * alpha);
  color_on(BLUE_PIN, blue_intensity * alpha);
}


void blink_16k(int color, unsigned long ms_on, int repeat = 1, unsigned long ms_off = INT32_MAX) {
  if (ms_off == INT32_MAX) {
    ms_off = ms_on;
  }
  for (int i = 0; i < repeat; i++) {
    rgb_16k(color);
    delay(ms_on);
    rgb_16k(0);
    delay(ms_off);
  }
}
