#include "../include/Shape.h"

Shape::Shape() : background_color_(known_colors::kBlack), border_color_(known_colors::kBlack) {

}

Shape::Shape(int x, int y) : background_color_(known_colors::kBlack), border_color_(known_colors::kBlack) {
  location_.x = x;
  location_.y = y;
}

void Shape::setLocation(Point &p) {
  location_.x = p.x;
  location_.y = p.y;
}

void Shape::setLocation(int x, int y) {
  location_.x = x;
  location_.y = y;
}
