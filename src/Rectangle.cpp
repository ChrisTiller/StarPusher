#include "../include/Rectangle.h"

Rectangle::Rectangle() {

}

Rectangle::Rectangle(int x, int y, int w, int h) : Shape(x, y) {
    size_.width = w;
    size_.height = h;
}

void Rectangle::draw(SDL_Renderer* renderer) {

    SDL_Rect r;

    r.x = location_.x;
    r.y = location_.y;
    r.w = size_.width;
    r.h  = size_.height;

    SDL_SetRenderDrawColor(renderer, background_color_.r, background_color_.g, background_color_.b, background_color_.a);

    SDL_RenderFillRect(renderer, &r);

    SDL_SetRenderDrawColor(renderer, border_color_.r, border_color_.g, border_color_.b, border_color_.a);

    SDL_RenderDrawRect(renderer, &r);
}

void Rectangle::setSize(int w, int h) {
    size_.width = w;
    size_.height = h;
}