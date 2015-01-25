#ifndef INITIALISATION_CPP
	#define INITIALISATION_CPP

#include "screenSaver.h"
#include "ball.h"
#include "menu.h"
#include "table.h"
#include "ballThreads.h"

		extern vector<pthread_t> vecBallThread;
		extern vector<pthread_mutex_t> vecMutexThreadTerminate;
		extern vector<bool> threadTerminate;

	//Table's variables
		extern vector<vector<float> > _cornersTHREE_D;
		extern vector<vector<float> > _cornersTWO_D;
		extern float BOUND;
	//GLUI variables
		extern	GLUI 			*glUserInterface;

	//Lighting
		extern GLfloat qaBlack[4]; //Black Color
		extern GLfloat qaGreen[4]; //Green Color
		extern GLfloat qaWhite[4]; //White Color
		extern GLfloat qaRed[4] ; //Red 	Color

	    // Set lighting intensity and color
		extern GLfloat qaAmbientLight[4]  ;
		extern GLfloat qaDiffuseLight[4] ;
		extern GLfloat qaSpecularLight[4] ;
		extern GLfloat emitLight[4]  ;
		extern GLfloat Noemit[4];
	    // Light source position
		extern GLfloat qaLightPosition[4]; //0.5 is arbitrary


	///Stuff for ball generation
	float MAX_RADIUS 				= 1.0;
	float MAX_VELOCITY 				= 0.05;
	float DELTA_T;

	///Camera related variables
	float X_CAM 						= 0.0;
	float Y_CAM 						= 0.0;
	float Z_CAM 						= 50.0;

	float X_CAM_FOCAL				= 0.0;
	float Y_CAM_FOCAL 				= 0.0;
	float Z_CAM_FOCAL 				= 0.0;
	float UP_X 						= 0.0;
	float UP_Y 						= 1.0;
	float UP_Z 						= 0.0;

	///R^3 space rendering variables
	float ROTATE_X 					= 0.0;
	float ROTATE_Y 					= 0.0;
	float ROTATE_Z 					= 0.0;
	float Z_DISPLACE 				= 0.0;


    int WIDTH;
	int HEIGHT;
	float NEAR_CLIPPING_DISTANCE 	= 1.0f;
	float FAR_CLIPPING_DISTANCE 		= 100.0f;
	float FOV_Y						= 45.0f;

	int selectedBall 				= 0;
	volatile int NUM_BALLS;

	float NEG_MIN_FLOAT 	= -10000.0f;
	///GUI Variables
	int Dimensional_state=3;
	///Ball's rendering parameters
		int KABIR_SLICES 	= 50;
		int KABIR_STACKS 	= 50;
		int H_SLICES			= 7;
		int H_STACKS			= 3;
		int HARMAN_SLICES	= 10;
		int HARMAN_STACKS	= 7; 
		int NUM_SLICES 		= KABIR_SLICES;
		int NUM_STACKS 		= KABIR_STACKS;
		int BLINK_TIME 		= 10;
	
	///Physics Variables
		float gravity 					= 0.0;
		float coefficientRestitution 	= 1.0;

	ScreenSaver* mainScreenSaver;
	extern Menu menu;




///Function that setps up glut's camera and rendering mode etc.
void ScreenSaver::init() {

	glEnable(GL_DEPTH_TEST); //Ensure that THREE_D figures are drawn in the correct order.
	glCullFace(GL_BACK); //Ensures that when a solid is drawn, the back figuyres arent draw. Thats a 2x improvmenet in performance.
	glEnable(GL_CULL_FACE);
	//R*R*R space to camera space setup.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f , //FOV in yz plane.
			(float)WIDTH/(float)HEIGHT , //ratio
			NEAR_CLIPPING_DISTANCE , //Near clipping distance
			FAR_CLIPPING_DISTANCE //Far clipping distance.
		);
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();

	///Set background to black.
	glClearColor( 0.0 , 0.0 , 0.0 , 0.0);
	///Call the lighting functions.
	this->initLighting();

	glFlush();
}

void ScreenSaver::initLighting() {

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

     // Set lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    
    // Set the light position
     glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition); 
}





