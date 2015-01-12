#include <pthread>
#include <GL/glut.h>

#include <math.h>
#include <iostream>

#include <screenSaver.h>
#include <screenSaver.cpp>
#include <ball.h>
#include <ball.cpp>
#include <table.h>
#include <table.cpp>


#define WIDTH 840
#define HEIGHT 680

using namespace std;

/// function to initialize views, camera etc for glut.
void init() {
	glEnable(GL_DEPTH_TEST); //Ensure that 3d figures are drawn in the correct order.
	glCullFace(GL_BACK); //Ensures that when a solid is drawn, the back figuyres arent draw. Thats a 2x improvmenet in performance.
	glEnable(GL_CULL_FACE);


	//R*R*R space to camera space setup.
	glMatrixMode(GL_PROJECTION);
	glLoadIDentity();
	gluPerspective( 45 , //FOV in yz plane.
			(float)WIDTH/(float)HEIGHT , //ratio
			0.1f , //Near clipping distance
			10000000f //Far clipping distance.
		)
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();

	///Set background to brown.
	glCLearColor( 0.54 , 0.49 , 0.41 , 1.0); 
}

int main(int argc, char** argv) {
	string numThreads = argv[1];

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWIndowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50); //50,50 are arbitrary coordinates.
	int windowID = glutCreateWindow();
	//TODO : MENU WALI THINGS.
	init();
}