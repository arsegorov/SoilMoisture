#ifndef __RGB_H__
#define __RGB_H__

const uint8_t RED_PIN = 26,
              GREEN_PIN = 25,
              BLUE_PIN = 27;

const uint8_t RED = 4,
              GREEN = 2,
              BLUE = 1,
              BLACK = 0,
              YELLOW = RED | GREEN,
              MAGENTA = RED | BLUE,
              PURPLE = MAGENTA,
              CYAN = GREEN | BLUE,
              TEAL = CYAN,
              WHITE = RED | GREEN | BLUE;

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
void rgb(uint8_t color, uint8_t intensity);
void blink(
  uint8_t color,
  uint8_t intensity,
  unsigned long ms_on,
  int repeat = 1,
  unsigned long ms_off = INT32_MAX
);
void rgb_16k(int color);
void blink_16k(
  int color,
  unsigned long ms_on,
  int repeat = 1,
  unsigned long ms_off = INT32_MAX
);

#endif
