#ifndef BALL_CPP
	#define BALL_CPP


#define PI 3.14159265359
#define NUM_SLICES 100
#define NUM_STACKS 100
#define OFFSET 0.001
#include "ball.h"
#include <ncurses.h>
#include <unistd.h>
#include "equationSolver.cpp"



//Variables for lighting and stuff.
	GLfloat qaBlack[] = {0.0, 0.0, 0.0, 1.0}; //Black Color
	GLfloat qaGreen[] = {0.0, 1.0, 0.0, 1.0}; //Green Color
	GLfloat qaWhite[] = {1.0, 1.0, 1.0, 1.0}; //White Color
	GLfloat qaRed[] = {1.0, 0.0, 0.0, 1.0}; //White Color

	    // Set lighting intensity and color
	GLfloat qaAmbientLight[]    = {0.2, 0.2, 0.2, 1.0};
	GLfloat qaDiffuseLight[]    = {0.8, 0.8, 0.8, 1.0};
	GLfloat qaSpecularLight[]    = {1.0, 1.0, 1.0, 1.0};
	GLfloat emitLight[] = {0.9, 0.9, 0.9, 0.01};
	GLfloat Noemit[] = {0.0, 0.0, 0.0, 1.0};
	    // Light source position
	GLfloat qaLightPosition[]    = {0.0, 0.0 , 0.0, 0.5}; 



void Ball::display() {
	
	//Set ball's materials
	if( isSelected ) {
	    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaWhite);
	 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhite);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
	} 
	else {
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, myColour);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myColour);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
	    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
	}

	glColor4f(color[0] , color[1] , color[2] , 1.0);

	glPushMatrix();
		glTranslated( position[0] , position[1] , position[2] );
		if(isSelected) glutSolidSphere( radius , NUM_SLICES , NUM_STACKS);
		else glutWireSphere( radius , NUM_SLICES , NUM_STACKS);
	glPopMatrix();

}

void Ball::reshape(int w , int h , int oldWidth , int oldHeight ) {

/*	Manipulate variables here
	if ((w/oldWidth >= 1.0 ) && (h/oldHeight >= 1.0) ) {
		radius *= ( (w/oldWidth) < (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	}else {
		radius *= ( (w/oldWidth) > (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	}*/	
}

void Ball::displace(float dt) {
	this->setxCentre(this->getxCentre() + dt*this->getxVelocity());
	this->setyCentre(this->getyCentre() + dt*this->getyVelocity());
	this->setzCentre(this->getzCentre() + dt*this->getzVelocity());
}

void Ball::handleWallCollision(Table* _table) {
	if ((this->getxCentre() + DELTA_T*this->getxVelocity() + this->getRadius()) >=_table->getBottomRightFrontCorner()[0]) {
		this->setxVelocity(-1 * this->getxVelocity());										//checks for collision with right wall
		}
	if ((this->getxCentre() + DELTA_T*this->getxVelocity()) <= (this->getRadius()+_table->getBottomLeftFrontCorner()[0])) {
		this->setxVelocity(-1 * this->getxVelocity());										//checks for collision with left wall
	}

	if ((this->getyCentre() + DELTA_T*this->getyVelocity() + this->getRadius()) >= _table->getTopRightFrontCorner()[1]) {
		this->setyVelocity(-1 * this->getyVelocity());										//checks for collision with top wall
	}
	if ((this->getyCentre() + DELTA_T*this->getyVelocity()) <= this->getRadius() + _table->getBottomRightFrontCorner()[1]) {
		this->setyVelocity(-1 * this->getyVelocity());										//checks for collision with bottom wall
	}
	#ifdef THREE_D
	if ((this->getzCentre() + DELTA_T*this->getzVelocity() + this->getRadius()) >= _table->getTopRightFrontCorner()[2]) {
	 	this->setzVelocity(-1 * this->getzVelocity());										//checks for collision with front wall
	 }
	if ((this->getzCentre() + DELTA_T*this->getzVelocity() ) <= this->getRadius() + _table->getBottomRightBackCorner()[2]) {
		this->setzVelocity(-1 * this->getzVelocity());										//checks for collision with back wall
	}
	#endif
}

#define preciseDeltaT (DELTA_T/20.0)

void Ball::pullApart(vector<float> targetPosition, vector<float> targetVelocity, float targetRadius)
{
	vector<float> tempVelocity=this->getVelocity();
	vector<float> tempPos=this->getPosition();
	//	targetPosition=addVectors(targetPosition,ScalarMult(targetVelocity,-1.0*DELTA_T));
	// vector<float> deltaPos = addVectors(tempPos , ScalarMult( targetPosition, -1.0));
	
	
	vector<float> deltaPos = addVectors( tempPos , ScalarMult(targetPosition , -1.0)); 
	float distSquare = dotProduct(deltaPos , deltaPos);
	float deltaPosMagnitude = sqrt( dotProduct( deltaPos , deltaPos) );
	deltaPos = ScalarMult( deltaPos, 1.0 / deltaPosMagnitude );

	while(distSquare <= pow( this->getRadius() + targetRadius, 2) ) {
		tempPos=addVectors(tempPos, ScalarMult(deltaPos,1.0*preciseDeltaT));
		targetPosition=addVectors(targetPosition, ScalarMult(deltaPos,-1.0*preciseDeltaT));
		deltaPos = addVectors(tempPos , ScalarMult( targetPosition, -1.0));
		distSquare = dotProduct(deltaPos , deltaPos);
	}
	this->setPosition(tempPos);
}



void Ball::handleBallCollision(vector<float> targetPosition , vector<float> targetVelocity , float targetMass , float targetRadius) {
	//this->setVelocity()
	vector<float> newPos = this->getPosition(); //addVectors( this->getPosition() , ScalarMult(this->getVelocity() , DELTA_T));
	vector<float> deltaPos = addVectors(newPos , ScalarMult( targetPosition, -1.0));
	float distSquare = dotProduct(deltaPos , deltaPos);
	if (distSquare <= pow( this->getRadius() + targetRadius, 2) ) {		
		this->setVelocity(solveBallCollision(this->getVelocity(), targetVelocity, newPos, targetPosition, this->getMass(), targetMass).first); /// checks and updates the balls velocity if it collides with some other ball
	}
	this->pullApart(targetPosition, targetVelocity, targetRadius);


}



#endif