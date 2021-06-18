#include "../include/GameObject.h"

using namespace Graphics;

GameObject::GameObject() {
    texture_ = nullptr;
}

GameObject::GameObject(Texture* texture) {
    texture_ = texture;
}

GameObject::GameObject(Texture* texture, const Point& location) {
    texture_ = texture;
    location_ = location;
}

GameObject::GameObject(Texture* texture, int x, int y) {
    texture_ = texture;
    location_.x = x;
    location_.y = y;
}

Texture* GameObject::getTexture() {
    return texture_;
}

SDL_Rect GameObject::getTextureRect() {
    SDL_Rect rect;

    rect.x = location_.x;
    rect.y = location_.y;
    rect.w = texture_->getWidth();
    rect.h = texture_->getHeight();

    return rect;
}

bool GameObject::intersects(const SDL_Rect& rect) {
    return ( location_.x + texture_->getWidth()  >= rect.x && \
             location_.y + texture_->getHeight() >= rect.y && \
             location_.x <= (rect.x + rect.w) && \
             location_.y <= (rect.y + rect.h));
}

void GameObject::setLocation(const Point& new_point) {
    location_ = new_point;
}

Point GameObject::getLocation() {
    return location_;
}