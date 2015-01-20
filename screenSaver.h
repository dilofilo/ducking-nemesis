#ifndef SCREEN_SAVER_H
	#define SCREEN_SAVER_H
#include <GL/glut.h>
#include <pthread.h>
#include <math.h>

using namespace std;

///Include source code.
#include "equationSolver.cpp" //includes a few functions
#include "ball.h" //includes ball vector
#include "table.h" //Includes table*
#include "ballThreads.cpp" //includes mailboxes and threading stuff.
#include "ball.cpp" 
#include "table.cpp" 

///Static Global Variables - Initialized in the class ScreenSaver's constructor.
static int WIDTH;
static int HEIGHT;
static int DELTA_T;
//program specific stuff
static int NUM_BALLS;
static int Z_CAMERA;

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
		for(int i = 0; i< NUM_BALLS ; i++) delete ball[i];
		delete table;
	}
	
	///Initializes the table and the balls.
	void init();
	void generateTable();
	void generateBall();
	///Memory and thread closing handling.
	void exitter(int& argc , char** argv);

	///Called to start.
	void execute();
	

	///Control functions
	void display();
	void reshape(int w , int h);
	void timer(int value);

	///User I/O function
	void handleMouse(int button , int state , int x , int y);
	void handleKeyboard(unsigned char key , int x , int y);
	void handleSpecialKey(unsigned char key , int x , int y);

};

#endif