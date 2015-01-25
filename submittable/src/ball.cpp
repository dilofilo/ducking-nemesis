#ifndef BALL_CPP
	#define BALL_CPP

#include "ball.h"
#include "table.h"
#include "screenSaver.h"

	extern float BOUND;
	extern float DELTA_T;
	extern float MAX_VELOCITY;
	///Rendering Variables
	//Lighting
		GLfloat qaBlack[] 			= {0.0, 0.0, 0.0, 1.0}; //Black Color
		GLfloat qaGreen[] 			= {0.0, 1.0, 0.0, 1.0}; //Green Color
		GLfloat qaWhite[] 			= {1.0, 1.0, 1.0, 1.0}; //White Color
		GLfloat qaRed[] 			= {1.0, 0.0, 0.0, 1.0}; //Red 	Color

	    // Set lighting intensity and color
		GLfloat qaAmbientLight[]    = {0.2, 0.2, 0.2, 1.0};
		GLfloat qaDiffuseLight[]    = {0.8, 0.8, 0.8, 1.0};
		GLfloat qaSpecularLight[]   = {1.0, 1.0, 1.0, 1.0};
		GLfloat emitLight[]         = {0.9, 0.9, 0.9, 0.01};
		GLfloat Noemit[]            = {0.0, 0.0, 0.0, 1.0};
	    // Light source position
		GLfloat qaLightPosition[]   = { (GLfloat)2.0*BOUND, (GLfloat)2.0*BOUND, (GLfloat)2.0*BOUND, 0.5}; //0.5 is arbitrary

	extern int NUM_SLICES;
	extern int NUM_STACKS;
	extern int Dimensional_state;
	extern float gravity;
	extern float coefficientRestitution;
	extern int BLINK_TIME;
vector<Ball*> ball; 

void Ball::changeColor()
{
	for (int j=0; j<3; j++)
	{
		float tempVariable = rand()%101;
		tempVariable /= 100.0;
		myColour[j] = tempVariable; 	//generates random Colour
	        color[j] = tempVariable;
	}
}


void Ball::ballMaterial() {

	//Set ball's materials
	if( isSelected ) {
	    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaWhite);
	 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaWhite);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
	}
	else {
		if(timeSinceCollision == 0) {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, myColour);
		    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myColour);
		    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
	    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
		}
		//Collision Effect
		else if ( timeSinceCollision % 5 != 0) { // 5 is an arbitrary number.
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaBlack);
		    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaBlack);
		    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaBlack);
	    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);				
	    	timeSinceCollision -- ;
		}
		else {
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, myColour);
		    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, myColour);
		    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
	    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);				
	    	timeSinceCollision -- ;
		}


	}
}

void Ball::display() {
	
	ballMaterial();
	glColor4f(color[0] , color[1] , color[2] , 1.0);
	glPushMatrix();
		glTranslated( position[0] , position[1] , position[2] );
		if(isSelected) glutSolidSphere( radius , NUM_SLICES , NUM_STACKS);
		else glutWireSphere( radius , NUM_SLICES , NUM_STACKS);
	glPopMatrix();
}

void Ball::reshape(int w , int h , int oldWidth , int oldHeight ) {
	
}

void Ball::displace(float dt) {	//Updates Position of Ball - also, handles gravity.
	if( Dimensional_state == 2) {
		this->setzVelocity(0.0f);
		this->setzCentre(0.0f);
	}
	this->setxCentre(this->getxCentre() + dt*this->getxVelocity());					
	this->setyCentre(this->getyCentre() + dt*this->getyVelocity());
	this->setzCentre(this->getzCentre() + dt*this->getzVelocity());
	this->setyVelocity(this->getyVelocity() - DELTA_T*gravity);
}

void Ball::VelocityIncreaser()	{		//Handles Velocity Increase Requests
	float myxVel = this->getxVelocity();
	float myyVel = this->getyVelocity();
	float myzVel = this->getzVelocity();
	///Ensure that your balls dont speed
	myxVel = myxVel*1.1;
		if(myxVel>MAX_VELOCITY)  //Check for maximum velocity
			myxVel = MAX_VELOCITY;
	

	myyVel = myyVel*1.1;
		if(myyVel>MAX_VELOCITY) //Check for maximum velocity
			myyVel = MAX_VELOCITY;
	

	if (Dimensional_state==3)
	{
		myzVel = myzVel*1.1;
		if(myzVel>MAX_VELOCITY) myzVel = MAX_VELOCITY;
	}
	else {
		myzVel = 0.0f; //0 velocity on 2d plane.
	}

	this->setxVelocity(myxVel);
	this->setyVelocity(myyVel);
	this->setzVelocity(myzVel);
}

