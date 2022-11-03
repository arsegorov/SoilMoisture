#ifndef __RGB_H__
#define __RGB_H__

const uint8_t RED_PIN = 26;
const uint8_t GREEN_PIN = 25;
const uint8_t BLUE_PIN = 27;

const uint8_t RED = 4;
const uint8_t GREEN = 2;
const uint8_t BLUE = 1;
const uint8_t BLACK = 0;
const uint8_t YELLOW = RED | GREEN;
const uint8_t MAGENTA = RED | BLUE, PURPLE = MAGENTA;
const uint8_t CYAN = GREEN | BLUE, TEAL = CYAN;
const uint8_t WHITE = RED | GREEN | BLUE;

const uint8_t BRIGHT = 255,
              DIM = 191,
              DIMMER = 127,
              VERY_DIM = 63,
              REALLY_DIM = 31;

const uint8_t ZERO = 0UL,
              TENTH = 100UL,
              QUARTER = 250UL,
              HALF = 500UL,
              ONE = 1000UL;

void rgb_setup();
// void color_on(uint8_t pin, uint8_t intensity);
// void color_off(uint8_t pin);
void rgb(uint8_t color, uint8_t intensity);
void blink(uint8_t color, uint8_t intensity, unsigned long ms_on, int repeat = 1, unsigned long ms_off = INT32_MAX);
void rgb_16k(int color);
void blink_16k(int color, unsigned long ms_on, int repeat = 1, unsigned long ms_off = INT32_MAX);

#endif
