#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>
#include <unistd.h>
using namespace std;
#define Z_CAMERA 10.0
#define NUMSLICES 50
#define NUMSTACKS 50
#define BALL_ZPLANE 0.0
#define REDUCTIONFACTOR 0.000001

#include "table.h"
#include "table.cpp"
#include "ball.h"
#include "ball.cpp"

Table * table ;
Ball* ball;
clock_t oldtime;
clock_t newtime;
clock_t deltaT;



static float WIDTH;
static float HEIGHT;

void init() {
	
	glEnable(GL_DEPTH_TEST); //Ensure that 3d figures are drawn in the correct order.
	glCullFace(GL_BACK); //Ensures that when a solid is drawn, the back figuyres arent draw. Thats a 2x improvmenet in performance.
	glEnable(GL_CULL_FACE);


	//R*R*R space to camera space setup.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f , //FOV in yz plane.
			(float)WIDTH/(float)HEIGHT , //ratio
			1.0f , //Near clipping distance
			10000000.0f //Far clipping distance.
		);
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();

	///Set background to black. TODO
	glClearColor( 0.0 , 0.0 , 0.0 , 1.0);
	glutFullScreen();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	glPushMatrix();
	gluLookAt( 0.0 , 0.0 , Z_CAMERA , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 ,0.0); // Focus camera at 0,0,0. ZCAMERA defined in main.cpp
	glPushMatrix();

	newtime=clock();
	deltaT=  (double)(newtime - oldtime) ;
	oldtime=newtime;
	//table->display();
	ball->display();

	ball->setxCentre( ball->getxCentre() + REDUCTIONFACTOR*deltaT*(ball->getxVelocity()));
	ball->setyCentre( ball->getyCentre() + REDUCTIONFACTOR*deltaT*(ball->getyVelocity()));

	glPopMatrix();
	glPopMatrix();



	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w , int h) {
	WIDTH = w;
	HEIGHT = h;
	//table->reshape(w,h);
	ball->reshape(w,h);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glFlush();

}


int main(int argc, char** argv) {
	WIDTH = 600;
	HEIGHT = 600;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50);
	glutCreateWindow("testing");
	init();
	
	ball = new Ball( 1.0 , 0.0 , 0.02 , 0.6 , 0.0 , 0.0 , WIDTH , HEIGHT);
		ball->setxVelocity(-10.0);
		ball->setyVelocity(0.0);
	table= new Table(-5.0, -5.0, 5.0, -5.0, 5.0, 5.0, -5.0, 5.0, 0.0 , 0.0 , 0.70, 0.20 , WIDTH , HEIGHT); //TODO FIGURE OUT CORRECT PROPORTIONS
	//mytable->print();
	oldtime=clock();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;

}