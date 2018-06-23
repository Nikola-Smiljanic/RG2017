#include "../include/all.h"

ants flik;

void hud(){
  // Making the projection 2D for the HUD
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0, 800, 600, 0.0, -1.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_CULL_FACE);

  //setting depth buffer to -1 so i can draw the hud
  glClear(GL_DEPTH_BUFFER_BIT);
  glScalef(20,20,20);
  glBegin(GL_QUADS);

  //craetes hp bar in the top left corner that represents the numberOfAnts
  float k = 0;
    glColor3f(1, 0, 0);
    for(int i = 0; i < flik.numberOfAnts; i++) {
      glVertex2f(0,k);
      glVertex2f(1,k);
      glVertex2f(1,k+0.3);
      glVertex2f(0,k+0.3);
      k+=0.5;
    }
  glEnd();

  // Making sure we can render 3d again
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LIGHTING);
}
