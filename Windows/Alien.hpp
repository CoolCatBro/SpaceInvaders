#ifndef  _ALIEN_
#define _ALIEN_

#include "GameManager.hpp"

class Alien :	public GameManager
{
	int x, y;
	int sizex = alien_image_size.first;
	int sizey = alien_image_size.second;
	Image *alien;

public:
	Alien(int x, int y);
	bool collision(int m, int n);
	void render();
	void move(int x, int y);
	void attack() {}
};

#endif