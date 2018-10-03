#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <ncurses.h>
using namespace std;

//Classes
class Image;
class GameManager;
class Ship;
class Alien;
class Player;

class Image
{
  string graph;
  int** index;
  int sizex;
  int sizey;
public:
  Image(int sizex,int sizey):sizex(sizex),sizey(sizey)
  {
    index=new int*[sizex*sizey];
    for(int i=0;i<sizex*sizey;i++)
    index[i]=new int[2];
  }
  bool findXY(int x,int y)
  {
    for(int i=0; i<sizex*sizey; i++)
    {
      if(index[i][0]==x && index[i][1]==y)
      return true;
    }
    return false;
  }
  void render()
  {
    int j=0;
    for(int i=0;i<sizex*sizey;i++,j++)
    {
       if(graph[j]=='\n')
       j++;
        move(index[i][1],index[i][0]);
        addch(graph[j]);
    }
  }
  friend class GameManager;
};

class GameManager
{
protected:
int screen_width;
int screen_height;
int score;
pair<int,int> alien_image_size={4,2};
pair<int,int>  ship_image_size={7,4};

vector<pair<int,int> > missiles;

vector<Alien*>           aliens;
pair<int,int> aliens_number={4,7};
pair<int,int> aliens_position={2,1};
pair<int,int> aliens_pad={2,1};
int movedir=1;

char LEFT            =      'a';
char RIGHT           =      'd';
char SHOOT           =      'k';
char MISSILE         =      '^';

public:
  GameManager():score(0){
    initscr();
    getmaxyx(stdscr,screen_height,screen_width);
    noecho();
    cbreak();
  }
  ~GameManager(){
    endwin();
  }

  Image* setImage     (const string,int x,int y,int sizex,int sizey);
  void  setGraph      (Image*,const string);
  void  updateIndex   (Image*,int x,int y);
  void  setAliens     ();
  void  renderAliens  ();
  void  renderMissiles();
  bool  destroyAlien  (pair<int,int>&);
};

void GameManager :: setGraph(Image* img,const string object)
{
  stringstream buffer;
  ifstream file;
  file.open(object);
  if(!file)
  {
  buffer<<object<<" "<<"not found";
  img->graph=buffer.str();
  }
  buffer << file.rdbuf();
  img->graph=buffer.str();
}

void GameManager :: updateIndex(Image* img,int x,int y)
{
  int k=0;
  for(int i=y;i<y+img->sizey; i++)
  {
    for(int j=x;j<x+img->sizex; j++)
    {
      img->index[k][1]=i;
      img->index[k][0]=j;
      k++;
    }
  }
}

Image* GameManager :: setImage(const string object,int x,int y,int sizex,int sizey)
{
  Image *img=new Image(sizex,sizey);
  updateIndex(img,x,y);
  setGraph   (img,object);
  return img;
}

void GameManager :: renderMissiles()
{
  for(int i=0;i<missiles.size();i++)
  {
    if(!destroyAlien(missiles[i]) && missiles[i].second>0)
    {
    mvaddch(missiles[i].second,missiles[i].first,MISSILE);
    missiles[i].second--;
    }
    else
    {
      missiles.erase(missiles.begin()+i);
    }
  }
}


class Ship:public GameManager
{
  int x,y;
  int sizex=ship_image_size.first;
  int sizey=ship_image_size.second;
  Image *ship;
public:
  Ship(){
    x=screen_width/2;
    y=screen_height-sizey;
    ship=setImage("ship.txt",x,y,sizex,sizey);
  }
  void shoot();
  void controls(char);
  void explode(){}
  void render();
};

void Ship::shoot()
{
     missiles.push_back(pair<int,int>(x+sizex/2,y));
}

void Ship::controls(char key)
{
  if(key==LEFT)
  {
  if(x>0)
  GameManager::updateIndex(ship,--x,y);
  }
  if(key==RIGHT)
  {
  if(x<screen_width-sizex)
  GameManager::updateIndex(ship,++x,y);
  }
  if(key==SHOOT)
  shoot();
}

void Ship :: render()
{
  ship->render();
}


class Alien:public GameManager
{
  int x,y;
  int sizex=alien_image_size.first;
  int sizey=alien_image_size.second;
  Image *alien;
public:
  Alien(int x,int y) : x(x),y(y){
     alien=setImage("alien.txt",x,y,sizex,sizey);
  }
  bool collision(int m,int n);
  void render();
  void move(int x,int y);
  void attack(){}
};

bool Alien :: collision(int m,int n)
{
  return alien->findXY(m,n);
}

void Alien :: move(int x,int y)
{
  this->x=x; this->y=y;
  GameManager :: updateIndex(alien,x,y);
}
void Alien :: render()
{
  alien->render();
}

void GameManager :: setAliens()
{
  int x=aliens_position.first , y=aliens_position.second;
  for(int i=0;i<aliens_number.second;i++)
  {
    for(int j=0;j<aliens_number.first;j++)
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
    if(aliens_position.first==40)
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

class Player:public Ship
{
public:
  void play();
};

void Player::play()
{
  char key;

  Ship::render();
  GameManager::setAliens();
  GameManager::renderAliens();
  refresh();

  while(1)
  {
  timeout(100);
  key=getch();
  Ship::controls(key);
  clear();
  Ship::render();
  GameManager::renderAliens();
  GameManager::renderMissiles();
  }
}

int main()
{
  Player yourbro;
  yourbro.play();
  return 0;
}
