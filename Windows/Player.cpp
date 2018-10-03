#include "Player.hpp"
#include <conio.h>

void Player::play()
{
  char key='\0';

  Ship::render();
  GameManager::setAliens();
  GameManager::renderAliens();
  GameEngine.refresh();

  while(1)
  {
	  Sleep(timeout);
	  if (_kbhit())
	  {
		  key = _getch();
	  }
	  if(key =='q')
		  break;
   Ship::controls(key);
   GameEngine.clear();
   Ship::render();
   GameManager::renderAliens();
   GameManager::renderMissiles();
   GameEngine.refresh();
  }
  system("pause");
}