#ifndef SCREEN_SAVER_CPP
	#define SCREEN_SAVER_CPP

#include "screenSaver.h"
#include <limits>
#include <GL/glut.h>
#include <GL/glui.h>
using namespace std;

#define BOUNDING_RADIUS 10.0

///GLUI wali things
	int obj=0;
	int obj2=0;
	int gravGui=0;
	int buttonmanager=1;
	int modeNO=0;

	GLUI_RadioGroup *radioGroup;
	GLUI_RadioGroup *radioGroup2;
	GLUI *glUserInterface;


void initLighting(); /// Function to start up the lighting effects.

///Function that setps up glut's camera and rendering mode etc.
void ScreenSaver::init() {

	glEnable(GL_DEPTH_TEST); //Ensure that THREE_D figures are drawn in the correct order.
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
	glClearColor( 0.0 , 0.0 , 0.0 , 0.0);
	///Call the lighting functions.
	initLighting();
	//initSkybox();

	glFlush();
}

void ScreenSaver::exitter() {
	for(int i = 0; i<NUM_BALLS; i++) {
		pthread_mutex_lock(&vecMutexThreadTerminate[i]);
			threadTerminate[i] = true;
		pthread_mutex_unlock(&vecMutexThreadTerminate[i]);
		//delete ball[i];
		
	}
	//killSkybox();
	//delete table;
	//Handle ball, table etc?
	
	glUserInterface->close();

	glutDestroyWindow(windowID);
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

void modehandler(int ID){
	switch(obj) {
		case 0 : { 
			NUM_SLICES=50;
			NUM_STACKS=50;
			break;

		}
		case 1 : {
			NUM_SLICES=7;
			NUM_STACKS=3;
			cout<<"haroun\n";
			break;

		}
		case 2 : {
			NUM_SLICES=15;
			NUM_STACKS=15;
			cout<<"harman\n";
			break;
		}
		
	}
}

void modehandler2(int ID) {
	switch(obj2) {
		case 0 : {
			Dimensional_state=2;
			break;
		}
		case 1 : {
			Dimensional_state=3;
			break;
		}
	}
}

// void gravityactivator(int ID) {
// if (gravGui) 
// 	gravity = GRAVITY;
// else 
// 	gravity=0.0f;
// }

void Buttons(int ID) {
	mainScreenSaver->exitter();

}

void Grav(int ID)
{
	gravGui=!gravGui;
}

void Pauser(int ID)
{
	mainScreenSaver->togglePaused();
}

void VelocityIncreaser(int ID)
{
	cout<<"Increase the Speed of the selected ball. \n";
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
			if (Dimensional_state==3)
			{
				myzVel = myzVel*1.1;
				if(myzVel>MAX_VELOCITY) myzVel = MAX_VELOCITY;
			}
			else
			myzVel = 0.0f;
			

			ball[selectedBall]->setxVelocity(myxVel);
			ball[selectedBall]->setyVelocity(myyVel);
			ball[selectedBall]->setzVelocity(myzVel);

		}
}

void VelocityDecreaser(int ID)
{
	cout<<"Decrease the Speed of the selected ball. \n";
		/// Decrease the Speed of the selected ball.
		if(selectedBall >= 0) {
			// TODO Modify the velocity.
			float myxVel = ball[selectedBall]->getxVelocity();
			float myyVel = ball[selectedBall]->getyVelocity();
			float myzVel = ball[selectedBall]->getyVelocity();

			myxVel = myxVel*0.9;
			myyVel = myyVel*0.9;
		//	#ifdef THREE_D
			if (Dimensional_state==3)
				myzVel = myzVel*0.9;
			else
			myzVel = 0.0f;
			
			ball[selectedBall]->setxVelocity(myxVel);
			ball[selectedBall]->setyVelocity(myyVel);
			ball[selectedBall]->setzVelocity(myzVel);
		}
	}

