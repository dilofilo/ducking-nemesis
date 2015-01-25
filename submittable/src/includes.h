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




	
#endif