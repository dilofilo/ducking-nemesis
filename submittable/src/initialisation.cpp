#ifndef INITIALISATION_CPP
	#define INITIALISATION_CPP

#include "screenSaver.h"

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
	if (Dimensional_state==3)
		table = new Table(_cornersTHREE_D);							//generates new ball
	else
		table = new Table(_cornersTWO_D);
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