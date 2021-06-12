#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Texture.h"
#include "Point.h"

namespace Graphics {

    class GameObject {

    public:

        GameObject();
        GameObject(Texture*);
        GameObject(Texture*, Point);
        GameObject(Texture*, int, int);

        Point getLocation();
        Texture* getTexture();

        void setLocation(Point);
        void setLocation(int, int);

        virtual void moveUp() = 0;
        virtual void moveDown() = 0;
        virtual void moveLeft() = 0;
        virtual void moveRight() = 0;

    protected:

        Point _location;
        Texture* _texture;

    };

}

#endif
