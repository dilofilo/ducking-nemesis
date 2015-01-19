#include <GL/glut.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <math.h>

#define DELTA_T 50.0
#define WIDTH 480
#define HEIGHT 320

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
	///Set background to black.
	glClearColor( 0.0 , 0.0 , 0.0 , 1.0);
	glFlush();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();
	glPushMatrix();
	gluLookAt( 0.0 , 0.0 , 7.0 , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 ,0.0); // Focus camera at 0,0,0. ZCAMERA defined in main.cpp
	glPushMatrix();
	
	glColor3f(1,1,1);

		glutSolidSphere( 2.0 , 50 , 50 );
	
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();

}


void reshape(int w, int h) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w/ (GLfloat)h, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	glFlush();
}


int main(int argc, char** argv) {
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50);
	glutCreateWindow("testing");
	init();
	

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}