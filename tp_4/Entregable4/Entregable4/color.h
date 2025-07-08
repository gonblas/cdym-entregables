#ifndef COLORS_H_
#define COLORS_H_
#include <stdint.h>

typedef struct
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} RGB_t;

RGB_t colors_vec[];

#endif