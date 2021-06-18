#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef struct Color {

  Color() {
    r = 0;
    g = 0;
    b = 0;
    a = 255;
  }

  Color(int r, int g, int b, int a = 255) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

} Color;

namespace known_colors {

const Color kBlack = Color(0, 0, 0);
const Color kBlue = Color(0, 0, 255);
const Color kGreen = Color(0, 255, 0);
const Color kRed = Color(255, 0, 0);  
const Color kWhite = Color(255, 255, 255);

}

#endif
