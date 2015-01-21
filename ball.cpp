#ifndef BALL_CPP
	#define BALL_CPP


#define PI 3.14159265359
#define NUM_SLICES 50
#define NUM_STACKS 50
#define OFFSET 0.001
#include "ball.h"

#include <unistd.h>
#include "equationSolver.cpp"


void Ball::display() {
	glColor3f(color[0] , color[1] , color[2]);
	if( isSelected ) glColor3f(1.0,1.0,1.0);
	glPushMatrix();
		glTranslated( position[0] , position[1] , position[2] );
		if(isSelected) glutSolidSphere( radius , NUM_SLICES , NUM_STACKS);
		else glutWireSphere( radius , NUM_SLICES , NUM_STACKS);
	glPopMatrix();

}

void Ball::reshape(int w , int h , int oldWidth , int oldHeight ) {
	//Manipulate variables here
	// if ((w/oldWidth >= 1.0 ) && (h/oldHeight >= 1.0) ) {
	// 	radius *= ( (w/oldWidth) < (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	// }else {
	// 	radius *= ( (w/oldWidth) > (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	// }	
}

void Ball::displace(float dt) {
	this->setxCentre(this->getxCentre() + dt*this->getxVelocity());
	this->setyCentre(this->getyCentre() + dt*this->getyVelocity());
	this->setzCentre(this->getzCentre() + dt*this->getzVelocity());
}

void Ball::handleWallCollision(Table* _table) {
	if ((this->getxCentre() + DELTA_T*this->getxVelocity() + this->getRadius()) >=_table->getBottomRightFrontCorner()[0])
		this->setxVelocity(-1 * this->getxVelocity());										//checks for collision with right wall

	else if ((this->getxCentre() + DELTA_T*this->getxVelocity()) <= (this->getRadius()+_table->getBottomLeftFrontCorner()[0]))
		this->setxVelocity(-1 * this->getxVelocity());										//checks for collision with left wall

	else if ((this->getyCentre() + DELTA_T*this->getyVelocity() + this->getRadius()) >= _table->getTopRightFrontCorner()[1])
		this->setyVelocity(-1 * this->getyVelocity());										//checks for collision with top wall

	else if ((this->getyCentre() + DELTA_T*this->getyVelocity()) <= this->getRadius() + _table->getBottomRightFrontCorner()[1])
		this->setyVelocity(-1 * this->getyVelocity());										//checks for collision with bottom wall

	 else if ((this->getzCentre() + DELTA_T*this->getzVelocity() + this->getRadius()) >= _table->getTopRightFrontCorner()[2])
	 	this->setzVelocity(-1 * this->getzVelocity());										//checks for collision with front wall

	 else if ((this->getzCentre() + DELTA_T*this->getzVelocity() ) <= this->getRadius() + _table->getBottomRightBackCorner()[2])
		this->setzVelocity(-1 * this->getzVelocity());										//checks for collision with back wall
}


void Ball::handleBallCollision(vector<float> targetPosition , vector<float> targetVelocity , float targetMass , float targetRadius) {
	//this->setVelocity()
	
	vector<float> newPos = addVectors( this->getPosition() , ScalarMult(this->getVelocity() , DELTA_T));
	vector<float> deltaPos = addVectors(newPos , ScalarMult( targetPosition, -1.0));
	float distSquare = dotProduct(deltaPos , deltaPos);
	if (distSquare <= pow( this->getRadius() + targetRadius, 2) )
		this->setVelocity(solveBallCollision(this->getVelocity(), targetVelocity, newPos, targetPosition, this->getMass(), targetMass).first); /// checks and updates the balls velocity if it collides with some other ball
	
}

#endif