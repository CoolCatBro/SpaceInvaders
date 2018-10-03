#include "Ship.hpp"

Ship :: Ship() 
{
	x = screen_width / 2;
	y = screen_height - sizey;
	ship = setImage("ship.txt", x, y, sizex, sizey);
}

void Ship::shoot()
{
	missiles.push_back(pair<int, int>(x + sizex / 2, y));
}

void Ship::controls(char key)
{
	if (key == LEFT)
	{
		if (x > 0)
			GameManager::updateIndex(ship, x-=2, y);
	}
	if (key == RIGHT)
	{
		if (x < screen_width - sizex)
			GameManager::updateIndex(ship, x+=2, y);
	}
	if (key == SHOOT)
		shoot();
}

void Ship::render()
{
	ship->render();
}
