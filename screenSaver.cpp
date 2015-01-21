#ifndef SCREEN_SAVER_CPP
	#define SCREEN_SAVER_CPP

#include "screenSaver.h"
#include <limits>
using namespace std;

#define BOUNDING_RADIUS 10.0

void initLighting(); /// Function to start up the lighting effects.

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
			10000.0f //Far clipping distance.
		);
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();
	///Set background to black.
	glClearColor( 0.0 , 0.0 , 0.0 , 1.0);
	///Call the lighting functions.
	initLighting();
	glFlush();
}

void ScreenSaver::exitter() {
	cout << "BYE BYE BABY HOW DO YOU DO?\n";
}

void initLighting() {

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

     // Set lighting intensity and color
    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
    
    // Set the light position
     glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition); 
}


///Function that starts the entire process.
void ScreenSaver::execute(int& argc , char** argv) {

	///Generating objects
	generateTable();
	generateBall();
	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
	glutInitWindowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50);
	glutCreateWindow(" Bouncy ball ");

	init();
	threadInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(handleMouse);
	glutKeyboardFunc(handleKeyboard);
	glutSpecialFunc(handleSpecial);

	glutTimerFunc(DELTA_T , timer , 0);
	glutMainLoop();
}


void handleMouse(int button , int state , int x , int y) {

	
	if( button ==3 || button == 4 ) {
		/// 3= Scroll UP and 4 = Scroll DOWN
		///If Z_CAM is greater or lesser than certain thresholds, it won't scroll.
		
	}
	else if((state==GLUT_DOWN) && (button == GLUT_LEFT_BUTTON)) {

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

		float maxZCentre = numeric_limits<float>::min(); // MIN_INT
		
		float myDenominator = pow((m_start_x - m_end_x),2) + pow((m_start_y - m_end_y),2) + pow((m_start_z - m_end_z),2);

			for(int counter=0;counter<ball.size();counter++)
			{
				///Cross product magic.
				/// Check whether this was the ball clicked
				float myRadius = ball[counter]->getRadius() + BOUNDING_RADIUS;
				float myxCentre = ball[counter]->getxCentre();
				float myyCentre = ball[counter]->getyCentre();
				float myzCentre = ball[counter]->getzCentre();
				
				bool checkIntersecting = false;

				float diff1_x = m_end_x - m_start_x;
				float diff1_y = m_end_y - m_start_y;
				float diff1_z = m_end_z - m_start_z;

				float diff2_x = -(myxCentre - m_start_x);
				float diff2_y = -(myyCentre - m_start_y);
				float diff2_z = -(myzCentre - m_start_z);

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
						ball[selectedBall]->setIsSelected(false);
					}

					ball[counter]->setIsSelected(true);
					selectedBall=counter;
					maxZCentre = myzCentre;
				
				}
			}		

		
	}

}

void handleKeyboard(unsigned char key, int x, int y) {

	if(key=='w' || key=='W') {
		ROTATE_X += 0.5;
	}	
	else if(key=='s' || key=='S') {
		ROTATE_X -= 0.5;
	}	
	else if(key=='d' || key=='D') {
		ROTATE_Y += 0.5;
	}	
	else if(key=='a' || key=='A') {
		ROTATE_Y -= 0.5;
	}	
	else if(key=='e' || key=='E')  {
		ROTATE_Z += 0.5;
	}	
	else if(key=='q' || key=='Q')  {
		ROTATE_Z -= 0.5;
	}
	else if(key=='f' || key=='F') {
		if (mainScreenSaver->isFullScreen) {
			//Reshape window
			glutReshapeWindow(WIDTH/2.0, HEIGHT/2.0);
        	glutPositionWindow(50,50);
			mainScreenSaver->isFullScreen = false;
		}
		else {
			glutFullScreen();
			mainScreenSaver->isFullScreen = true;
		}
	}
	else if(key=='i' || key=='I') {
		/// Request to add a ball.
		cout<<"Request to add a ball \n";
		
		/// TODO
	}
	else if(key=='r' || key=='R') {
		/// Request to delete a ball.
		cout<<"Request to delete a ball \n";

		/// TODO
	}
	else if(int(key) == 27 ) {
		/// Esc pressed, Request to exit the Window. 
		cout<<"Request to exit the Window \n";

		/// TODO cALL EXITTER().
	}
	else if(int(key) == 32) {
		/// Spacebar pressed, Request to pause.
		mainScreenSaver->togglePaused();
	}
}

