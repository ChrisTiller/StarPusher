#ifndef CAMERA_H
#define CAMERA_H

#include "SDLWindow.h"


class Camera {

public:

	Camera();
	Camera(SDLWindow*);

	void handleEvents(SDL_Event&);
	void update();

	int getXPos() const;
	int getYPos() const;

	float getZoom() const;

	SDL_Rect getRect() const;

	void setXYPos(const int, const int);

	void setUse(bool);

private:

	SDLWindow* _window;

	int _posX;
	int _posY;

	float _zoom;

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
