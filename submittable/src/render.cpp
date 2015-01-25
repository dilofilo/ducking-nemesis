#ifndef RENDER_CPP
	#define RENDER_CPP

#include "screenSaver.h"
#include "ballThreads.h"
#include "menu.h"

extern int gravGui;
extern float rotation_matrix[16];

extern	float X_CAM 						;
extern  float Y_CAM 						;
extern 	float Z_CAM 						;

extern pthread_mutex_t mutexStateVariableUpdate;
extern vector<pthread_cond_t> vecCondBallUpdateBegin;
extern int numBallUpdates;
extern pthread_cond_t condBallUpdateComplete;
extern vector<bool> vecShouldBallUpdate;
extern float FOV_Y;
extern float NEAR_CLIPPING_DISTANCE;
extern float FAR_CLIPPING_DISTANCE;
extern int Dimensional_state;
extern float gravity;

extern ScreenSaver* mainScreenSaver;
extern Menu menu;

void display() {
  	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	//glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();

	//glPushMatrix();
	gluLookAt( X_CAM , Y_CAM , Z_CAM , X_CAM_FOCAL , Y_CAM_FOCAL , Z_CAM_FOCAL , UP_X , UP_Y , UP_Z); // Focus camera at 0,0,0. ZCAMERA defined in main.cpp
	//glPushMatrix();
  	displaySkybox(); //Display it like an ominous background - starfield.

  		glTranslated(0.0,0.0,Z_DISPLACE);
  		if(Dimensional_state==3) {
  			glMultMatrixf(rotation_matrix);
  		}
	  	glRotatef( ROTATE_X, 1.0, 0.0, 0.0);
  		glRotatef( ROTATE_Y, 0.0, 1.0, 0.0);
  		glRotatef(ROTATE_Z , 0.0, 0.0, 1.0);
  	///Render balls first because they are opaque
    

    glEnable(GL_LIGHTING);
	for(int i=0; i<NUM_BALLS; i++) 
		ball[i]->display();
	glDisable(GL_LIGHTING);
	
	table->display();

	//displaySkybox();
	//glPopMatrix();
	//glPopMatrix();
	glutSwapBuffers();
}

void timer(int value) {
	//GLUI requires
		glutSetWindow(mainScreenSaver->getWindowID()); // Thank you, GLUI
		if (gravGui) {
			gravity=GRAVITY;
		}
		else{
			gravity=0.0f;
		}

	///Code for updating balls
	if(! (mainScreenSaver->getIsPaused()) && mainScreenSaver->isAlive()) {
		pthread_mutex_lock(&mutexStateVariableUpdate);
		//Command every thread to begin updating itself
		for(int i = 0; i<NUM_BALLS;i++) {
				pthread_cond_signal(&vecCondBallUpdateBegin[i]);
		}
		//Wait for every ball to finish updating
		while(numBallUpdates != 0 ) {
			pthread_cond_wait(&condBallUpdateComplete , &mutexStateVariableUpdate);
		}
		
		//Setup for next iteration
		numBallUpdates = NUM_BALLS;
		for(int i = 0; i<NUM_BALLS;i++) {
			vecShouldBallUpdate[i] = true;
		}
		pthread_mutex_unlock(&mutexStateVariableUpdate);
		//End of locked section
	}
	//Handling exit request.
	if( mainScreenSaver->isAlive()) { //Avoids poting redisplay after quit.
		glutTimerFunc(DELTA_T , timer , 0);
		glutPostRedisplay();
	}
	else {

	}
}


void reshape(int w , int h) {
	
	if(mainScreenSaver->isAlive()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Thank you, GLUI
		int tx, ty, tw, th;
		GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
		glViewport( tx, ty, tw , th );

		//Handling the reshaping of the window. - Alter the perspective, without changing the modelview matrix. 
		//	Hence, the objects are rendered correctly.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(FOV_Y, (GLfloat)w / (GLfloat)h, NEAR_CLIPPING_DISTANCE, FAR_CLIPPING_DISTANCE);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Calling reshape of table and that of ball because thats how it should be.
		table->reshape(w , h, WIDTH , HEIGHT);
		for(int i=0; i< NUM_BALLS; i++) ball[i]->reshape(w , h, WIDTH , HEIGHT);

		//Updating HEIGHT and WIDTH so that they may be used elsewhere if necesssary.
		WIDTH = w;
		HEIGHT = h;

		glFlush();
	}
}
#endif