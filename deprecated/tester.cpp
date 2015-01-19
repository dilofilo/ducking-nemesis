#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <limits>
using namespace std;
#define Z_CAMERA 10.0
#define NUMSLICES 50
#define NUMSTACKS 50
#define BALL_ZPLANE 0.0
#define REDUCTIONFACTOR 0.000001
#define deltaT 1.0
#define DT 0.001
#include "equationSolver.cpp"
#include "table.h"
#include "table.cpp"
#include "ball.h"
#include "ball.cpp"

Table * table ;
vector<Ball*> balls;
vector<pthread_t> threads;
vector<bool> shouldThreadUpdate;
int nUpdatesToBeDone;
static float WIDTH;
static float HEIGHT;
static int selectedBall=-1;

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


void mouseClickHandler (int button , int state , int x , int y) {

/*	if(state==GLUT_DOWN) {

		/// Mouse Click Detected!	
		/// Check the Ball that was clicked and mark it as selected.


		cout<<"The coordinates of the click are \t"<<x<<"\t"<<y<<endl;

		double matModelView[16], matProjection[16]; 
		int viewport[4]; 
		glGetDoublev( GL_MODELVIEW_MATRIX, matModelView ); 
		glGetDoublev( GL_PROJECTION_MATRIX, matProjection ); 
		glGetIntegerv( GL_VIEWPORT, viewport );
		double winX = (double)x; 
		double m_start_x, m_start_y, m_start_z, m_end_x, m_end_y, m_end_z;
		double winY = viewport[3] - (double)y; 
		gluUnProject(winX, winY, 0.0, matModelView, matProjection, viewport, &m_start_x, &m_start_y, &m_start_z); 
		gluUnProject(winX, winY, 1.0, matModelView, matProjection, viewport, &m_end_x, &m_end_y, &m_end_z); 

		cout<< m_start_x<<"\t"<<m_start_y<<"\t"<<m_start_z<<"\n";
		cout<< m_end_x<<"\t"<<m_end_y<<"\t"<<m_end_z<<"\n";

		float maxZCentre = numeric_limits<int>::min();
		
		float myDenominator = pow((m_start_x - m_end_x),2) + pow((m_start_y - m_end_y),2) + pow((m_start_z - m_end_z),2);

			for(int counter=0;counter<balls.size();counter++)
			{
				
				/// Check whether this was the ball clicked

				float myRadius = balls[counter]->getRadius();
				float myxCentre = balls[counter]->getxCentre();
				float myyCentre = balls[counter]->getyCentre();
				float myzCentre = balls[counter]->getzCentre();
				
				bool checkIntersecting = false;

				float diff1_x = myxCentre - m_start_x;
				float diff1_y = myyCentre - m_start_y;
				float diff1_z = myzCentre - m_start_z;

				float diff2_x = myxCentre - m_end_x;
				float diff2_y = myyCentre - m_end_y;
				float diff2_z = myzCentre - m_end_z;

				float matX = diff1_y*diff2_z - diff2_y*diff1_z;
				float matY = diff1_x*diff2_z - diff1_z*diff2_x;
				float matZ = diff1_x*diff2_y - diff1_y*diff2_x; 


				float myNumerator = pow(matX,2) + pow(matY,2) + pow(matZ,2);


				float perpDist = myNumerator/myDenominator;

				if(perpDist <= pow(myRadius,2)) {
					checkIntersecting = true;
				}


				if( (checkIntersecting) && (myzCentre > maxZCentre ))  {
	
					/// This is the ball! Mark it as selected.
					if(selectedBall >= 0) {
						balls[selectedBall]->setIsSelected(false);
					}

					balls[counter]->setIsSelected(true);
					selectedBall=counter;
					maxZCentre = myzCentre;
				
				}
			}		

		
	}
*/
}

void keyboardHandler(unsigned char key, int x, int y) {

	if(key=='a' || key=='A') {
		/// Request to add a ball.
		cout<<"Request to add a ball \n";
		
		/// TODO
	}

	if(key=='d' || key=='D') {
		/// Request to delete a ball.
		cout<<"Request to delete a ball \n";

		/// TODO
	}

	if(int(key) == 27 ) {
		/// Esc pressed, Request to exit the Window. 
		cout<<"Request to exit the Window \n";

		/// TODO cALL EXITTER().
	}

	if(int(key) == 32) {
		/// Spacebar pressed, Request to pause.
		cout<<"Request to pause \n";
	
		/// TODO SET IS PAUSED TO TRUE/FALSE.
	}
}

