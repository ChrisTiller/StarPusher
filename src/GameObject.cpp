#include "../include/GameObject.h"

using namespace Graphics;

GameObject::GameObject() {
    _texture = NULL;
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

SDL_Rect GameObject::getRect() {
    SDL_Rect rect;

    rect.x = _location.getX();
    rect.y = _location.getY();
    rect.w = _texture->getWidth();
    rect.h = _texture->getHeight();

    return rect;
}

bool GameObject::intersects(SDL_Rect rect) {
    return ( getLocation().getX() + getTexture()->getWidth()  >= rect.x && \
             getLocation().getY() + getTexture()->getHeight() >= rect.y && \
             getLocation().getX() <= (rect.x + rect.w) && \
             getLocation().getY() <= (rect.y + rect.h));
}