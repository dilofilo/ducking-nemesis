#ifndef TABLE_CPP
	#define TABLE_CPP
#include "table.h"

void Table::randomizeColor()
{
	srand(time(NULL));

		for (int j=0; j<3; j++)
		{
			float tempVariable = rand()%101;
			tempVariable /= 100.0;
			this->color[j] = tempVariable;	//generates random Colour
			myColour[j] = color[j];
		}
} 

void Table::display() {
	
	//Fix lighting issues
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT , myColour );
 	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE , myColour );
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, myColour );
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);

	glColor4f(color[0] , color[1] , color[2] );
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
	
	
	// glColor4f(0.203,0.596 ,0.858 , 0.5);
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