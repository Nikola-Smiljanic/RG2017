#ifndef GLOBALVARIABLES_H_INCLUDED
#define GLOBALVARIABLES_H_INCLUDED
/* ^^ these are the include guards */
#include <stdbool.h>

//for global variables
extern int animation_ongoing; //for walking
extern double speed; //for walking
extern int debugMod; //debugMod
extern double size; //size of colony
extern int isMoving; //test for moving
extern double enemyMove; //for enemy movement
extern int scoreFood; //score
extern int scoreMaxNumberOfAnts; //scor


//struct for food
typedef struct Food{
  int numberOfFood;
  double foodXPosition[100];
  double foodYPosition[100];
  int isSpawned[100];
      /*
      / 0-no
      / 1-yes
     */
}food;

//struct for the player
typedef struct{
  int numberOfAnts;
  double antXPosition[100];
  double antYPosition[100];
  int hasFood[100];
  int antMovmentDirection[100];
        /*
        / 0 - left
        / 1 - right
        / 2 - up
        / 3 - down
       */
}ants;

//struct for enemy
typedef struct{
  double enemyXPosition[9];
  double enemyYPosition[9];
  double enemySpeed[9];
}enemy;

extern ants flik; //player
extern food fruit; //food/pickups
extern enemy evilBallHorizontal;//enemyH
extern enemy evilBallVertical;//enemyV

extern GLuint dirt[2];//for texture

#endif
