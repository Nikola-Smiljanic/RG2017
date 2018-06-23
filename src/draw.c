#include "../include/all.h"
#include <math.h>


ants flik; //player
food fruit; //pickups
enemy evilBallHorizontalBall; //enemies
GLuint dirt[2]; //texture
void colony_material(); //material for the colony
void foodMaterialU(); //material for food
void antBodyM();//material for the body of the ant
void antHeadM();//material for the head of the ant
void antObjM();//material for the carrying item
void evilBallHorizontalBall_material();//material for the pickups
double size;//size of the colony
int scoreFood;//score
int scoreMaxNumberOfAnts;//score



//creates floor for ants
//creates a square(30x30) and adds the dirt texture to it
void draw_floor(){
  glEnable(GL_LIGHTING);
      glPushMatrix();
        glRotatef(-90,1,0,0);
        glBindTexture(GL_TEXTURE_2D, dirt[0]);
        glPushMatrix();
        glTranslatef(0,0,1);
        glBegin(GL_QUADS);
            glNormal3f(0, 0, 1);

            glTexCoord2f(0, -0);
            glVertex3f(-1, -1, 0);

            glTexCoord2f(60, 0);
            glVertex3f(30, -1, 0);

            glTexCoord2f(60, 6);
            glVertex3f(30, 30, 0);

            glTexCoord2f(0, 60);
            glVertex3f(-1, 30, 0);
        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);

      glPopMatrix();
  glDisable(GL_LIGHTING);
}


//main draw ant function
void draw_ant(ants flik){
  for(int i=0;i<flik.numberOfAnts;i++){
    ant(flik.antXPosition[i],flik.antYPosition[i],flik.antMovmentDirection[i],flik.hasFood[i]);
  }
}

//ant drawing function
void ant(double x,double y,int direction,int food){
  glEnable(GL_LIGHTING);
  glPushMatrix();
    //move ant to set location
    glTranslatef(x,1,y);
    //looking direction
    switch (direction) {
      case 0:
        glRotatef(180,0,1,0);
        break;
      case 1:
        break;
      case 2:
        glRotatef(90,0,1,0);
        break;
      case 3:
        glRotatef(-90,0,1,0);
        break;
    }
    glPushMatrix();
      //drawing the body
      glScalef(1.2,0.4,0.2);
      antBodyM();
      glutSolidCube(0.2);
      glPushMatrix();
        //drawing the head
        glTranslatef(0.1,0.1,0);
        glScalef(0.1,0.1,0.3);
        glColor3f(1,1,1);
        antHeadM();
        glutSolidCube(1);
        glPushMatrix();
          if(food){
            //drawing the item
            glTranslatef(0,0.2,0);
            antObjM();
            glutSolidTeapot(1);
          }
        glPopMatrix();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  glDisable(GL_LIGHTING);
}

//food drawing function
void draw_food(food* fruit){

  glEnable(GL_LIGHTING);

  //checks if the food is SPAWNED, if it isnt
  //creates it and places it in a random location
  for (int i = 0; i<fruit->numberOfFood;i++){
    if(fruit->isSpawned[i] == 0){
      fruit->isSpawned[i] = 1;
      double PositionX1 = (rand()%10) *3 +2;
      double PositionY1 = (-((rand()%10)*3 +2)+0.5);
      fruit->foodXPosition[i] = PositionX1;
      fruit->foodYPosition[i] = PositionY1;

      glPushMatrix();
        glTranslatef(PositionX1,1,PositionY1);
        foodMaterialU();
        glutSolidTeapot(0.2);
      glPopMatrix();

      if(debugMod){
        printf("FRUIT SPAWNED\n");
        printf("FRUIT POSITION:\n");
        printf("----X-----||-----Y----\n");
        printf("<%lf><%lf>\n",fruit->foodXPosition[i],fruit->foodYPosition[i]);
      }
    }
    //food is spawned,just redraw it
    else{
      redrawFood(fruit->foodXPosition[i],fruit->foodYPosition[i],i,fruit);
    }

  }

  glDisable(GL_LIGHTING);
}