void handleSpecial(int key , int x , int y) {

	if(key == GLUT_KEY_RIGHT) {
		//table->randomizeColor();
		/// De-Select the current Ball and Select the next ball in the vector.
		if(selectedBall >= 0) {
			ball[selectedBall]->setIsSelected(false);
			selectedBall=(selectedBall+1)%(ball.size());
			ball[selectedBall]->setIsSelected(true);
		}
	}

	if(key == GLUT_KEY_LEFT) {
		/// De-Select the current Ball and Select the previous ball in the vactor.
		//table->randomizeColor();
		if(selectedBall >= 0) {
			ball[selectedBall]->setIsSelected(false);
			selectedBall= (selectedBall-1 >= 0)?(selectedBall-1) : (ball.size()-1);
			ball[selectedBall]->setIsSelected(true);
		}
	}

	if(key == GLUT_KEY_UP) {

		/// Increse the Speed of the selected ball.
		
		cout<<"Increse the Speed of the selected ball. \n";
		if(selectedBall >= 0) {
			// TODO Modify the velocity.

			float myxVel = ball[selectedBall]->getxVelocity();
			float myyVel = ball[selectedBall]->getyVelocity();
			float myzVel = ball[selectedBall]->getzVelocity();

			///Ensure that your balls dont speed
			myxVel = myxVel*1.1;
				if(myxVel>MAX_VELOCITY) myxVel = MAX_VELOCITY;
			myyVel = myyVel*1.1;
				if(myyVel>MAX_VELOCITY) myyVel = MAX_VELOCITY;
			myzVel = myzVel*1.1;
				if(myzVel>MAX_VELOCITY) myzVel = MAX_VELOCITY;


			ball[selectedBall]->setxVelocity(myxVel);
			ball[selectedBall]->setyVelocity(myyVel);
			ball[selectedBall]->setzVelocity(myzVel);

		}
	}

	if(key == GLUT_KEY_DOWN) {

		cout<<"Decrease the Speed of the selected ball. \n";
		/// Decrease the Speed of the selected ball.
		if(selectedBall >= 0) {
			// TODO Modify the velocity.
			float myxVel = ball[selectedBall]->getxVelocity();
			float myyVel = ball[selectedBall]->getyVelocity();
			float myzVel = ball[selectedBall]->getyVelocity();

			myxVel = myxVel*0.9;
			myyVel = myyVel*0.9;
			myzVel = myzVel*0.9;
			ball[selectedBall]->setxVelocity(myxVel);
			ball[selectedBall]->setyVelocity(myyVel);
			ball[selectedBall]->setzVelocity(myzVel);
		}
	}
}


void display() {
  	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	glLoadIdentity();
  	


	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();
	glPushMatrix();
	gluLookAt( X_CAM , Y_CAM , Z_CAM , X_CAM_FOCAL , Y_CAM_FOCAL , Z_CAM_FOCAL , UP_X , UP_Y , UP_Z); // Focus camera at 0,0,0. ZCAMERA defined in main.cpp
	glPushMatrix();
	  	glRotatef( ROTATE_X, 1.0, 0.0, 0.0);
  		glRotatef( ROTATE_Y, 0.0, 1.0, 0.0);
  		glRotatef(ROTATE_Z , 0.0, 0.0, 1.0);

	table->display();
	for(int i=0; i<NUM_BALLS; i++) ball[i]->display();
	
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void timer(int value) {
	if(! (mainScreenSaver->isPaused) ) {
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
	}
	glutTimerFunc(DELTA_T , timer , 0);
	glutPostRedisplay();
}


void reshape(int w , int h) {
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


///Function that initializes the table* (included in table.h)
	///Default values for bounding box.
	vector<vector<float> > _corners{{-BOUND,-BOUND,BOUND},{BOUND,-BOUND,BOUND},{BOUND,BOUND,BOUND},{-BOUND,BOUND,BOUND},{-BOUND,-BOUND,-BOUND},{BOUND,-BOUND,-BOUND},{BOUND,BOUND,-BOUND},{-BOUND,BOUND,-BOUND}};		//generates box  
void ScreenSaver::generateTable() {
	table = new Table(_corners);							//generates new ball
}

///Function that initializes n ball randomly.
void ScreenSaver::generateBall() {
	srand(time(NULL));
	
	vector<pair<vector<float>,float> > positionRadius;		//stores all positions and radii
	for (int i=0;i<NUM_BALLS;i++)
	{
		bool created=false;									//checks if ball is created
		while(!created)
		{				
			vector<float> initPos;							
			for (int j=0; j<3; j++) {
				float tempVar = rand()%101;
				tempVar /= 100;
				tempVar -= 0.5;
				tempVar *= 2.0*(BOUND - MAX_RADIUS);
				initPos.push_back(tempVar);	//generates random velocity
			}
		
			float newRadius = rand()%101;						//random radius	
			newRadius /= 100.0;
			newRadius *= MAX_RADIUS/2.0;
			newRadius += MAX_RADIUS/2.0;
			
			bool validPos=true;									
			for (int k=0; k<positionRadius.size(); k++)
			{
				if (pow((initPos[0]-positionRadius[k].first[0]),2) + pow((initPos[1]-positionRadius[k].first[1]),2) + pow((initPos[2]-positionRadius[k].first[2]),2)<= pow(newRadius + positionRadius[k].second,2))
					{
						validPos=false;																	//checks if position is valid
						break;
					}																		
			}	
			if (validPos==true)
			{
				positionRadius.push_back(pair<vector<float>,float> ( initPos, newRadius ));				//updates vectors of position and radii
				created=true;
			}
		}
		
	} 
	for (int i=0; i<NUM_BALLS; i++)
	{
		vector<float> initVelocity;
		for (int j=0; j<3; j++) {
			float tempVar = rand()%101;
			tempVar /= 100.0;
			tempVar -= 0.5;
			tempVar *= 2.0;
			tempVar *= MAX_VELOCITY/2.0;
			tempVar += MAX_VELOCITY/2.0;
			initVelocity.push_back(tempVar);	//generates random velocity
		}

		vector<float> vectorColor;
		for (int j=0; j<3; j++)
		{
			float tempVariable = rand()%101;
			tempVariable /= 100.0;
			vectorColor.push_back(tempVariable);	//generates random Colour
		}


		cout << "ball" << i << "made " << positionRadius[i].second << "\t" << initVelocity[0] <<"\t" << initVelocity[1] << "\t" << initVelocity[2] << "\n";									
		Ball* newBall= new Ball( positionRadius[i].first , initVelocity, positionRadius[i].second , vectorColor );	//creates new ball with parameters
		ball.push_back(newBall);																		//updates ball vector
	}	
}
#endif