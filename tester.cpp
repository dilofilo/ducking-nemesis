#include <GL/glut.h>
#include <vector>
#include <iostream>
using namespace std;

#include "table.h"
#include "table.cpp"
//#include "ball.h"
//#include "ball.cpp"

Table * mytable ;
//Ball* balls;

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

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	glPushMatrix();
	gluLookAt( 0.0 , 0.0 , 5.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 ,0.0); // Focus camera at 0,0,0. Z_CAMERA defined in main.cpp
	glPushMatrix();

	
	mytable->display();
	

	glPopMatrix();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void reshape(int w , int h) {
	WIDTH = w;
	HEIGHT = h;
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
	mytable= new Table(-0.9, -0.90, 0.90, -0.90, 0.90, 0.90, -0.90, 0.90, 0.0 , 0.0 , 1.0, 0.0);
	//mytable->print();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;

}