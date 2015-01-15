#ifndef BALL_CPP
	#define BALL_CPP


#define PI 3.14159265359
#define NUM_SLICES 50
#define NUM_STACKS 50

#include "ball.h"
#include <stdint.h>


void Ball::display() {
	glColor3f(color[0] , color[1] , color[2]);
	glPushMatrix();
		glTranslated( position[0] , position[1] , position[2] );
		glutSolidSphere( radius , NUM_SLICES , NUM_STACKS);
	glPopMatrix();

	if(isSelected) {
		glColor3f(color[2] , color[1] , color[0]);
		glBegin(GL_POLYGON);
			//Draw square around the ball.
			glVertex3f(position[0] + radius, position[1] + radius, position[2] );
			glVertex3f(position[0] - radius, position[1] + radius, position[2] );
			glVertex3f(position[0] - radius, position[1] - radius, position[2] );
			glVertex3f(position[0] - radius, position[1] + radius, position[2] );
		glEnd();
	}
}

void Ball::reshape(int w , int h , int oldWidth , int oldHeight ) {
	//Manipulate variables here
	if ((w/oldWidth >= 1.0 ) && (h/oldHeight >= 1.0) ) {
		radius *= ( (w/oldWidth) < (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	}else {
		radius *= ( (w/oldWidth) > (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	}	
}

///This struct can be used to pass more data if ever required.
struct BallThreadParameters {
	int ID;
	BallThreadParameters(int x) : ID(x) {}
};

void* ballThread(void* args) {
	BallThreadParameters* arg = (BallThreadParameters*)args ;
	int ID = arg->ID;
	//TODO
	while(true) {
		pthread_mutex_lock(&vecMutexBallPthreads[ID]);
		while(numBallUpdates == 0)
			pthread_cond_wait(&condBallUpdateBegin , &vecMutexBallPthreads[ID]);
		while( (numBallUpdates > 0) && ( shouldBallUpdate[ID] ) ) {
			pthread_mutex_lock(&mutexBallShouldUpdate);
			numBallUpdates--;
			shouldBallUpdate[ID] = false;
			pthread_mutex_unlock(&mutexBallShouldUpdate);
			ball[ID]->setxCentre( ball[ID]->getxCentre() + DELTA_T*ball[ID]->getxVelocity());
			ball[ID]->setyCentre( ball[ID]->getyCentre() + DELTA_T*ball[ID]->getyVelocity());
			ball[ID]->setzCentre( ball[ID]->getzCentre() + DELTA_T*ball[ID]->getzVelocity());
		}
		pthread_cond_signal(&condBallUpdateComplete);
		pthread_mutex_lock(&vecMutexBallPthreads[ID]);
	}
}

#endif