#include "../include/Camera.h"

Camera::Camera() {
  _posX = 0;
  _posY = 0;

  _velXLEFT = 0;
  _velXRIGHT = 0;
  _velYUP = 0;
  _velYDOWN = 0;
  _maxVelX = 20;
  _maxVelY = 20;
  _acceleration = 1;

  _inUse = false;

  _w = false;
  _s = false;
  _a = false;
  _d = false;
}

void Camera::handleEvents(SDL_Event& e) {

  if (!_inUse) {
    return;
  }

  switch( e.type ) {
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym) {
        case SDLK_w:
          _w = true;
          break;
        case SDLK_s:
          _s = true;
          break;
        case SDLK_a:
          _a = true;
          break;
        case SDLK_d:
          _d = true;
          break;
      }
      break;
    case SDL_KEYUP:
      switch (e.key.keysym.sym) {
        case SDLK_w:
          _w = false;
          break;
        case SDLK_s:
          _s = false;
          break;
        case SDLK_a:
          _a = false;
          break;
        case SDLK_d:
          _d = false;
          break;
      }
  }

}

void Camera::update() {

  if (!_inUse) {
    return;
  }

  if (_w) {
    if (_velYUP  - _acceleration < -1 * _maxVelY) {
      _velYUP = -1 * _maxVelY;
    } else {
      _velYUP -= _acceleration;
    }
  } else {
    if (_velYUP + _acceleration > 0) {
      _velYUP = 0;
    } else {
      _velYUP += _acceleration;
    }
  }

  if (_s) {
    if (_velYDOWN + _acceleration > _maxVelY) {
      _velYDOWN = _maxVelY;
    } else {
      _velYDOWN += _acceleration;
    }
  } else {
    if (_velYDOWN - _acceleration < 0) {
      _velYDOWN = 0;
    } else {
      _velYDOWN -= _acceleration;
    }
  }

  if (_a) {
    if (_velXLEFT  - _acceleration < -1 * _maxVelX) {
      _velXLEFT = -1 * _maxVelX;
    } else {
      _velXLEFT -= _acceleration;
    }
  } else {
    if (_velXLEFT + _acceleration > 0) {
      _velXLEFT = 0;
    } else {
      _velXLEFT += _acceleration;
    }
  }

  if (_d) {
    if (_velXRIGHT + _acceleration > _maxVelX) {
      _velXRIGHT = _maxVelX;
    } else {
      _velXRIGHT += _acceleration;
    }
  } else {
    if (_velXRIGHT - _acceleration < 0) {
      _velXRIGHT = 0;
    } else {
      _velXRIGHT -= _acceleration;
    }
  }

  _posY += _velYUP + _velYDOWN;
  _posX += _velXLEFT + _velXRIGHT;

}

void Camera::setUse(bool use) {
  _inUse = use;
}

int Camera::getXPos() const {
  return _posX;
}

int Camera::getYPos() const {
  return _posY;
}

void Camera::setXYPos(const int x, const int y) {
  _posX = x;
  _posY = y;
}
