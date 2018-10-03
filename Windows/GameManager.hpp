#ifndef  _GAMEMANAGER_
#define _GAMEMANAGER_

#include <vector>
#include <utility>

#include "Image.hpp"
#include "Globals.hpp"

using std::pair;
using std::vector;

class Image;
class Alien;

class GameManager 
{
protected:
	int score;
	vector<pair<int, int> > missiles;
	vector<Alien*>           aliens;
	int screen_width, screen_height;

public:
	GameManager();
	 Image* setImage     (const string,int x,int y,int sizex,int sizey);
     void  setGraph        (Image*,const string);
     void  updateIndex    (Image*,int x,int y);
     void  setAliens        ();
     void  renderAliens   ();
     void  renderMissiles();
     bool  destroyAlien   (pair<int,int>&);
};

#endif
