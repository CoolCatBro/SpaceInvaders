#ifndef _SHIP_
#define _SHIP_

#include "GameManager.hpp"

class Ship : public GameManager
{
	int x, y;
	int sizex = ship_image_size.first;
	int sizey = ship_image_size.second;
	Image *ship;

public:
	Ship();
	void shoot();
	void controls(char);
	void explode() {}
	void render();
};

#endif

