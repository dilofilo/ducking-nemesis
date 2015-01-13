#ifndef BALL_CPP
	#define BALL_CPP

//ball.cpp
#include "ball.h"
#define SELECTION_RED 0.2
#define SELECTION_GREEN 0.4
#define SELECTION_BLUE 0.8
#define OFFSET 0.001
void Ball::display() {
	glMatrixMode(GL_MODELVIEW);
	glColor3f(color[0],color[1],color[2]);
	glPushMatrix();
		glTranslated(xCentre,yCentre,BALL_ZPLANE);
		glutSolidSphere(radius, NUMSLICES , NUMSTACKS);//TODO)
	glPopMatrix();

	if(isSelected) {
		glColor3f(SELECTION_RED,SELECTION_GREEN,SELECTION_BLUE);
		glBegin(GL_POLYGON);
			glVertex3f(xCentre +radius , yCentre +radius, BALL_ZPLANE + OFFSET );
			glVertex3f(xCentre -radius , yCentre +radius, BALL_ZPLANE + OFFSET );
			glVertex3f(xCentre -radius , yCentre -radius, BALL_ZPLANE + OFFSET );
			glVertex3f(xCentre +radius , yCentre -radius, BALL_ZPLANE + OFFSET);
		glEnd();
	}
	
}

void Ball::reshape(int w , int h) {
	//Manipulate variables here
	if ((w/oldWidth >= 1.0 ) && (h/oldHeight >= 1.0) ) {
		radius *= ( (w/oldWidth) < (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	}else {
		radius *= ( (w/oldWidth) > (h/oldHeight) ? (h/oldHeight) : (w/oldWidth) );
	}
	
	oldWidth = w;
	oldHeight = h;
}

#endif