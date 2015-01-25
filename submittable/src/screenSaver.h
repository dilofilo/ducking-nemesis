#ifndef SCREEN_SAVER_H
	#define SCREEN_SAVER_H

#include "includes.h"
#include "ball.h"
#include "table.h"
#include "ballThreads.h"
#include "skybox.h"
#include "menu.h"

	extern vector<Ball*> ball;
	extern Table* table;


	///program specific stuff

	extern volatile int NUM_BALLS;
	extern int WIDTH;
	extern int HEIGHT;
	extern float DELTA_T;
	extern float X_CAM_FOCAL;
	extern float Y_CAM_FOCAL;
	extern float Z_CAM_FOCAL;
	extern float UP_X;
	extern float UP_Y;
	extern float UP_Z;

	///R^3 space rendering variables
	extern float ROTATE_X;
	extern float ROTATE_Y;
	extern float ROTATE_Z;
	extern float Z_DISPLACE;





class ScreenSaver {
	///Variables
	bool 	alive;
	bool 	isPaused;
	bool 	isFullScreen;
	int  	windowID;
public:
	
	///Constructors and Destructors
	ScreenSaver(int numBalls) {
		alive 				= true;
		isPaused 			= false;
		isFullScreen 		= false;
		NUM_BALLS 			= numBalls; //Static variable set.
		WIDTH 				= 640; 		//pixels
		HEIGHT 				= 480; 		//pixels
		DELTA_T 			= 5.0; 		//Arbitrary Number, units are milliseconds.

	}
	~ScreenSaver() {
		for(int i = 0; i< NUM_BALLS ; i++) 
			delete ball[i];
		delete table;
	}
	///Functional functions
	int 		getWindowID() { return windowID;}
	bool 		getIsPaused() { return isPaused; }
	void 		togglePaused() { isPaused = !isPaused; }
	bool 		getIsFullScreen() { return isFullScreen ; }
	void 		toggleFullScreen() { isFullScreen = !isFullScreen; }
	bool 		isAlive() { return alive; }
	void 		kill() { alive = false; }

	///Initializes the table and the balls.
	void 		init();
	void 		initLighting(); /// Function to start up the lighting effects.

	void 		generateTable();
	void 		generateBall();

	///Memory and thread closing handling.
	void 		exitter();

	///Called to start.
	void 		execute(int& argc , char** argv);

	// Number of Balls modification functions
	void 		addBall();
	void 		deleteBall();

	//End of Class
};

	//These functions are required to be outside the class because of glut.

	///Control functions
	void 		display();
	void 		reshape(int w , int h);
	void 		timer(int value);


	///User I/O function
	void 		handleMouse(int button , int state , int x , int y);
	void 		handleKeyboard(unsigned char key , int x , int y);
	void 		handleSpecial(int key , int x , int y);


#endif