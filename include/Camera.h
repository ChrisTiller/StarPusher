#ifndef CAMERA_H
#define CAMERA_H

#include "SDL2/SDL.h"


class Camera {

public:

	Camera();

	void handleEvents(SDL_Event&);
	void update();

	int getXPos() const;
	int getYPos() const;

	void setXYPos(const int, const int);

	void setUse(bool);

private:

	int _posX;
	int _posY;

	int _velXRIGHT;
	int _velXLEFT;
	int _maxVelX;

	int _velYUP;
	int _velYDOWN;
	int _maxVelY;

	int _acceleration;

	bool _inUse;

	bool _w;
	bool _s;
	bool _d;
	bool _a;

};


#endif
