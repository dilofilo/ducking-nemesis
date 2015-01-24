#include <iostream> 	//... cout for debug statements
#include <cstdlib> 		//... includes 
#include <GL/gl.h>		//
#include <GL/glut.h>	//... Image rendering libraries
#include <GL/glui.h>	//... includes menu management
#include <SDL/SDL.h>	//... used for texture loading (from .bmp files)
#include <pthread.h>	//... used for threading, mutexing, conditional variables
#include <cmath>		//... general purpose math
#include <vector>		//... included for std::vector
#include <queue>		//... mailBox for thread's communication system
#include <time.h>		//... used to set time NULL for rand

using namespace std;

#define GRAVITY 0.001;
#define PI 3.14159265359

///Global Variables

vector<float> vecUnity{ 1.0 , 1.0 , 1.0};
vector<float> vecZero{ 0.0 , 0.0 , 0.0};

///GUI Variables
	//Lighting
		GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0}; //Black Color
		GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0}; //Green Color
		GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color
		GLfloat qaRed[] =   {1.0, 0.0, 0.0, 1.0}; //White Color

	    // Set lighting intensity and color
		GLfloat qaAmbientLight[]    = {0.2, 0.2, 0.2, 1.0};
		GLfloat qaDiffuseLight[]    = {0.8, 0.8, 0.8, 1.0};
		GLfloat qaSpecularLight[]   = {1.0, 1.0, 1.0, 1.0};
		GLfloat emitLight[]         = {0.9, 0.9, 0.9, 0.01};
		GLfloat Noemit[]            = {0.0, 0.0, 0.0, 1.0};
	    // Light source position
		GLfloat qaLightPosition[]   = {0.0, (GLfloat)2.0*BOUND , (GLfloat)2.0*BOUND, 0.5}; 

	///Ball's rendering parameters
		static int NUM_SLICES = 50;
		static int NUM_STACKS = 50;

	///GLUI static variables
		int obj=0;
		int obj2=0;
		int gravGui=0;
		int buttonmanager=1;
		int modeNO=0;
		float rotation_matrix[16] = { 1.0, 0.0, 0.0, 0.0,
	                              0.0, 1.0, 0.0, 0.0,
	                              0.0, 0.0, 1.0, 0.0,
	                              0.0, 0.0, 0.0, 1.0 };
	    float coEfficient=1.0;
	    GLUI_Rotation *rotatewala;
	    GLUI_Spinner  *coefficientwala;

		GLUI_RadioGroup *radioGroup;
		GLUI_RadioGroup *radioGroup2;
		GLUI *glUserInterface;
	


///Physics Variables
	static float gravity = 0.0;
	static float coefficientRestitution = 0.8;



///Threading Variables
	std::vector<pthread_t> vecBallThread;					//Threads
	std::vector<pthread_mutex_t> vecMutexBallPthreads;		//Lock for every thread

	vector<bool> threadTerminate;							//Termination Boolean
	vector<pthread_mutex_t> vecMutexThreadTerminate;		//Termination Mutex

	std::vector< std::queue<BallDetailsMessage> > mailBox; 	//Mailbox for each thread.
	std::vector<pthread_mutex_t> vecMutexMailBox;			//Lock for every ball's mailbox
	std::vector<pthread_cond_t> vecCondMailBoxReceived;		//Conditional variable for mailbox
	
	//Interaction between timer and each thread.
	pthread_mutex_t mutexStateVariableUpdate;				//Lock for timer to update booleans
	std::vector<bool> vecShouldBallUpdate;					//Boolean indicator
	static int numBallUpdates;								//Number of balls indicator to avoid an O(n) check
	std::vector<pthread_cond_t> vecCondBallUpdateBegin;		//Conditional variables to begin the update of every thread - Sent to every worker thread
	pthread_cond_t condBallUpdateComplete;					//Conditional variable for update completition - Sent to parent thread
	


