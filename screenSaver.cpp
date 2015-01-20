#ifndef SCREEN_SAVER_CPP
	#define SCREEN_SAVER_CPP

///Function that setps up glut's camera and rendering mode etc.
void ScreenSaver::init() {
	glEnable(GL_DEPTH_TEST); //Ensure that 3d figures are drawn in the correct order.
	glCullFace(GL_BACK); //Ensures that when a solid is drawn, the back figuyres arent draw. Thats a 2x improvmenet in performance.
	glEnable(GL_CULL_FACE);
	//R*R*R space to camera space setup.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f , //FOV in yz plane.
			(float)WIDTH/(float)HEIGHT , //ratio
			1.0f , //Near clipping distance
			10000000.0f //Far clipping distance.
		);
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();
	///Set background to black.
	glClearColor( 0.0 , 0.0 , 0.0 , 1.0);
	glFlush();
}

///Function that initializes the table* (included in table.h)

///Function that initializes n balls randomly.

///Function that starts the entire process.
void ScreenSaver::execute(int& argc , char** argv) {

}

#endif