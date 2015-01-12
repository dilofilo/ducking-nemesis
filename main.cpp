#include <pthread>
#include <GL/glut.h>

#include <math.h>
#include <iostream>
#include <string>
#include <stringstream>


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
void init(Table* table, vector<Ball*>& ballList , int& numThreads) {
	
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


///function to handle reshaping of windows
void reshape(int w, int h) {

}

///function to handle the keys pressed by the user - including , escape, spacebar and F
void keHandler(unsigned char key , int x , int y) {

}

///function to handle the actual display jobs.
void display() {

}
int main(int argc, char** argv) {
	
	//Code to convert string to int
	int numThreads = 0;
	string myString = argv[1];
	istringstream buffer(myString);
	buffer >> numThreads;
	//Code to convert numThreads to int is complete.

	screenSaver obj = new screenSaver(numThreads);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWIndowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50); //50,50 are arbitrary coordinates.
	int windowID = glutCreateWindow();
	//TODO : MENU WALI THINGS.
	init(  table, ballList , numThreads);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyHandler);
}