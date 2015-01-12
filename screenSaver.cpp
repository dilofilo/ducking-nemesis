#ifndef SCREEN_SAVER_CPP
	#define SCREEN_SAVER_CPP

#include <screenSaver.h>

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

void screenSaver::makeObjects(Table* table, vector<Ball*>& ballList , vector<pthread_t>& threads , int& numThreads) { //Makes Objects and threads.
	table = new Table(XLL,YLL , XLR,YLR , XTR,YTR , XTL,YTL);

}

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
	glSwapBuffers();
	//for all threads, add item to jobQueue of thread
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
			exitter();
		}
	}
}



///function to handle reshaping of windows
void screenSaver::reshape(int w, int h) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	table->reshape(w,h);
	for(int i=0; i<numThreads ; i++) {
		balls[i]->reshape(w,h);
	}
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFlush();
}




void screenSaver::execute() {

	makeObjects(table, balls);
	//Make glut window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWIndowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50); //50,50 are arbitrary coordinates.
	windowID = glutCreateWindow();
	//TODO : MENU WALI THINGS.
	init(  table, ballList , threads , numThreads);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyHandler);
	//Glut window is ready.
 	glutMainLoop();
 	return 0;

}
#endif