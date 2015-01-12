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