void specialKeyHandler(int key , int x , int y) {

	/**
	* 37 = Left Arrow Key.
	* 38 = Up Arrow Key.
	* 39 = Right Arrow Key.
	* 40 = Down Arrow Key.
	*/
	
	if(key == GLUT_KEY_RIGHT) {
		/// De-Select the current Ball and Select the next ball in the vector.
		if(selectedBall >= 0) {
			balls[selectedBall]->setIsSelected(false);
			selectedBall=(selectedBall+1)%(balls.size());
			balls[selectedBall]->setIsSelected(true);
		}
	}

	if(key == GLUT_KEY_LEFT) {
		/// De-Select the current Ball and Select the previous ball in the vactor.
		if(selectedBall >= 0) {
			balls[selectedBall]->setIsSelected(false);
			selectedBall= (selectedBall-1>0)?(selectedBall-1) : (balls.size()-1);
			balls[selectedBall]->setIsSelected(true);
		}
	}

	if(key == GLUT_KEY_UP) {

		/// Increse the Speed of the selected ball.
		
		cout<<"Increse the Speed of the selected ball. \n";
		if(selectedBall >= 0) {
			// TODO Modify the velocity.

			float myxVel = balls[selectedBall]->getxVelocity();
			float myyVel = balls[selectedBall]->getyVelocity();

			myxVel = myxVel*1.1;
			myyVel = myyVel*1.1;

			balls[selectedBall]->setxVelocity(myxVel);
			balls[selectedBall]->setyVelocity(myyVel);
		}
	}

	if(key == GLUT_KEY_DOWN) {

		cout<<"Increse the Speed of the selected ball. \n";
		/// Decrease the Speed of the selected ball.
		if(selectedBall >= 0) {
			// TODO Modify the velocity.

			float myxVel = balls[selectedBall]->getxVelocity();
			float myyVel = balls[selectedBall]->getyVelocity();

			myxVel = myxVel*0.9;
			myyVel = myyVel*0.9;

			balls[selectedBall]->setxVelocity(myxVel);
			balls[selectedBall]->setyVelocity(myyVel);
		}
	}
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
	
	for(int i = 0; i<balls.size(); i++) {
		Ball* ball = balls[i];
		float xNew = ball->getxCentre() + deltaT*(ball->getxVelocity());
		float yNew = ball->getyCentre() + deltaT*(ball->getyVelocity());

		if ( (xNew+(ball->getRadius())>(table->getxlr())) || (xNew-(ball->getRadius()) < (table->getxll())) ) {
			ball->setxVelocity(-1*ball->getxVelocity());
		}


		if ( (yNew -(ball->getRadius()) < (table->getylr())) || (yNew+(ball->getRadius()) > (table->getytl())) ) {
			ball->setyVelocity(-1*ball->getyVelocity());
		}

		xNew =  ball->getxCentre() + deltaT*(ball->getxVelocity());
		yNew = ball->getyCentre() + deltaT*(ball->getyVelocity());
		ball->setxCentre( xNew );
		ball->setyCentre( yNew );

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

				do { //
					if ( ( ball->getxVelocity()*balls[j]->getxVelocity() ) < 0 || ( ball->getyVelocity()*balls[j]->getyVelocity() ) < 0 ) {
						ball->setxCentre( ball->getxCentre() - DT*ball->getxVelocity());
						ball->setyCentre( ball->getyCentre() - DT*ball->getyVelocity()); 
					}else {
						ball->setxCentre( ball->getxCentre() + DT*ball->getxVelocity());
						ball->setyCentre( ball->getyCentre() + DT*ball->getyVelocity()); 
					}
				}while(ball->willBallCollide(balls[j]));

			}
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
		ball0->setxVelocity(-0.02);
		ball0->setyVelocity(0.001);
	Ball* ball1 = new Ball( -1.1 , 0.0 , 0.3 , 0.0 , 0.0 , 0.6 , WIDTH , HEIGHT);
		ball1->setxVelocity(+0.01);
		ball1->setyVelocity(-0.02);
	Ball* ball2 = new Ball( 0.0 , 1.0 , 0.3 , 0.0 , 0.0 , 0.6 , WIDTH , HEIGHT);
		ball1->setxVelocity(+0.01);
		ball1->setyVelocity(-0.02);

	ball0 -> setIsSelected(true);
	selectedBall = 0;

	balls.push_back(ball0);
	balls.push_back(ball1);
	balls.push_back(ball2);
	
	threads.resize(balls.size());
	shouldThreadUpdate.resize(balls.size() , false);

	// for(int i=0; i < balls.size(); i++) {
	// 	int* iptr = &i;
	// 	int rc = pthread_create( &threads[i] , NULL , threadFunction , (void*)(iptr) );
	// 	if(rc) { cout << "HOLY MOTHER OF GOD ERROR"; }
	// }
	table= new Table(-1.5, -1.5, 1.5, -1.5, 1.5, 1.5, -1.5, 1.5, 0.0 , 0.0 , 0.70, 0.20 , WIDTH , HEIGHT); //TODO FIGURE OUT CORRECT PROPORTIONS
	//mytable->print();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1 , timerFunc , 1); //1000 is an arbitrary constant value
	//void glutMouseFunc(void (*func)(int button, int state, int x, int y))
	glutMouseFunc(mouseClickHandler);
	glutKeyboardFunc(keyboardHandler);
	glutSpecialFunc(specialKeyHandler);
	glutMainLoop();

	return 0;

}