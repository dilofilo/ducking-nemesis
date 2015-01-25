#ifndef SCREEN_SAVER_H
	#define SCREEN_SAVER_H

#include "includes.h"
#include "ball.h"
#include "table.h"
#include "ballThreads.h"
#include "skybox.h"
#include "menu.h"

    static int WIDTH;
	static int HEIGHT;
	static float NEAR_CLIPPING_DISTANCE 	= 1.0f;
	static float FAR_CLIPPING_DISTANCE 		= 100.0f;
	static float FOV_Y						= 45.0f;
///program specific stuff
	static int selectedBall 				= 0;
	static volatile int NUM_BALLS;

	///Stuff for ball generation
	static float MAX_RADIUS 				= 1.0;
	static float MAX_VELOCITY 				= 0.05;
	static int DELTA_T;

	///Camera related variables
	static float X_CAM 						= 0.0;
	static float Y_CAM 						= 0.0;
	static float Z_CAM 						= 50.0;
	static float X_CAM_FOCAL				= 0.0;
	static float Y_CAM_FOCAL 				= 0.0;
	static float Z_CAM_FOCAL 				= 0.0;
	static float UP_X 						= 0.0;
	static float UP_Y 						= 1.0;
	static float UP_Z 						= 0.0;

	///R^3 space rendering variables
	static float ROTATE_X 					= 0.0;
	static float ROTATE_Y 					= 0.0;
	static float ROTATE_Z 					= 0.0;
	static float Z_DISPLACE 				= 0.0;


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


ScreenSaver* mainScreenSaver;
#endif