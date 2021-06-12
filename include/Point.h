#ifndef POINT_H
#define POINT_H

namespace Graphics {

    class Point {

    public:

        Point();
        Point(int, int);

        int getX();
        int getY();
        
        void setX(int);
        void setY(int);

    private:

        int _x;
        int _y;

    };

}

#endif
