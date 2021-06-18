#ifndef SHAPE_H
#define SHAPE_H

#include "SDL2/SDL.h"
#include "Color.h"
#include "Point.h"

class Shape {

public:

  Shape();
  Shape(int, int);

  void setLocation(Point&);
  void setLocation(int, int);
  
  virtual void draw(SDL_Renderer*) = 0;

  Color background_color_;
  Color border_color_;

  Point location_;

protected:

private:

};

#endif