//redraw food if its not taken
void redrawFood(double x,double z,int i,food* fruit){
  glEnable(GL_LIGHTING);

  //if the player is at the food location check if he has enough space
  //to care it and if he has despawn the food and set it on the player
  if((abs(x-flik.antXPosition[0]) < 0.1) && (abs(z-flik.antYPosition[0])<0.1)){
    if(debugMod){
      printf("COLISION\n");
    }
    bool isFull = setAntCarry();
    if(isFull){
      glPushMatrix();
        glTranslatef(x,1,z);

        foodMaterialU();

        glutSolidTeapot(0.2);
      glPopMatrix();
    }else{
    fruit->isSpawned[i] = 0;
    }
  }else{
    glPushMatrix();
      glTranslatef(x,1,z);
      foodMaterialU();
      glutSolidTeapot(0.2);
    glPopMatrix();
  }

  glDisable(GL_LIGHTING);

}


//add food to ant if he has any space left
bool setAntCarry(){
  for(int i=0;i<flik.numberOfAnts;i++){
    if(flik.hasFood[i] == 0){
      flik.hasFood[i] = 1;
      return false;
    }
  }
  return true;
}


//creates home and adds score
void draw_colony(double* size){

  glEnable(GL_LIGHTING);

  double numberOfFood=0;
  //when the player is at the home location check if he has any food on him
  //and if he has increase the size of the colony and the score
  if(flik.antXPosition[0] <= 0.1 && flik.antYPosition[0]>=0.5){
    if(debugMod){
      printf("AT HOME\n");
    }
    int i=1;
    if(flik.hasFood[0] == 1){
      numberOfFood=1;
      while(1){
        if(flik.hasFood[i] == 0)
          break;
        else{
          numberOfFood++;
          i++;
        }
      }
      *size += numberOfFood*0.04;
      scoreFood+=numberOfFood;

      for(int j=0;j<i;j++){
        flik.hasFood[j]=0;
      }
      if(numberOfFood+flik.numberOfAnts>scoreMaxNumberOfAnts){
        scoreMaxNumberOfAnts+=numberOfFood;
      }
      addAnts(numberOfFood);
    }
  }
  glPushMatrix();
    glScalef(*size,*size,*size);
    glPushMatrix();
      glPushMatrix();

        colony_material();
        glutSolidCube(1);

        GLUquadric* cone  = gluNewQuadric();
        if( cone == 0){
          printf("NO MORE MEMORY\n");
          exit(-1);
        }
        glRotatef(-90,1,0,0);
        glTranslatef(0,0,0.5);
        gluCylinder(cone,0.5,0,1,100,100);

      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

  glDisable(GL_LIGHTING);

}


//add ants to player if he brings food home
void addAnts(int numberToAdd){
  for(int i =0;i<numberToAdd;i++){
   if(flik.antMovmentDirection[flik.numberOfAnts+i-1] ==0){
     flik.antXPosition[flik.numberOfAnts+i] = flik.antXPosition[flik.numberOfAnts-1+i]+1;
     flik.antYPosition[flik.numberOfAnts+i] = flik.antYPosition[flik.numberOfAnts-1+i];
     flik.antMovmentDirection[flik.numberOfAnts+i] = 0;
   }
   else{
     flik.antXPosition[flik.numberOfAnts+i] = flik.antXPosition[flik.numberOfAnts-1+i];
     flik.antYPosition[flik.numberOfAnts+i] = flik.antYPosition[flik.numberOfAnts-1+i]-1;
     flik.antMovmentDirection[flik.numberOfAnts+i] = 3;
    }
  }


  flik.numberOfAnts+=numberToAdd;

}


//drays enemy that moves horizontaly
void enemyDrawH(enemy* evilBallHorizontal){

  glEnable(GL_LIGHTING);
  for( int i=0;i<9;i++){
    glPushMatrix();
      if(evilBallHorizontal->enemyXPosition[i]>29 || evilBallHorizontal->enemyXPosition[i]<0){
        evilBallHorizontal->enemySpeed[i] *=-1;
      }

      evilBallHorizontal->enemyXPosition[i] += enemyMove*evilBallHorizontal->enemySpeed[i];
      glTranslatef(evilBallHorizontal->enemyXPosition[i] ,1,evilBallHorizontal->enemyYPosition[i]);
      evilBallHorizontalBall_material();
      glutSolidSphere(0.3,20,20);
    glPopMatrix();

    if(fabs(evilBallHorizontal->enemyXPosition[i] - flik.antXPosition[0]) <0.2  &&
       fabs(evilBallHorizontal->enemyYPosition[i] - flik.antYPosition[0])<0.2){
      if(debugMod){
        printf("COLISION\n");
      }
      killAnt();
    }

  }
  glDisable(GL_LIGHTING);
}


