#ifndef POINT_H
#define POINT_H

typedef struct Point {

    Point() {
        x = 0;
        y = 0;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Point& operator=(const Point& src) {
        x = src.x;
        y = src.y;
        return *this;
    }

    bool operator==(const Point& other) {
        return (x == other.x && y == other.y);
    }

    int x;
    int y;

} Point;

#endif
