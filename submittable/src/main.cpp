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

#include "includes.h"
#include "screenSaver.h"
#include "ball.h"
#include "table.h"
#include "ballThreads.h"
#include "skybox.h"
#include "menu.h"


extern ScreenSaver* mainScreenSaver;

int main(int argc, char** argv) {
	//Convert string to int.
	if( argc < 2) {

	} else {
		string numBall_str = argv[1];
		istringstream buffer(numBall_str);
		int nBalls; buffer >> nBalls;
		if( nBalls <= 0) {
			cout << " ###############################ERROR!~ ERROR!~ ###############################\n Input a positive number of balls please\n";
		} else if ( nBalls >= MAX_BALLS ) {
			cout << " ###############################ERROR!~ ERROR!~ ###############################\n Input a number less than " << MAX_BALLS << " please\n";
		} else {
			mainScreenSaver = new ScreenSaver(nBalls);
			mainScreenSaver->execute(argc, argv);
		}
	}
	return 0;
}