#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
/* ^^ these are the include guards */
#include <GL/glut.h>
#include "globalVariables.h"
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


// for all drawing related functions
void ant(double x, double y,int direction,int food);
void draw_floor();
void draw_ant(ants flik);
void draw_food(food* fruit);
void spawnFood();
void redrawFood(double x,double z,int i,food* fruit);
bool setAntCarry();
void draw_colony(double* size);
void addAnts(int numberToAdd);
void enemyDrawH(enemy* evilBall);
void killAnt();
void enemyDrawV(enemy* evilBall);

#endif
