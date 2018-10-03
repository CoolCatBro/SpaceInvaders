#include "Globals.hpp"

Engine GameEngine;

int timeout = 100;

//CONTROLS

char  LEFT = 'a';
char  RIGHT ='d';
char SHOOT ='k';

//ART

char  MISSILE ='^';

//IMAGE_SIZE

pair<int, int>  alien_image_size = { 4,2 };
pair<int, int>  ship_image_size  = { 7,4 };

//ALIENS_INFO

pair<int, int>  aliens_number = { 4,7 };
pair<int, int>  aliens_position = { 0,1 };
pair<int, int>  aliens_pad = { 2,1 };
int movedir = 1;