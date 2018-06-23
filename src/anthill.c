#include "../include/all.h"

ants flik; //player
food fruit; //pickups
enemy evilBallHorizontal; //enemyH
enemy evilBallVertical; //enemyV
int scoreFood; //score
int scoreMaxNumberOfAnts; //score



static void on_display(void);
static void on_reshape(int width, int height);
void startup(void);

int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutSetWindowTitle("Anthill");

    //set begining variables
    startup();
    glutKeyboardFunc(keyboard_func);
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);

    glClearColor(0.51, 0.86, 0.77, 0);

    glutMainLoop();

    return 0;
}

static void on_display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();

    //loking at the main ant
    gluLookAt(flik.antXPosition[0], 5, flik.antYPosition[0] +5,
       flik.antXPosition[0],1,flik.antYPosition[0],
       0, 1, 0);


    draw_floor(); //creates the floor
    draw_colony(&size);//home drawn
    draw_food(&fruit);//pickups drawn
    draw_ant(flik); //player drawn

    //no more ants == you lost
    if(flik.numberOfAnts <= 0){
      printf("---CONGRATS---\n");
      printf("NUMBER OF FOOD BROUGHT HOME:%d\n",scoreFood);
      printf("MAX NUMBER OF ANTS: %d\n",scoreMaxNumberOfAnts);
      printf("---------------\n");
      exit(1);
    }

    //draw enemies
    enemyDrawH(&evilBallHorizontal);
    enemyDrawV(&evilBallVertical);

    hud();//top-left number of ants alive
    glutSwapBuffers();
  }

static void on_reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 120);
}
