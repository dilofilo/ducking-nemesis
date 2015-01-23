//Things needed to convert string to int
#define THREE_D
#include <GL/gl.h>
#include <GL/glut.h>
#include <pthread.h>
#include <math.h>
#include <vector>
#include <queue>
#include <time.h>
#include <string>
#include <sstream>
#include <iostream>

#include "screenSaver.h"
#include "screenSaver.cpp"



int main(int argc, char** argv) {
	//Convert string to int.
	string numBall_str = argv[1];
	istringstream buffer(numBall_str);
	int nBalls; buffer >> nBalls;
	mainScreenSaver = new ScreenSaver(nBalls);
	mainScreenSaver->execute(argc, argv);
	mainScreenSaver->exitter();
	return 0;
}