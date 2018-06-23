#include "../include/all.h"
#include <math.h>
//keyboard/mouse related functions

ants flik; //player
double tmp; //speed
double speed;//speed
int animation_ongoing;//for the animation
int scoreFood; //score
int scoreMaxNumberOfAnts;//score
int isMoving; //used to disable movment if ant is already moving
void on_timer(int id);

void keyboard_func(unsigned char key, int x, int y){


  switch (key) {
    case 27:    // esc <---> 27
      printf("NUMBER OF FOOD BROUGHT HOME:%d\n",scoreFood);
      printf("MAX NUMBER OF ANTS: %d\n",scoreMaxNumberOfAnts);
      exit(0);
      break;
      //move right
    case 'D':
    case 'd':
      if(!isMoving){
        if (flik.antXPosition[0] + 0.1 < 29){
          isMoving =1;
          animation_ongoing = 1;
          glutTimerFunc(10, on_timer, 1);
        }
      }
      break;
      //move left
    case 'A':
    case 'a':
      if(!isMoving){
        if(flik.antXPosition[0] - 0.1 > 0){
          isMoving =1;
          animation_ongoing = 1;
          glutTimerFunc(10, on_timer, 0);
        }
      }
      break;
      //move up
    case 'W':
    case 'w':
      if(!isMoving){
        if(flik.antYPosition[0] -0.1 >-28.5){
          isMoving =1;
          animation_ongoing = 1;
          glutTimerFunc(10, on_timer, 2);
        }
      }
      break;
      //move down
    case 'S':
    case 's':
      if(!isMoving){
        if(flik.antYPosition[0]+0.1 < 0.5){
          isMoving =1;
          animation_ongoing =1;
          glutTimerFunc(10, on_timer, 3);
        }
      }
      break;
      //enable/disable debugMod
      //debugMod: prints the main ant location,collisons and food spawing.
    case '=':
      if(debugMod){
        debugMod =0;
      }else{
        debugMod =1;
      }
      break;
  }
}


//movment function for the ants
void on_timer(int id){

  speed +=0.1;
  tmp = 0.1;

  //check what function was called and move them in the called maner
  //case 1: (move right);
  //move the main ant right and for all the other move them so that
  //they follow him... same for case0/2/3/

  switch(id){
    case 1:
      flik.antXPosition[0] += tmp;
      for(int i = 1;i<flik.numberOfAnts;i++){
        switch (flik.antMovmentDirection[i]) {
          case 0:
            flik.antXPosition[i] -=tmp;
            break;
          case 1:
            flik.antXPosition[i] +=tmp;
            break;
          case 2:
            flik.antYPosition[i] -=tmp;
            break;
          case 3:
            flik.antYPosition[i] +=tmp;
            break;
        }
      }
    break;

    case 0:
      flik.antXPosition[0] -= tmp;
      for(int i = 1;i<flik.numberOfAnts;i++){
        switch (flik.antMovmentDirection[i]) {
          case 0:
            flik.antXPosition[i] -=tmp;
            break;
          case 1:
            flik.antXPosition[i] +=tmp;
            break;
          case 2:
            flik.antYPosition[i] -=tmp;
            break;
          case 3:
            flik.antYPosition[i] +=tmp;
            break;
        }
      }
      break;

    case 2:
      flik.antYPosition[0] -= tmp;
      for(int i = 1;i<flik.numberOfAnts;i++){
        switch (flik.antMovmentDirection[i]) {
          case 0:
            flik.antXPosition[i] -=tmp;
            break;
          case 1:
            flik.antXPosition[i] +=tmp;
            break;
          case 2:
            flik.antYPosition[i] -=tmp;
            break;
          case 3:
            flik.antYPosition[i] +=tmp;
            break;
        }
      }
      break;

    case 3:
      flik.antYPosition[0] += tmp;
      for(int i = 1;i<flik.numberOfAnts;i++){
        switch (flik.antMovmentDirection[i]) {
          case 0:
            flik.antXPosition[i] -=tmp;
            break;
          case 1:
            flik.antXPosition[i] +=tmp;
            break;
          case 2:
            flik.antYPosition[i] -=tmp;
            break;
          case 3:
            flik.antYPosition[i] +=tmp;
            break;
        }
      }
      break;
  }


  //the ant got to his location enable movment and set the speed to 0
  //stop the movement
  if(speed >= 0.9){
    if(debugMod){
      printf("MAIN ANT POSITION: <<%lf>> <<%lf>>\n",flik.antXPosition[0],flik.antYPosition[0]);
    }
    isMoving = 0;
    animation_ongoing = 0;
    speed = 0;
    //after the movement was done change the direction of all the ants so that they
    //look where the ant infront of them was looking
    flik.antMovmentDirection[0] = id;
    for (int i =1;  i < flik.numberOfAnts; i++) {
      flik.antMovmentDirection[flik.numberOfAnts-i] = flik.antMovmentDirection[flik.numberOfAnts-i-1];
    }
  }

  //call the draw function again
  switch (id) {
    case 0:
      if (animation_ongoing ) {
        glutTimerFunc(10, on_timer, 0);
      }
      break;
    case 1:
      if (animation_ongoing) {
        glutTimerFunc(10, on_timer, 1);
      }
      break;
    case 2:
      if (animation_ongoing) {
        glutTimerFunc(10, on_timer, 2);
      }
      break;
    case 3:
      if (animation_ongoing) {
        glutTimerFunc(10, on_timer, 3);
      }
      break;
  }

	glutPostRedisplay();
}