///Function that starts the entire process.
void ScreenSaver::execute(int& argc , char** argv) {

	///Generating objects
	generateTable();
	generateBall();
	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH , HEIGHT);
	glutInitWindowPosition(50,50);
	windowID = glutCreateWindow(" Bouncy ball ");

	init();
	threadInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(handleMouse);
	glutKeyboardFunc(handleKeyboard);
	glutSpecialFunc(handleSpecial);

	GLUI *glUserInterface = GLUI_Master.create_glui_subwindow( windowID,GLUI_SUBWINDOW_RIGHT );
	


	//glUserInterface = GLUI_Master.create_glui("GLUT",0);
	//glUserInterface ->add_statictext("Choose Mode");
	//glUserInterface->add_separator();

	GLUI_Panel *mera_panel = glUserInterface->add_panel( "Interact Smarter");
		radioGroup = glUserInterface->add_radiogroup_to_panel(mera_panel,&obj,3,modehandler);
	glUserInterface->add_radiobutton_to_group( radioGroup, "Kabira's mode (the best)" );
	glUserInterface->add_radiobutton_to_group( radioGroup, "Haroun's mode" );
	glUserInterface->add_radiobutton_to_group( radioGroup, "Harman's mode");

	GLUI_Panel *tera_panel = glUserInterface->add_panel( "Mode");
		radioGroup2 = glUserInterface->add_radiogroup_to_panel(tera_panel,&obj2,3,modehandler2);
	glUserInterface->add_radiobutton_to_group( radioGroup2, "2D" );
	glUserInterface->add_radiobutton_to_group( radioGroup2, "3D (the best)" );

	glUserInterface->add_button("toggle gravity",5, (GLUI_Update_CB) Grav);
	glUserInterface->add_button("Pause",5, (GLUI_Update_CB) Pauser);
	glUserInterface->add_button("Increase Velocity",5, (GLUI_Update_CB) VelocityIncreaser);
	glUserInterface->add_button("Decrease Velocity",5, (GLUI_Update_CB) VelocityDecreaser);
	glUserInterface->sync_live();
	//glUserInterface->add_checkbox("Kabira's Mode (the best)", &mode )

	GLUI_Panel *merapanelpart2 = glUserInterface->add_panel ( "Exitter");
	glUserInterface->add_button_to_panel( merapanelpart2, "hi", 4, (GLUI_Update_CB) Buttons);
	glUserInterface->set_main_gfx_window( windowID );//which window to send redisplay call to

	glutTimerFunc(DELTA_T , timer , 0);
	glutMainLoop();
	for(int i=0; i<NUM_BALLS;i++)
		pthread_exit(&vecBallThread[i]);
}


