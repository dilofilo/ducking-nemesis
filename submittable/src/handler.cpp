#ifndef HANDLER_CPP
	#define HANDLER_CPP

#include "screenSaver.h"
#include "table.h"
#include "menu.h"	
	extern float Z_CAM;
	extern float BOUND;
	extern int gravGui;
	extern int selectedBall;
	extern float NEG_MIN_FLOAT;
	extern int Dimensional_state;
	extern ScreenSaver* mainScreenSaver;


void handleMouse(int button , int state , int x , int y) {

	/// 3= Scroll UP and 4 = Scroll DOWN
	if( button ==3) {		
		if (Z_CAM - Z_DISPLACE > 3.0*BOUND) Z_DISPLACE += 0.5;
		
	} else if (button == 4) {
		if (Z_CAM - Z_DISPLACE < 10.0*BOUND) Z_DISPLACE -= 0.5;
	}

	else if((state==GLUT_DOWN) && (button == GLUT_RIGHT_BUTTON)) {
			ball[selectedBall]->setIsSelected(false);
			selectedBall = 0;
		}


	else if((state==GLUT_DOWN) && (button == GLUT_LEFT_BUTTON)) {

		/// Mouse Click Detected!	
		/// Check the Ball that was clicked and mark it as selected.
	

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
		//m_start_z += Z_CAM;
		//m_end_z += Z_CAM;

		#if defined(DEBUG) || defined(HANDLER_DEBUG)
			cout<<"The coordinates of the click are \t"<<x<<"\t"<<y<<endl;
			cout<< m_start_x<<"\t"<<m_start_y<<"\t"<<m_start_z<<"\n";
			cout<< m_end_x<<"\t"<<m_end_y<<"\t"<<m_end_z<<"\n";
		#endif

		float maxZCentre = NEG_MIN_FLOAT; // NEG_MIN_FLOAT is a very negative number.
		
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

	if( (key=='c') || (key =='C'))
	{
		#if defined(DEBUG) || defined(HANDLER_DEBUG)
			cout<<"Request to change color \n";
		#endif
		ball[selectedBall]->changeColor();
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

		/// Increase the Speed of the selected ball.
		
		if (selectedBall>=0)
			ball[selectedBall]->VelocityIncreaser();
	}

	if(key == GLUT_KEY_DOWN) {
		if (selectedBall>=0)
			ball[selectedBall]->VelocityDecreaser();
			
	}
}
#endif