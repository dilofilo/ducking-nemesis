#ifndef TABLE_CPP
	#define TABLE_CPP
#include "table.h"

void Table::display() {
	glColor3f(color[0] , color[1] , color[2]);
	
	///Generate line-like things
	
	//Edges
		glBegin(GL_LINES);
			glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
			glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
			glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
			glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
			glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
			glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
			glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
			glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
			glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
			glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
			glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
			glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
			glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
		glEnd();
	//End of edges

	//Face Wali Crosses	
		glBegin(GL_LINES);
			glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
			glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
			glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
			glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
			glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
			glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
			glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
			glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
			glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
			glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
			glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
			glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
			glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
		glEnd();
	/// Dilapidated code for hollow cube
	// glBegin(GL_POLYGON);
	// 	glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
	// 	glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
	// 	glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
	// 	glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
	// glEnd();
	// glBegin(GL_POLYGON);
	// 	glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
	// 	glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
	// 	glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
	// 	glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
	// glEnd();
	// glBegin(GL_POLYGON);
	// 	glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
	// 	glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
	// 	glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
	// 	glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
	// glEnd();
	// glBegin(GL_POLYGON);
	// 	glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
	// 	glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
	// 	glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
	// 	glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
	// glEnd();
	// glBegin(GL_POLYGON);
	// 	glVertex3f( corners[3][0] , corners[3][1] , corners[3][2]);
	// 	glVertex3f( corners[2][0] , corners[2][1] , corners[2][2]);
	// 	glVertex3f( corners[6][0] , corners[6][1] , corners[6][2]);
	// 	glVertex3f( corners[7][0] , corners[7][1] , corners[7][2]);
	// glEnd();
	// glBegin(GL_POLYGON);
	// 	glVertex3f( corners[4][0] , corners[4][1] , corners[4][2]);
	// 	glVertex3f( corners[5][0] , corners[5][1] , corners[5][2]);
	// 	glVertex3f( corners[1][0] , corners[1][1] , corners[1][2]);
	// 	glVertex3f( corners[0][0] , corners[0][1] , corners[0][2]);
	// glEnd();
		
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