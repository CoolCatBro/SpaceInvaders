#include "Alien.hpp"

Alien::Alien(int x,int y):  x(x),y(y)
{
     alien=setImage("alien.txt",x,y,sizex,sizey);
}


bool Alien::collision(int m, int n)
{
	return alien->findXY(m, n);
}

void Alien::move(int x, int y)
{
	this->x = x; this->y = y;
	GameManager::updateIndex(alien, x, y);
}

void Alien::render()
{
	alien->render();
}
