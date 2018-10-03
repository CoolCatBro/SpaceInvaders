#ifndef  _GLOBALS_
#define _GLOBALS_

#include <utility>
#include "Engine.hpp"
using std::pair;

extern Engine GameEngine;

extern int timeout;

//CONTROLS

extern char  LEFT;
extern char  RIGHT;
extern char SHOOT;

//ART

extern char  MISSILE ;

//IMAGE_SIZE

extern pair<int, int>  alien_image_size;         //{ 4,2 };
extern pair<int, int>  ship_image_size;          //{ 7,4 };

//ALIENS_INFO

extern pair<int, int>  aliens_number;              //{ 4,7 };
extern pair<int, int>  aliens_position;             //{ 2,1 };
extern pair<int, int>  aliens_pad;                   //{ 2,1 };
extern int movedir;

#endif