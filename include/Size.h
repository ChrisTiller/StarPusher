#ifndef SIZE_H
#define SIZE_H

typedef struct Size {

  Size() {
    width = 0;
    height = 0;
  }

  Size(int width, int height) {
    this->width = width;
    this->height = height;
  }

  int width;
  int height;
  
} Size;

#endif