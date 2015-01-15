#ifndef SCREEN_SAVER_CPP
	#define SCREEN_SAVER_CPP

#include <screenSaver.h>

///Function that declares all the threads and initializes them.
void screenSaver::makeObjects(Table* table, vector<Ball*>& ballList , vector<pthread_t>& threads , vector<bool>& threadUpdate , vector<pthread_mutex_t> vecMutex  , int& numThreads) { //Makes Objects and threads.
	table = new Table(XLL,YLL , XLR,YLR , XTR,YTR , XTL,YTL);
	srand(time(NULL));
	for(int i=0; i<numThreads;i++) {
		//TODO : newBall declaration and setting variables.
			float radius= (float)(rand() % (WIDTH/((float)(6*numThreads))));// radius is at max half of width of column
			float _xCentre= (float)(rand() % (WIDTH/numThreads)) + i*WIDTH/numThreads - (WIDTH/2.0); //the width of each column is width/numthreads  
			float _yCentre= (float)(rand() % (HEIGHT- (int)(2.0*radius))) + radius - (HEIGHT/2.0);
			
		Ball *newBall= new Ball(_xCentre,_yCentre,radius, 0.0, 0.0, 0.5, WIDTH , HEIGHT);//initializing ball with random properties //TODO
			float xVelo = (float)(rand()%(int)(newball->velocityLimit));
			float yVelo = (float)(rand()%(int)(newball->velocityLimit));
			newball->setxVelocity(xVelo);
			newBall->setyVelocity(yVelo);

		ballList[i]=newBall;
	}
	for(int i =0; i<numThreads; i++) {
		int rc = pthread_create(&threads[i],NULL, individualThread , (void*)(i) );
		threadUpdate[i] = false;
		if(rc) {
			cout << "\n\n\n\n\n Fatal Weird Error Happened. \n\n\n\n\n\n If This message is ever displayed, you're in deep trouble.";
		}
	}
	for (int i=0; i<numThreads; i++) {
		threadUpdate[i]=false;
	}
	for (int i=0; i<numThreads; i++){
		pthread_mutex_init(&vecMutex[i], NULL);
	}

	

}


/// function to initialize views, camera etc for glut.
void screenSaver::init() {
	
	glEnable(GL_DEPTH_TEST); //Ensure that 3d figures are drawn in the correct order.
	glCullFace(GL_BACK); //Ensures that when a solid is drawn, the back figuyres arent draw. Thats a 2x improvmenet in performance.
	glEnable(GL_CULL_FACE);


	//R*R*R space to camera space setup.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f , //FOV in yz plane.
			(float)WIDTH/(float)HEIGHT , //ratio
			0.1f , //Near clipping distance
			10000000.0f //Far clipping distance.
		)
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();

	///Set background to brown. TODO
	glCLearColor( 0.54 , 0.49 , 0.41 , 1.0);
}

///Function that is called if the user Escapes. handle all 
void screenSaver::exitter() {
	//TODO
}

///function to handle the actual display jobs.
void screenSaver::display() {
	//Clears the screen

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	gluLookAt( 0.0 , 0.0 , Z_CAMERA , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 ,0.0); // Focus camera at 0,0,0. Z_CAMERA defined in main.cpp
	
	glPushMatrix();

	//Call the display function for the table.
	table->display();

	//Calls every ball's display function.
	for(int i=0; i<numThreads; i++) {
		balls[i]->display();
	}

	glPopMatrix();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
	//for all threads, add item to jobQueue of thread
	for(int i = 0; i<numThreads ; i++) {
		//TODO : Insert locks.
		threadUpdate[i] = true;
	}
	glutPostRedisplay();
}

///function to handle the keys pressed by the user - including , escape, spacebar and F
void screenSaver::keyHandler(unsigned char key , int x , int y) {
	switch(key) { 
		case 32: { //SpaceBar handling
			if(isPaused) {
				isPaused = false;
				glutPostRedisplay();
			}
			else {
				isPaused = true;
			}
		}
		case 'F' : { //FullScreen handling
			if(!isFullScreen) {
				glutFullScreen();
				isFullScreen = true;
			}
			else {
				glutReshapeWindow(WIDTH,HEIGHT);
				glutPositionWindow(50,50);
				isFullScreen = false;
			}

		}
		case 27 : { //Escape handling.
			isExit = true;
			exitter();
		}
		case 'A': { //Add ball?

		}
		//TODO : Ball Selection keys.
	}
}



///function to handle reshaping of windows
void screenSaver::reshape(int w, int h) {
	WIDTH = w;
	HEIGHT = h;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	table->reshape(w,h);
	for(int i=0; i<numThreads ; i++) {
		balls[i]->reshape(w,h);
	}
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFlush();
}


///
void* individualThread(void* threadID) {
	int* _tID = (int*) threadID; //_tID is the pointer to the thread id.
	int tID = *_tID;
	while(true) {
		if(!isExit) {
			if(!isPaused) {

				//AcquireLock
				if(threadUpdate[tID]) {

					//Check for collision with boundary.
					
					//Check for collision with other balls.
					for(int ballID = tID + 1; ballID < numThreads; ballID++) {
						//Check if a collision occurs. if it does, solve for it and update the variables.
							//TODO
						//Acquire ball[bID] ka lock,

						//Release ball[bID] ka lock.
					}

				}
				//ReleaseLock
			}
			else {
				contiue;
			}
		} else {
			break;
		}
	}
}

void screenSaver::execute() {

	makeObjects(table, balls , threads , threadUpdate , vecMutex , numThreads);
	//Make glut window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWIndowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50); //50,50 are arbitrary coordinates.
	windowID = glutCreateWindow();
	//TODO : MENU WALI THINGS.
	init( );
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyHandler);
	//Glut window is ready.
 	glutMainLoop();
 	return 0;

}
#endif