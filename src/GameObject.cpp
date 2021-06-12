#include "../include/GameObject.h"

using namespace Graphics;

GameObject::GameObject() {

}

GameObject::GameObject(Texture* texture) {
    _texture = texture;
}

GameObject::GameObject(Texture* texture, Point location) {
    _texture = texture;
    _location = location;
}

GameObject::GameObject(Texture* texture, int x, int y) {
    _texture = texture;
    _location.setX(x);
    _location.setY(y);
}

Point GameObject::getLocation() {
    return _location;
}

void GameObject::setLocation(Point p) {
    _location = p;
}

void GameObject::setLocation(int x, int y) {
    _location.setX(x);
    _location.setY(y);
}

Texture* GameObject::getTexture() {
    return _texture;
}