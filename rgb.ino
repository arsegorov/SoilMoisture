#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

#include "rgb.h"


/**
 * Initializes the RGB LED control pins
 *  and blinks each of the 3 colors.
*/
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


/**
 * Sets an RGB pin signal intensity.
 * 
 * @param pin one of the RGB LED's control pins: RED_PIN, GREEN_PIN, or BLUE_PIN
 * @param intensity desired intensity, 0..255
*/
void set_intensity(uint8_t pin, uint8_t intensity) {
  WiFiDrv::analogWrite(pin, intensity);
}


/**
 * Turns on the RGB LED with the 3-bit color and 8-bit intensity.
 * 
 * @param color 3-bit color, the high 5 bits are ignored
 * @param intensity 8-bit intensity
*/
void rgb(uint8_t color, uint8_t intensity) {
  set_intensity(RED_PIN, color & RED ? intensity : (uint8_t)0);
  set_intensity(GREEN_PIN, color & GREEN ? intensity : (uint8_t)0);
  set_intensity(BLUE_PIN, color & BLUE ? intensity : (uint8_t)0);
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


/**
 * Turns on the RGB LED with the given 16-bit color.
 * 
 * @param color 16-bit color;
 *  the highest 4 bits are overall intensity adjustment,
 *  the next 4 are red color intensity, the next 4 - green, the lowest 4 - blue.
*/
void rgb_16k(int color) {
  uint8_t red_intensity = (color>>8) & 0b1111,
          green_intensity = (color>>4) & 0b1111,
          blue_intensity = color & 0b1111,
          alpha = (color>>8) & 0b11110000;
  set_intensity(RED_PIN, alpha + red_intensity);
  set_intensity(GREEN_PIN, alpha + green_intensity);
  set_intensity(BLUE_PIN, alpha + blue_intensity);
}


/**
 * Blinks the RGB LED with the given 16-bit color, time on, time off, and number of repeats.
 * 
 * @param color 16-bit color;
 *  the highest 4 bits are overall intensity adjustment,
 *  the next 4 are red color intensity, the next 4 - green, the lowest 4 - blue.
 * @param ms_on the time in ms the LED should be on
 * @param repeat how many times to blink
 * @param ms_off the time in ms the LED should be off
*/
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
