#include <sstream>
#include <fstream>

#include "GameManager.hpp"
#include "Alien.hpp"

using std::stringstream;
using std::ifstream;

GameManager::GameManager()
{
	score = 0;
	screen_width = GameEngine.screen_width;
	screen_height = GameEngine.screen_height;
}


Image* GameManager :: setImage(const string object, int x, int y, int sizex, int sizey)
{
	Image *img = new Image(sizex, sizey);
	updateIndex(img, x, y);
	setGraph(img, object);
	return img;
}


void GameManager :: setGraph(Image* img, const string object)
{
	stringstream buffer;
	ifstream file;
	file.open(object);
	if (!file)
	{
		buffer << object << " " << "not found";
		img->graph = buffer.str();
	}
	buffer << file.rdbuf();
	img->graph = buffer.str();
}

void GameManager::updateIndex(Image* img, int x, int y)
{
	int k = 0;
	for (int i = y; i < y + img->sizey; i++)
	{
		for (int j = x; j < x + img->sizex; j++)
		{
			img->index[k][1] = i;
			img->index[k][0] = j;
			k++;
		}
	}
}

void GameManager::renderMissiles()
{
	for (int i = 0; i < missiles.size(); i++)
	{
		if (!destroyAlien(missiles[i]) && missiles[i].second > 0)
		{
			GameEngine.mvprintCh(missiles[i].first, missiles[i].second,MISSILE);
			missiles[i].second--;
		}
		else
		{
			missiles.erase(missiles.begin() + i);
		}
	}
}

void GameManager :: setAliens()
{
  int x=aliens_position.first , y=aliens_position.second;
  for(int i=0;i<aliens_number.first;i++)
  {
    for(int j=0;j<aliens_number.second;j++)
    {
      aliens.push_back(new Alien(x,y));
      y+=alien_image_size.second+aliens_pad.second;
    }
    x+=alien_image_size.first+aliens_pad.first;
    y=aliens_position.second;
  }
}

bool GameManager :: destroyAlien(pair<int,int>& p)
{
  for(int i=0;i<aliens.size();i++)
  {
    if(aliens[i]!=nullptr && aliens[i]->collision(p.first,p.second))
    {
    delete aliens[i];
    aliens[i]=nullptr;
    return true;
    }
  }
  return false;
}

void GameManager :: renderAliens()
{
  if(movedir==1)
  {
    ++aliens_position.first;
    if(aliens_position.first==screen_width - aliens_number.second*( alien_image_size.first + aliens_pad.first) )
    movedir=-1;
  }
  else
  {
    --aliens_position.first;
    if(aliens_position.first==0)
    movedir=1;
  }
  int k=0;
  int x=aliens_position.first , y=aliens_position.second;
  for(int i=0;i<aliens_number.second;i++)
  {
    for(int j=0;j<aliens_number.first;j++)
    {
      if(aliens[k]!=nullptr)
      aliens[k]->move(x,y);
      k++;
      y+=alien_image_size.second+aliens_pad.second;
    }
    x+=alien_image_size.first+aliens_pad.first;
    y=aliens_position.second;
  }

  for(auto i=0;i<aliens.size();i++)
  {
  if(aliens[i]!=nullptr)
  aliens[i]->render();
  }
}

