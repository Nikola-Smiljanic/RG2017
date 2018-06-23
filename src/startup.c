#include "../include/all.h"

ants flik; //player
food fruit; //food
enemy evilBallHorizontal; //enemyH
enemy evilBallVertical; //enemyV
int debugMod; //denugMod ON/OFF
double size; //colony size
GLuint dirt[2];//texture
int isMoving;//movement
double enemyMove; //enemy Movement
int scoreFood; //score
int scoreMaxNumberOfAnts;//score


void enemy_on_timer(int id);

void startup(){

  int i;
  srand(time(NULL)); //setting random number gen.
  int k = 0;
  scoreFood = 0;//score at the start
  scoreMaxNumberOfAnts = 3;//score at the start

  //enemy (horizontal) start position and random speed
  for(i = 0;i<9;i++){
    evilBallHorizontal.enemyXPosition[i] = 0;
    evilBallHorizontal.enemyYPosition[i] = -7.5-k;
    k+=2;
    //setting that every enemy has a diffrent speed
    evilBallHorizontal.enemySpeed[i] = (rand() %10 +1)*0.3;
  }
  k=0;
  //enemy (vertical) start position and random speed
  for(i = 0;i<9;i++){
    evilBallVertical.enemyXPosition[i] = 12+k;
    evilBallVertical.enemyYPosition[i] = 0.5;
    k+=2;
    //setting that every enemy has a diffrent speed
    evilBallVertical.enemySpeed[i] = -(rand() %10 +1)*0.3;
  }

  enemyMove = 0;//for enemy movemt
  //start enemy movement
  glutTimerFunc(30,enemy_on_timer, 0);

  //setting up light
  GLfloat light_position[] = { -5, 5, 3, 0 };
  GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1 };
	GLfloat light_diffuse[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat light_specular[] = { 0.5, 0.5, 0.5, 1 };


  glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

  //adding texture for the floor
  Image * image;

  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV,
            GL_TEXTURE_ENV_MODE,
            GL_REPLACE);

  image = image_init(0, 0);

  image_read(image, "../textures/dirt.bmp");
  glGenTextures(2, dirt);

  glBindTexture(GL_TEXTURE_2D, dirt[0]);
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
               image->width, image->height, 0,
               GL_RGB, GL_UNSIGNED_BYTE, image->pixels);


  glBindTexture(GL_TEXTURE_2D, 0);

  image_done(image);


  debugMod = 0; //debugMod OFF
  isMoving = 0; //enabling movement
  animation_ongoing = 0; //enabling movement
  speed = 0; //starting speed
  size = 1; //staring colony size
  fruit.numberOfFood = 5; //starting numnber of food


  //ant starting POSITION (MAIN ANT)
  flik.antXPosition[0] = 3.0;
  flik.antYPosition[0] = 0.5;
  flik.antMovmentDirection[0] = 1;

  //ant starting POSITION (2. ANT)
  flik.antXPosition[1] = 2.0;
  flik.antYPosition[1] = 0.5;
  flik.antMovmentDirection[1] = 1;

  //ant starting POSITION (3. ANT)
  flik.antXPosition[2] = 1.0;
  flik.antYPosition[2] = 0.5;
  flik.antMovmentDirection[2] = 1;

  //starting number of ants
  flik.numberOfAnts = 3;

  //no ant has food at the beginning
  for(i = 0;i<100;i++){
    flik.hasFood[i] = 0;
    fruit.isSpawned[i] = 0;
  }
}

//always on
void enemy_on_timer(int id){
  enemyMove =0.1;
    glutTimerFunc(30,enemy_on_timer, 0);
  glutPostRedisplay();
}
