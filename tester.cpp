#include <GL/glut.h>
#include <vector>

#include "table.h"
#include "table.cpp"

using namespace std;

static Ball* ball;
static Table* table;

static float WIDTH;
static float HEIGHT;

void init() {
	glEnable(GL_DEPTH_TEST); //Ensure that 3d figures are drawn in the correct order.
	glCullFace(GL_BACK); //Ensures that when a solid is drawn, the back figuyres arent draw. Thats a 2x improvmenet in performance.
	glEnable(GL_CULL_FACE);


	//R*R*R space to camera space setup.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0f , //FOV in yz plane.
			(float)WIDTH/(float)HEIGHT , //ratio
			0.1f , //Near clipping distance
			10000000.0f //Far clipping distance.
		)
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();

	///Set background to brown. TODO
	glCLearColor( 0.54 , 0.49 , 0.41 , 1.0);

}
int main(int argc, char** argv) {
	WIDTH = 600;
	HEIGHT = 600;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50);
	glutCreateWindow("testing");
	init();
	table = new Table( 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;

}