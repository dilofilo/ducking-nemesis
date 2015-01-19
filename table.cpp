#ifndef TABLE_CPP
	#define TABLE_CPP
#include "table.h"

void Table::display() {
	glColor3f(color[0] , color[1] , color[2]);
	glBegin(GL_POLYGON);
		glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
		glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
		glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
		glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
	glEnd();
}

void Table::reshape(int w , int h , int oldWidth , int oldHeight) {
	// float xRatio = w/oldWidth;
	// float yRatio = h/oldHeight;

	// for(int i=0; i<4;i++) {
	// 	corners[i][0] *= xRatio;
	// 	corners[i][1] *= yRatio;
	// }
}
#endif