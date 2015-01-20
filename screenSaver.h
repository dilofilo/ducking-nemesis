#ifndef SCREEN_SAVER_H
	#define SCREEN_SAVER_H
//C++ includes

#include <GL/glut.h>
#include <pthread.h>
#include <math.h>
#include <vector>
#include <queue>
#include <time.h>
#include <iostream>
using namespace std;

///Static Global Variables - Initialized in the class ScreenSaver's constructor.

static int WIDTH;
static int HEIGHT;
static int DELTA_T;
///program specific stuff
static int selectedBall = 0;
static int NUM_BALLS;

///Stuff for ball generation
static float MAX_RADIUS = 1.0;
static float BOUND = 10.0;
static float MAX_VELOCITY = 0.1;

///Camera related variables
static float X_CAM = 0.0;
static float Y_CAM = 0.0;
static float Z_CAM = 50.0;
static float X_CAM_FOCAL = 0.0;
static float Y_CAM_FOCAL = 0.0;
static float Z_CAM_FOCAL = 0.0;
///0.57 is root(1/3)
static float UP_X = 0.0;
static float UP_Y = 1.0;
static float UP_Z = 0.0;

///R^3 space things
static float ROTATE_X = 0.0;
static float ROTATE_Y = 0.0;
static float ROTATE_Z = 0.0;


///Include source code.

#include "equationSolver.cpp" //includes a few functions
#include "table.h" //Includes table*
#include "ball.h" //includes ball vector
#include "ballThreads.cpp" //includes mailboxes and threading stuff.
#include "ball.cpp" 
#include "table.cpp" 


class ScreenSaver {

public:
	///Variables
	bool isPaused;
	bool isFullScreen;
	
	///Constructors and Destructors
	ScreenSaver(int numBalls) {
		isPaused = false;
		isFullScreen = false;
		NUM_BALLS = numBalls; //Static variable set.
		WIDTH = 640;
		HEIGHT = 480;
		DELTA_T = 3.0; //Arbitrary Number.
	}
	~ScreenSaver() {
		for(int i = 0; i< NUM_BALLS ; i++) 
			delete ball[i];

		delete table;
	}
	
	///Initializes the table and the balls.
	void init();
	void generateTable();
	void generateBall();

	///Memory and thread closing handling.
	void exitter();

	///Called to start.
	void execute(int& argc , char** argv);

	//End of Class
};

	//Wish I could have been in the class.

	///Control functions
	void display();
	void reshape(int w , int h);
	void timer(int value);

	///User I/O function
	void handleMouse(int button , int state , int x , int y);
	void handleKeyboard(unsigned char key , int x , int y);
	void handleSpecial(int key , int x , int y);


ScreenSaver* mainScreenSaver;
#endif