void Ball::VelocityDecreaser()	{		//Handles Velocity Decrease Requests
	float myxVel = this->getxVelocity();
	float myyVel = this->getyVelocity();
	float myzVel = this->getzVelocity();

	myxVel = myxVel*0.9;
	myyVel = myyVel*0.9;

	if (Dimensional_state==3)
		myzVel = myzVel*0.9;
	else
		myzVel = 0.0f;
	
	this->setxVelocity(myxVel);
	this->setyVelocity(myyVel);
	this->setzVelocity(myzVel);

}

void Ball::handleWallCollision(Table* _table) {
	if ((this->getxCentre() + DELTA_T*this->getxVelocity() + this->getRadius()) >=_table->getBottomRightFrontCorner()[0]) {
		if(this->getxVelocity()>=0)
			this->setxVelocity(-1.0* coefficientRestitution * this->getxVelocity());										//checks for collision with right wall

		}
	if ((this->getxCentre() + DELTA_T*this->getxVelocity()  ) <= (this->getRadius()+_table->getBottomLeftFrontCorner()[0])) {
		if(this->getxVelocity()<=0)
			this->setxVelocity(-1.0* coefficientRestitution * this->getxVelocity());										//checks for collision with left wall
	}

	if ((this->getyCentre() + DELTA_T*this->getyVelocity()  + this->getRadius()) >= _table->getTopRightFrontCorner()[1]) {
		if(this->getyVelocity()>=0)
			this->setyVelocity(-1.0* coefficientRestitution * this->getyVelocity());										//checks for collision with top wall
	}
	if ((this->getyCentre() + DELTA_T*this->getyVelocity()  ) <= this->getRadius() + _table->getBottomRightFrontCorner()[1]) {
		if(this->getyVelocity()<=0)
			this->setyVelocity(-1.0* coefficientRestitution * this->getyVelocity());										//checks for collision with bottom wall
	}
	if (Dimensional_state==3)
	{
		if ((this->getzCentre() + DELTA_T*this->getzVelocity()  + this->getRadius()) >= _table->getTopRightFrontCorner()[2]) {
	 		if(this->getzVelocity()>=0)
	 			this->setzVelocity(-1.0* coefficientRestitution * this->getzVelocity());										//checks for collision with front wall
	 	}
		if ((this->getzCentre() + DELTA_T*this->getzVelocity()  ) <= this->getRadius() + _table->getBottomRightBackCorner()[2]) {
			if(this->getzVelocity()<=0)
				this->setzVelocity(-1.0* coefficientRestitution * this->getzVelocity());										//checks for collision with back wall
		}
	}
}

void Ball::handleBallCollision(vector<float> targetPosition , vector<float> targetVelocity , float targetMass , float targetRadius) {			//Resolves Ball Collisions
	//this->setVelocity()
	vector<float> newPos  	= addVectors(this->getPosition() , ScalarMult(this->getVelocity() , DELTA_T)); 					// Position in next iteration
	vector<float> deltaPos 	= addVectors(newPos , ScalarMult(targetPosition , -1.0)); 										//R1 - R2
	float speedAlongNormal 	= dotProduct(deltaPos , addVectors(targetVelocity , ScalarMult(this->getVelocity() , -1.0))); 	// (V1-V2).N
	float distSquare 		= dotProduct(deltaPos , deltaPos);									
	
	if( (distSquare <= pow( this->getRadius() + targetRadius , 2)) &&( speedAlongNormal >= 0.0) ) {
		this->setVelocity(solveBallCollision(this->getVelocity(), targetVelocity, newPos, targetPosition, this->getMass(), targetMass , coefficientRestitution).first); /// checks and updates the balls velocity if it collides with some other ball
		this-> setTimeSinceCollision(BLINK_TIME); //Display changes according to timeSinceCollision
	}

	#if defined(DEBUG) || defined(BALL_DEBUG)
		float x 			= this->getMass();
		float y 			= this->getMass() * pow(this->getVelocity(),2) * 0.5;
		string temp_output	= "Mass =" + to_string(x) + " Energy= " + to_string(y);
		cout<<temp_output<<"\n";
	#endif
}
#endif