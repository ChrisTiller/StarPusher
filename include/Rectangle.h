#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include "Size.h"

class Rectangle : public Shape {

public:

    Rectangle();
    Rectangle(int, int, int, int);

    virtual void draw(SDL_Renderer*);

    void setSize(int, int);

    Size size_;

private:

};

#endif