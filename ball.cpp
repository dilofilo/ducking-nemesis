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
	// if ((w/oldWidth >= 1.0 ) && (h/oldHeight >= 1.0) ) {
	// 	radius *= ( (w/oldWidth) < (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	// }else {
	// 	radius *= ( (w/oldWidth) > (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	// }	
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

void Ball::handleWallCollision(Table* _table) {

}

void Ball::handleBallCollision(vector<float>& deltaPosition , vector<float>& targetVelocity , float targetMass) {
	//this->setVelocity()
}

#endif