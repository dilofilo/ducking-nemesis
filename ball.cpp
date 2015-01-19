#ifndef BALL_CPP
	#define BALL_CPP


#define PI 3.14159265359
#define NUM_SLICES 50
#define NUM_STACKS 50

#include "ball.h"
#include <unistd.h>
#include "equationSolver.cpp"

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
	BallThreadParameters(int x) { ID = x;}
};

void Ball::displace(float dt) {
	this->setxCentre(this->getxCentre() + dt*this->getxVelocity());
	this->setyCentre(this->getyCentre() + dt*this->getyVelocity());
	this->setzCentre(this->getzCentre() + dt*this->getzVelocity());
}

vector<float> Ball::nextPos(float dt) {
	return addVector( position , ScalarMult( velocity , dt));
}

void handleWallCollision(Table* _table) {
	
	if ((this->getxCentre + this->getRadius())>=_table->getBottomRightCorner()[0]))
		this->setxVelocity(-1 * this->getxVelocity());
	else if (this->getxCentre <= (_table->getBottomLeftCorner()[0]+this->getRadius()))
		this->setxVelocity(-1 * this->getxVelocity());
	else if ((this->getyCentre+this->getRadius())>=_table->getTopRightCorner()[1])
		this->setyVelocity(-1 * this->getyVelocity());
	else if ((this->getyCentre<=this->getRadius()+_table->getBottomRightCorner))
}


// static int numBallUpdates;
// 	vector<pthread_mutex_t> vecMutexBallPthreads;
// 	vec<pthread_cond_t> vecCondBallUpdateBegin;
// 	vec<pthread_cond_t> vecCondBallUpdateComplete;
// 	pthread_mutex_t mutexStateVariableUpdate;
// 	vector<bool> vecShouldBallUpdate;
// pthread_cond_t condBallUpdateComplete
// 	vector<pthread_t> vecBallThread;

void* ballThread(void* args) {
	BallThreadParameters* arg = (BallThreadParameters*)args ;
	int ID = arg->ID;
	//TODO
	while(true) {
		vector<float> newPos;
		pthread_mutex_lock(&vecMutexBallPthreads[ID]);
		while(numBallUpdates == 0)
			pthread_cond_wait(&vecCondBallUpdateBegin[ID] , &vecMutexBallPthreads[ID]);
		while( (numBallUpdates > 0) && ( vecShouldBallUpdate[ID] ) ) {
			pthread_mutex_lock(&mutexStateVariableUpdate);
			numBallUpdates--;
			vecShouldBallUpdate[ID] = false;
			pthread_mutex_unlock(&mutexStateVariableUpdate);
			newPos = nextPos(DELTA_T);
			ball[ID]->setPosition(newPos);
		}
		pthread_cond_signal(&condBallUpdateComplete);
		pthread_mutex_unlock(&vecMutexBallPthreads[ID]);
	}
}

#endif