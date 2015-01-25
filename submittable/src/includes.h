#ifndef INCLUDES_H
	#define INCLUDES_H
#include <iostream> 	//... cout for debug statements
#include <cstdlib> 		//... includes rand()
#include <time.h>		//... used to set time NULL for rand

#include <GL/gl.h>		//
#include <GL/glut.h>	//... Image rendering libraries
#include <GL/glui.h>	//... includes menu management
#include <SDL/SDL.h>	//... used for texture loading (from .bmp files)
#include <pthread.h>	//... used for threading, mutexing, conditional variables

#include <cmath>		//... general purpose math
#include <vector>		//... included for std::vector
#include <queue>		//... mailBox for thread's communication system
#include <limits>

using namespace std;
#ifndef GRAVITY
	#define GRAVITY 		0.001
#endif
#ifndef PI
	#define PI 				3.14159265359
#endif
#ifndef BOUNDING_RADIUS
	#define BOUNDING_RADIUS 0.5
#endif
#ifndef MAX_BALLS
	#define MAX_BALLS 		75
#endif
///Global Variables

static float NEG_MIN_FLOAT 	= -10000.0f;
vector<float> vecUnity	{ 1.0 , 1.0 , 1.0};
vector<float> vecZero	{ 0.0 , 0.0 , 0.0};



///GUI Variables

	static int Dimensional_state=2;

	///Ball's rendering parameters
		static int KABIR_SLICES 	= 50;
		static int KABIR_STACKS 	= 50;
		static int H_SLICES			= 7;
		static int H_STACKS			= 3;
		static int HARMAN_SLICES	= 10;
		static int HARMAN_STACKS	= 7; 
		static int NUM_SLICES 		= KABIR_SLICES;
		static int NUM_STACKS 		= KABIR_STACKS;
		static int BLINK_TIME 		= 10;
	

		
	
///Physics Variables
		static float gravity 					= 0.0;
		static float coefficientRestitution 	= 1.0;




	
#endif