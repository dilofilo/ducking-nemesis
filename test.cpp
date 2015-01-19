#include <GL/glut.h>
#include <pthread.h>
#include <iostream>
#include <vector>
#include <math.h>


//GL stuff
#define Z_CAMERA 7.0
#define DELTA_T 5.0
static int WIDTH = 640;
static int HEIGHT = 480;
#define NUM_BALLS 3

using namespace std;

#include "equationSolver.cpp"
#include "ballThreads.cpp"
#include "table.h"
#include "table.cpp"
#include "ball.h"
#include "ball.cpp"
Table* table;


void init() {
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


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();
	glPushMatrix();
	gluLookAt( 0.0 , 0.0 , Z_CAMERA , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 ,0.0); // Focus camera at 0,0,0. ZCAMERA defined in main.cpp
	glPushMatrix();
	table->display();
	for(int i=0; i<NUM_BALLS; i++) ball[i]->display();
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void timer(int val) {
	//Calculations
	pthread_mutex_lock(&mutexStateVariableUpdate);
		for(int i = 0; i<NUM_BALLS;i++) {
			pthread_cond_signal(&vecCondBallUpdateBegin[i]);
		}
		while(numBallUpdates != 0 ) {
			pthread_cond_wait(&condBallUpdateComplete , &mutexStateVariableUpdate);
		}
		numBallUpdates = NUM_BALLS;
		for(int i = 0; i<NUM_BALLS;i++) {
			vecShouldBallUpdate[i] = true;
		}
	pthread_mutex_unlock(&mutexStateVariableUpdate);
	//End of locked section
	glutTimerFunc(DELTA_T , timer , 1);
	glutPostRedisplay();
	cout << "Redisplay posted\n";
}

void reshape(int w, int h) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w/ (GLfloat)h, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	table->reshape(w , h, WIDTH , HEIGHT);
	for(int i=0; i< NUM_BALLS; i++) ball[i]->reshape(w , h, WIDTH , HEIGHT);

	WIDTH = w;
	HEIGHT = h;

	glFlush();
}



// static int numBallUpdates;
// 	vector<pthread_mutex_t> vecMutexBallPthreads;
// 	vec<pthread_cond_t> vecCondBallUpdateBegin;
// 	vec<pthread_cond_t> vecCondBallUpdateComplete;
// 	pthread_mutex_t mutexStateVariableUpdate;
// 	vector<bool> vecShouldBallUpdate;
// pthread_cond_t condBallUpdateComplete
// 	vector<pthread_t> vecBallThread;

int main(int argc, char** argv) {
	
	vector<float> color{0.54 , 0.25 , 0.07};
	vector< vector<float> > tableCorners;
		vector<float> BL{ -5.0 , -4.0 , 0.0 };
		vector<float> BR{ 5.0 , -4.0 , 0.0 };
		vector<float> TR{ 5.0 , 4.0 , 0.0 };
		vector<float> TL{ -5.0 , 4.0 , 0.0 };
		tableCorners.push_back(BL);
		tableCorners.push_back(BR);
		tableCorners.push_back(TR);
		tableCorners.push_back(TL);
	table = new Table( tableCorners , color );
	ball.resize(NUM_BALLS);


	color[0] = 1.0 ; color[1] = 0.2; color[2] = 0.3;
	for(int i=0; i< NUM_BALLS; i++) {
		ball[i] = new Ball();
		ball[i]->setxCentre(-1.0 + (float)i);
		ball[i]->setColor(color);
	}
	ball[0]->setxVelocity(0.1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50);
	glutCreateWindow("testing");
	init();
	threadInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(DELTA_T , timer , 1); 

	glutMainLoop();
	return 0;
}