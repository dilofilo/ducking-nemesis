#ifndef TABLE_CPP
	#define TABLE_CPP
#include <GL/glut.h>

#include "table.h"

///function to display the table.
void Table::display() {
	//cout << color[0];
	glColor3f(color[0] , color[1], color[2]);
	glBegin(GL_POLYGON);
		glVertex3f(xll , yll , z);
		glVertex3f(xlr , ylr , z);
		glVertex3f(xtr , ytr , z);
		glVertex3f(xtl , ytl , z);
	glEnd();
}

void Table::print() {
	cout<<"Hello";

	cout<<xll<<yll<<endl;

}

///function to handle reshaping the table.
void Table::reshape(int w , int h) {
	
}
#endif