///Function that starts the entire process.
void ScreenSaver::execute(int& argc , char** argv) {

	///Generating objects
	generateTable();
	generateBall();
	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50);
	windowID = glutCreateWindow(" Bouncy ball ");

	init();
	threadInit();
	initSkybox();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(handleMouse);
	glutKeyboardFunc(handleKeyboard);
	glutSpecialFunc(handleSpecial); 
	//GLUI *glUserInterface = GLUI_Master.create_glui_subwindow( windowID,GLUI_SUBWINDOW_RIGHT );
	menu.createMenu();	

	glutTimerFunc(DELTA_T , timer , 0);
	glutMainLoop();
	for(int i=0; i<NUM_BALLS;i++)
		pthread_exit(&vecBallThread[i]);
}

void ScreenSaver::exitter() {
	for(int i = 0; i<NUM_BALLS; i++) {
		pthread_mutex_lock(&vecMutexThreadTerminate[i]);
			threadTerminate[i] = true;
		pthread_mutex_unlock(&vecMutexThreadTerminate[i]);
	}
	
	glUserInterface->close();
	glutDestroyWindow(windowID);
	killSkybox();
}

///Function that initializes the table* (included in table.h)
void ScreenSaver::generateTable() {
	//#ifdef THREE_D
	vector<float> white	{ 1.0 , 1.0 , 1.0};
	if (Dimensional_state==3)
		table = new Table(_cornersTHREE_D , white);							//generates new ball
	else
		table = new Table(_cornersTWO_D , white);
	//#endif 

}

///Function that initializes n ball randomly.
void ScreenSaver::generateBall() {
	srand(time(NULL));
	//#ifdef THREE_D
	int numDim;
	if (Dimensional_state==3)
		numDim=3;
	else
		numDim=2;
	//#endif
	vector<pair<vector<float>,float> > positionRadius;		//stores all positions and radii
	for (int i=0;i<NUM_BALLS;i++)
	{
		bool created=false;									//checks if ball is created
		while(!created)
		{				
			vector<float> initPos;
			for (int j=0; j<numDim; j++) {
				float tempVar = rand()%101;
				tempVar /= 100;
				tempVar -= 0.5;
				tempVar *= 2.0*(BOUND - MAX_RADIUS);
				initPos.push_back(tempVar);	//generates random velocity
			}
			//#ifndef THREE_D
			if (Dimensional_state==2){


				float tempVar=2.0;
				initPos.push_back(tempVar);
			}
			//#endif	
			float newRadius = rand()%101;						//random radius	
				newRadius /= 100.0;
				newRadius *= MAX_RADIUS/2.0;
				newRadius += MAX_RADIUS/2.0;
				bool validPos=true;									
			for (int k=0; k<positionRadius.size(); k++)
			{
				if (pow((initPos[0]-positionRadius[k].first[0]),2) + pow((initPos[1]-positionRadius[k].first[1]),2) + pow((initPos[2]-positionRadius[k].first[2]),2)<= pow(newRadius + positionRadius[k].second,2))
					{
						validPos=false;																	//checks if position is valid
						break;
					}	
			}	
			if (validPos==true)
			{
				positionRadius.push_back(pair<vector<float>,float> ( initPos, newRadius ));				//updates vectors of position and radii
				created=true;
			}
		}		
	}
	for (int i=0; i<NUM_BALLS; i++)
	{
		vector<float> initVelocity;
		for (int j=0; j<numDim; j++) {
			float tempVar = rand()%101;
			tempVar /= 100.0;
			tempVar -= 0.5;
			tempVar *= 2.0;
			tempVar *= MAX_VELOCITY/2.0;
			tempVar += MAX_VELOCITY/2.0;
			initVelocity.push_back(tempVar);	//generates random velocity
		}
		//#ifndef THREE_D
		if (Dimensional_state==2) {
			float tempVar=0.0;
			initVelocity.push_back(tempVar);
		}
		//#endif
		vector<float> vectorColor;
		for (int j=0; j<3; j++)
		{
			float tempVariable = rand()%101;
			tempVariable /= 100.0;
			vectorColor.push_back(tempVariable);	//generates random Colour
		}
		#if defined(DEBUG) || defined(INIT_DEBUG)
			cout << "ball" << i << "made " << positionRadius[i].second << "\t" << initVelocity[0] <<"\t" << initVelocity[1] << "\t" << initVelocity[2] << "\n";
		#endif
		Ball* newBall= new Ball( positionRadius[i].first , initVelocity, positionRadius[i].second , vectorColor );	//creates new ball with parameters
		ball.push_back(newBall);																		//updates ball vector
	}	
}
#endif