//drays enemy that moves horizontaly and checks for colision
void enemyDrawV(enemy* evilBall){

    glEnable(GL_LIGHTING);
    for( int i=0;i<9;i++){
      glPushMatrix();
        if(evilBall->enemyYPosition[i]<-28.5 || evilBall->enemyYPosition[i]>0.5){
          evilBall->enemySpeed[i] *=-1;
        }

        evilBall->enemyYPosition[i] += enemyMove*evilBall->enemySpeed[i];
        glTranslatef(evilBall->enemyXPosition[i] ,1,evilBall->enemyYPosition[i]);
        evilBallHorizontalBall_material();
        glutSolidSphere(0.3,20,20);
      glPopMatrix();
      if(fabs(evilBall->enemyXPosition[i] - flik.antXPosition[0]) <0.2  &&
         fabs(evilBall->enemyYPosition[i] - flik.antYPosition[0])<0.2){
        if(debugMod){
          printf("COLISION\n");
        }
        killAnt();
      }

    }
    glDisable(GL_LIGHTING);
}

//colison with enemy happened remove the first ant
void killAnt(){
  double tmpX = flik.antXPosition[0];
  double tmpY = flik.antYPosition[0];
  for(int i =0;i<flik.numberOfAnts;i++){
    flik.antXPosition[i] = flik.antXPosition[i+1];
    flik.antYPosition[i] = flik.antYPosition[i+1];
    flik.antMovmentDirection[i] = flik.antMovmentDirection[i+1];
  }
  flik.antXPosition[flik.numberOfAnts-1] = tmpX;
  flik.antYPosition[flik.numberOfAnts-1] = tmpY;
  flik.numberOfAnts--;
  if(debugMod){
    printf("LOST AN ANT\n");
  }
}


// -------------------------
// MATERIAL FOR ALL POLIGONS
// -------------------------

void evilBallHorizontalBall_material(){
  GLfloat ambient_EB[] = { 0.0f, 0.1f, 0.4f, 1 };
  GLfloat diffuse_EB[] = { 0.05, 0.95, 0.95f, 1 };
  GLfloat specular_EB[] = { 1, 1, 1, 1 };
  GLfloat shininess = 30;

  glColor4f(0.05f, 0.95f, 0.95f,1);

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_EB);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_EB);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_EB);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void colony_material(){

  GLfloat ambient_colony[] = { 0.5f, 0.35f, 0.05f, 1 };
	GLfloat diffuse_colony[] = { 0.6, 0.35, 0.05f, 1 };
	GLfloat specular_colony[] = { 1, 1, 1, 1 };
	GLfloat shininess = 30;

  glColor4f(0.5f, 0.35f, 0.05f,1);

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_colony);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_colony);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_colony);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

}


void foodMaterialU(){
  GLfloat ambient_foodU[] = { 0.3, 0, 0, 1 };
  GLfloat diffuse_foodU[] = { 0.9, 0.1, 0.05, 1 };
  GLfloat specular_foodU[] = { 1, 1, 1, 1 };
  GLfloat shininess = 30;

  glColor4f(0.9, 0, 0.05,1);

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_foodU);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_foodU);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_foodU);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

}

void antBodyM(){
  GLfloat ambient_antM[] = { 0.01, 0.3, 0, 1 };
  GLfloat diffuse_antM[] = { 0.1, 0.9, 0.05, 1 };
  GLfloat specular_antM[] = { 0.1, 0.9, 0.1, 1 };
  GLfloat shininess = 15;

  glColor4f(0.1, 0.9, 0.05,1);

  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_antM);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_antM);
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular_antM);
  glMaterialf(GL_FRONT, GL_SHININESS, shininess);

}

void antHeadM(){
  GLfloat ambient_antM[] = { 0.9, 0.01, 0, 1 };
  GLfloat diffuse_antM[] = { 0.3, 0.1, 0.05, 1 };
  GLfloat specular_antM[] = { 0, 0, 0, 1 };
  GLfloat shininess =30;

  glColor4f(0.9, 0, 0.05,1);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_antM);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_antM);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_antM);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

}

void antObjM(){
  GLfloat ambient_antM[] = { 0, 0.9, 0.9, 1 };
  GLfloat diffuse_antM[] = { 0, 0.3, 0.6, 1 };
  GLfloat specular_antM[] = { 0, 0, 0, 1 };
  GLfloat shininess =25;

  glColor4f(0, 1,1,1);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_antM);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_antM);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_antM);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

}