void handleMouse(int button , int state , int x , int y) {

	/// 3= Scroll UP and 4 = Scroll DOWN
	if( button ==3) {		
		if (Z_CAM - Z_DISPLACE > 3.0*BOUND) Z_DISPLACE += 0.5;
		
	} else if (button == 4) {
		if (Z_CAM - Z_DISPLACE < 10.0*BOUND) Z_DISPLACE -= 0.5;
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

		//Maybe try to do m_start_z += Z_CAM?

		cout<< m_start_x<<"\t"<<m_start_y<<"\t"<<m_start_z<<"\n";
		cout<< m_end_x<<"\t"<<m_end_y<<"\t"<<m_end_z<<"\n";

		m_start_z += Z_CAM;
		m_end_z += Z_CAM;

		float maxZCentre = numeric_limits<float>::min(); // MIN_INT
		
		float myDenominator = pow((m_start_x - m_end_x),2) + pow((m_start_y - m_end_y),2) + pow((m_start_z - m_end_z),2);

			for(int counter=0;counter<NUM_BALLS;counter++)
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


				//Perpendicular distance = myNumerator/myDenominator.
					//Intersects if perDist <= radius^2.
					//Alternate used becase of floating point errors

				if(myNumerator <= pow(myRadius,2)*myDenominator) {
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

	if (Dimensional_state==3) {
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
	}
	if(key=='f' || key=='F') {
		if (mainScreenSaver->getIsFullScreen()) {
			//Reshape window
			glutReshapeWindow(640 , 480);
        	glutPositionWindow(50,50);
			mainScreenSaver->toggleFullScreen(); //Sets it to false
		}
		else {
			glutFullScreen();
			mainScreenSaver->toggleFullScreen(); //Sets it to true;
		}
	}
	else if(key=='i' || key=='I') {
		/// Request to add a ball.
		
		cout<<"Request to add a ball \n";
		if (mainScreenSaver-> getIsPaused()) {
			mainScreenSaver -> toggleIndicatorAddBall();
		}

	}
	else if(key=='r' || key=='R') {
		/// Request to delete a ball.
		cout<<"Request to delete a ball \n";
		if (mainScreenSaver->getIsPaused()) {
			mainScreenSaver-> toggleIndicatorDeleteBall();
		}
		
	}
	else if(int(key) == 27 ) {
		/// Esc pressed, Request to exit the Window. 
		mainScreenSaver->kill();
		mainScreenSaver->exitter();
		/// TODO cALL EXITTER().
	}
	else if(int(key) == 32) {
		/// Spacebar pressed, Request to pause.
		mainScreenSaver->togglePaused();
	}
	else if( key== 'g' || key == 'G' ) {
		gravGui = !gravGui;
	}
}

void handleSpecial(int key , int x , int y) {

	if(key == GLUT_KEY_RIGHT) {
		//table->randomizeColor();
		/// De-Select the current Ball and Select the next ball in the vector.
		if(selectedBall >= 0) {
			ball[selectedBall]->setIsSelected(false);
			selectedBall=(selectedBall+1)%(NUM_BALLS);
			ball[selectedBall]->setIsSelected(true);
		}
	}

	if(key == GLUT_KEY_LEFT) {
		/// De-Select the current Ball and Select the previous ball in the vactor.
		//table->randomizeColor();
		if(selectedBall >= 0) {
			ball[selectedBall]->setIsSelected(false);
			selectedBall= (selectedBall-1 >= 0)?(selectedBall-1) : (NUM_BALLS-1);
			ball[selectedBall]->setIsSelected(true);
		}
	}

	if(key == GLUT_KEY_UP) {

		/// Increse the Speed of the selected ball.
		
		cout<<"Increase the Speed of the selected ball. \n";
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
			//#ifdef THREE_D
			if (Dimensional_state==3)
			{
				myzVel = myzVel*1.1;
				if(myzVel>MAX_VELOCITY) myzVel = MAX_VELOCITY;	
			}
			else
			myzVel = 0.0f;
			//#endif

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
			//#ifdef THREE_D
			if (Dimensional_state==3)
				myzVel = myzVel*0.9;
			else
				myzVel = 0.0f;
			
			ball[selectedBall]->setxVelocity(myxVel);
			ball[selectedBall]->setyVelocity(myyVel);
			ball[selectedBall]->setzVelocity(myzVel);
		}
	}
}


void display() {
  	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	glLoadIdentity();
  	cout << "hi\n";
	glMatrixMode(GL_MODELVIEW); // Object space to R*R*R space 
	glLoadIdentity();
	glPushMatrix();
	gluLookAt( X_CAM , Y_CAM , Z_CAM , X_CAM_FOCAL , Y_CAM_FOCAL , Z_CAM_FOCAL , UP_X , UP_Y , UP_Z); // Focus camera at 0,0,0. ZCAMERA defined in main.cpp
	glPushMatrix();
  		glTranslated(0.0,0.0,Z_DISPLACE);
	  	glRotatef( ROTATE_X, 1.0, 0.0, 0.0);
  		glRotatef( ROTATE_Y, 0.0, 1.0, 0.0);
  		glRotatef(ROTATE_Z , 0.0, 0.0, 1.0);

  	///Render balls first because they are opaque
    
    glEnable(GL_LIGHTING);
	for(int i=0; i<NUM_BALLS; i++) ball[i]->display();
	glDisable(GL_LIGHTING);
	
	table->display();

	//displaySkybox();
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void timer(int value) {

	if (gravGui) {
		gravity=GRAVITY;
	}
	else{
		gravity=0.0f;
	}

	///Code for updating stuff.
	if(! (mainScreenSaver->getIsPaused()) && mainScreenSaver->isAlive()) {
		pthread_mutex_lock(&mutexStateVariableUpdate);
		for(int i = 0; i<NUM_BALLS;i++) {
				pthread_cond_signal(&vecCondBallUpdateBegin[i]);
		}
		while(numBallUpdates != 0 ) {
			pthread_cond_wait(&condBallUpdateComplete , &mutexStateVariableUpdate);
		}

		//Add and delete ball Code

		//Back to normal Code
		numBallUpdates = NUM_BALLS;
		for(int i = 0; i<NUM_BALLS;i++) {
			vecShouldBallUpdate[i] = true;
		}
		pthread_mutex_unlock(&mutexStateVariableUpdate);

		//End of locked section
	}
	else { //Only works when paused.
		if(mainScreenSaver->getIndicatorAddBall()) {
			mainScreenSaver->addBall(); 
		}
		if(mainScreenSaver->getIndicatorDeleteBall()) {
			mainScreenSaver->deleteBall();
		}

	}
	if( mainScreenSaver->isAlive()) { //Avoids poting redisplay after quit.
		glutTimerFunc(DELTA_T , timer , 0);
		glutPostRedisplay();
	}else {

	}
}


void reshape(int w , int h) {
	
	if(mainScreenSaver->isAlive()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int tx, ty, tw, th;
		GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
		glViewport( tx, ty, tw , th );


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		table->reshape(w , h, WIDTH , HEIGHT);
		for(int i=0; i< NUM_BALLS; i++) ball[i]->reshape(w , h, WIDTH , HEIGHT);

		WIDTH = w;
		HEIGHT = h;

		glFlush();
	}
}


///Function that initializes the table* (included in table.h)
void ScreenSaver::generateTable() {
	//#ifdef THREE_D
	if (Dimensional_state==3)
		table = new Table(_cornersTHREE_D);							//generates new ball
	else
		table = new Table(_cornersTWO_D);
	//#endif 

}

///Function that initializes n ball randomly.
void ScreenSaver::generateBall() {
	srand(time(NULL));
	//#ifdef THREE_D
	int numDim;
	if (Dimensional_state==3)
		numDim=3;
	else
		numDim=2;
	//#endif
	vector<pair<vector<float>,float> > positionRadius;		//stores all positions and radii
	for (int i=0;i<NUM_BALLS;i++)
	{
		bool created=false;									//checks if ball is created
		while(!created)
		{				
			vector<float> initPos;
			for (int j=0; j<numDim; j++) {
				float tempVar = rand()%101;
				tempVar /= 100;
				tempVar -= 0.5;
				tempVar *= 2.0*(BOUND - MAX_RADIUS);
				initPos.push_back(tempVar);	//generates random velocity
			}
			//#ifndef THREE_D
			if (Dimensional_state==3){


				float tempVar=2.0;
				initPos.push_back(tempVar);
			}
			//#endif	
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
		for (int j=0; j<numDim; j++) {
			float tempVar = rand()%101;
			tempVar /= 100.0;
			tempVar -= 0.5;
			tempVar *= 2.0;
			tempVar *= MAX_VELOCITY/2.0;
			tempVar += MAX_VELOCITY/2.0;
			initVelocity.push_back(tempVar);	//generates random velocity
		}
		//#ifndef THREE_D
		if (Dimensional_state==3) {
			float tempVar=0.0;
			initVelocity.push_back(tempVar);
		}
		//#endif
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

void ScreenSaver::addBall()
{
	///Generate the balls outisde the box and send them flying in

	//Ball Generation Code.
	vector<float> initPos(3);
		initPos[0] = 0.0;
		initPos[1] = 2.0*BOUND ;
		initPos[2] = 0.0;
		//ASSERT : position is ready
		//Radius Generation
	float newRadius = rand()%101;						//random radius	
		newRadius /= 100.0;
		newRadius *= MAX_RADIUS/2.0;
		newRadius += MAX_RADIUS/2.0; //Minimum radius
	//Velocity
	vector<float> initVelocity(3);
			initVelocity[1] = -1.0*MAX_VELOCITY/4.0;
			initVelocity[0]= 0.0;
			initVelocity[2] = 0.0;		
		vector<float> vectorColor;
			for (int j=0; j<3; j++)
			{
					float tempVariable = rand()%101;
					tempVariable /= 100.0;
					vectorColor.push_back(tempVariable);	//generates random Colour
			}

		Ball* newBall = new Ball(initPos , initVelocity , newRadius , vectorColor );
		ball.push_back(newBall);
		//Handle threads. And all the associated jazz.
		
			queue<BallDetailsMessage> newBox;
			mailBox.push_back(newBox); //Increase size by 1 . 

			pthread_mutex_t threadMutex;
			pthread_mutex_init(&threadMutex , NULL);
			vecMutexBallPthreads.push_back(threadMutex);
			
		

			vecShouldBallUpdate.push_back(false);

			pthread_cond_t newCondUpdateBegin;
			pthread_cond_init(&newCondUpdateBegin , NULL);
			vecCondBallUpdateBegin.push_back(newCondUpdateBegin);
			

			pthread_mutex_t newMailBoxMutex;
			pthread_mutex_init(&newMailBoxMutex , NULL);
			vecMutexMailBox.push_back(newMailBoxMutex);
			

			pthread_cond_t newMailBoxCond;
			pthread_cond_init(&newMailBoxCond , NULL);
			vecCondMailBoxReceived.push_back(newMailBoxCond);

			pthread_mutex_t tempMutex;
			pthread_mutex_init(&tempMutex , NULL);
			vecMutexThreadTerminate.push_back(tempMutex);
			
			
			threadTerminate.push_back(false);


			int newID = NUM_BALLS ; //Temporary.
			BallThreadParameters* args = new BallThreadParameters(newID);
			//Create only after all initializations have occured
		
			pthread_t newBallThread;
			int rc = pthread_create(&newBallThread , NULL , ballThread , (void*)args);
			vecBallThread.push_back(newBallThread);
			if(rc) cout<< "HOLY MOTHER OF GOD . FATALITY \n";			
			NUM_BALLS++;	
}

void ScreenSaver::deleteBall() {
	this->toggleIndicatorDeleteBall();
	NUM_BALLS--;
	//Remove the last ball.
}

#endif