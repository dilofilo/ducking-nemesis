#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>
#include <unistd.h>
using namespace std;
#define Z_CAMERA 10.0
#define NUMSLICES 50
#define NUMSTACKS 50
#define BALL_ZPLANE 0.0
#define REDUCTIONFACTOR 0.000001
#define deltaT 1.0
#include "equationSolver.cpp"
#include "table.h"
#include "table.cpp"
#include "ball.h"
#include "ball.cpp"

Table * table ;
vector<Ball*> balls;
vector<pthread_t> threads;
vector<bool> shouldThreadUpdate;

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
			1.0f , //Near clipping distance
			10000000.0f //Far clipping distance.
		);
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();

	///Set background to black. TODO
	glClearColor( 0.0 , 0.0 , 0.0 , 1.0);
	//glutFullScreen();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	glPushMatrix();
	gluLookAt( 0.0 , 0.0 , Z_CAMERA , 0.0 , 0.0 , 0.0 , 0.0 , 1.0 ,0.0); // Focus camera at 0,0,0. ZCAMERA defined in main.cpp
	glPushMatrix();

	table->display();
	for(int i=0; i<balls.size();i++) {
		balls[i]->display();
	}

	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w , int h) {
	WIDTH = w;
	HEIGHT = h;
	table->reshape(w,h);
	for(int i=0; i<balls.size();i++) { balls[i]->reshape(w,h); } //reshape for balls.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100000.0f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glFlush();

}

void timerFunc(int val) {
	
	if(false) {
		for(int i = 0; i<balls.size(); i++) {
			Ball* ball = balls[i];
			float xNew = ball->getxCentre() + REDUCTIONFACTOR*deltaT*(ball->getxVelocity());
			float yNew = ball->getyCentre() + REDUCTIONFACTOR*deltaT*(ball->getyVelocity());

			if ( (xNew+(ball->getRadius())>(table->getxlr())) || (xNew-(ball->getRadius()) < (table->getxll())) ) {
				ball->setxVelocity(-1*ball->getxVelocity());
			}


			if ( (yNew -(ball->getRadius()) < (table->getylr())) || (yNew+(ball->getRadius()) > (table->getytl())) ) {
				ball->setyVelocity(-1*ball->getyVelocity());
			}

			xNew =  ball->getxCentre() + deltaT*(ball->getxVelocity());
			yNew = ball->getyCentre() + deltaT*(ball->getyVelocity());
			//Collision with walls checked.

			//To check collision with other balls.
			for(int j=i+1; j<balls.size();j++) {
				if( ball->willBallCollide(balls[j])) {
					float* newVelocities = solveBallCollision( ball->getxVelocity(),
															ball->getyVelocity(),
															ball->getMass(),
															balls[j]->getxVelocity(),
															balls[j]->getyVelocity(),
															balls[j]->getMass(),
															ball->getxCentre() - balls[j]->getxCentre(),
															ball->getyCentre() - balls[j]->getyCentre() );
					ball->setxVelocity(newVelocities[0]);
					ball->setyVelocity(newVelocities[1]);
					balls[j]->setxVelocity(newVelocities[2]);
					balls[j]->setyVelocity(newVelocities[3]);

				}
			}

		ball->setxCentre( xNew );
		ball->setyCentre( yNew );
		}
	} else {
		for(int i=0; i< balls.size() ; i++) {
		shouldThreadUpdate[i] = true;  //Needs Mutexing.
		while( !shouldThreadUpdate[i]) { continue; }
		}
	}

	glutTimerFunc( deltaT , timerFunc , val);
	glutPostRedisplay();

}

void* threadFunction(void* _tid) {
	int tID = *( (int*) _tid);
	while(true) {
		if( shouldThreadUpdate[tID] ) {
			balls[tID]->setxCentre( balls[tID]->getxCentre() + deltaT*(balls[tID]->getxVelocity()) ) ;
			balls[tID]->setyCentre( balls[tID]->getyCentre() + deltaT*(balls[tID]->getyVelocity()) ) ;
			shouldThreadUpdate[tID] = false;
		}
	}

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
	
	Ball* ball0 = new Ball( 1.1 , 0.0 , 0.3 , 0.6 , 0.0 , 0.0 , WIDTH , HEIGHT);
		ball0->setxVelocity(-0.2);
		ball0->setyVelocity(0.1);
	Ball* ball1 = new Ball( -1.1 , 0.0 , 0.3 , 0.0 , 0.0 , 0.6 , WIDTH , HEIGHT);
		ball1->setxVelocity(+0.01);
		ball1->setyVelocity(-0.02);
	balls.push_back(ball0);
	balls.push_back(ball1);
	
	threads.resize(balls.size());
	shouldThreadUpdate.resize(balls.size() , false);

	for(int i=0; i < balls.size(); i++) {
		int* iptr = &i;
		int rc = pthread_create( &threads[i] , NULL , threadFunction , (void*)(iptr) );
		if(rc) { cout << "HOLY MOTHER OF GOD ERROR"; }
	}
	table= new Table(-1.5, -1.5, 1.5, -1.5, 1.5, 1.5, -1.5, 1.5, 0.0 , 0.0 , 0.70, 0.20 , WIDTH , HEIGHT); //TODO FIGURE OUT CORRECT PROPORTIONS
	//mytable->print();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1 , timerFunc , 1); //1000 is an arbitrary constant value
	glutMainLoop();

	return 0;

}