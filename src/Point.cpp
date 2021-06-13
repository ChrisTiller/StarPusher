#include "../include/Point.h"

using namespace Graphics;

Point::Point() {
    _x = 0;
    _y = 0;
}

Point::Point(int x, int y) {
    _x = x;
    _y = y;
}

int Point::getX() {
    return _x;
}

int Point::getY() {
    return _y;
}

void Point::setX(int x) {
    _x = x;
}

void Point::setY(int y) {
    _y = y;
}

bool Point::operator==(const Point& p) {
    return (_x == p._x && _y == p._y);
}

bool Point::operator!=(const Point& p) {
    return !((*this) == p);
}