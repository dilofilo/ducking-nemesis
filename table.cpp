#ifndef TABLE_CPP
	#define TABLE_CPP

#include <table.h>

///function to display the table.
void Table::display() {
	glMatrixMode(GL_MATRIXVIEW); //Now renders object space to 3d space
	glBegin(GL_QUADS);
		glColor3f()
	glEnd();
}


///function to handle reshaping the table.
void Table::reshape(int w , int h) {
	//Do Nothing
}
#endif