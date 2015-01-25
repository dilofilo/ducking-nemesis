#ifndef MENU_CPP
	#define MENU_CPP

#include "menu.h"
#include "screenSaver.h"
///GLUI static variables
	
	Menu menu;

	int obj						= 0;
	int obj2					= 1;
	int gravGui					= 0;
	int buttonmanager			= 1;
	int modeNO					= 0;
	float rotation_matrix[16] 	= { 1.0, 0.0, 0.0, 0.0,
                              		0.0, 1.0, 0.0, 0.0,
                              		0.0, 0.0, 1.0, 0.0,
                              		0.0, 0.0, 0.0, 1.0 };
    float coEfficient=1.0;

    GLUI_Rotation	*rotateVar;
    GLUI_Spinner  	*coefficientVar;

	GLUI_RadioGroup *radioGroup;
	GLUI_RadioGroup *radioGroup2;
	GLUI 			*glUserInterface;
	extern int Dimensional_state;
	extern int NUM_SLICES;
	extern int NUM_STACKS;
	extern int KABIR_SLICES;
	extern int KABIR_STACKS;
	extern int H_SLICES;
	extern int H_STACKS;
	extern int HARMAN_SLICES;
	extern int HARMAN_STACKS;
	extern float MAX_VELOCITY;
	extern int selectedBall;
	extern float coefficientRestitution;

	extern ScreenSaver* mainScreenSaver;
///Functions for handling menu buttons
void shapeHandler(int ID){							//For giving different shapes to the Balls
	switch(obj) {
		case 0 : { 
			NUM_SLICES=KABIR_SLICES;
			NUM_STACKS=KABIR_STACKS;
			#if defined(DEBUG) || defined(MENU_DEBUG)
				cout << "kabir\n";
			#endif
			break;

		}
		case 1 : {
			NUM_SLICES=H_SLICES;
			NUM_STACKS=H_STACKS;
			#if defined(DEBUG) || defined(MENU_DEBUG)
				cout<<"haroun\n";
			#endif
			break;

		}
		case 2 : {
			NUM_SLICES=HARMAN_SLICES;
			NUM_STACKS=HARMAN_STACKS;
			#if defined(DEBUG) || defined(MENU_DEBUG)
				cout<<"harman\n";
			#endif
			break;
		}
		
	}
	
}

void dimensionHandler(int ID) {						//For switching from 2D to 3D and vice-versa
	switch(obj2) {
		case 0 : {
			Dimensional_state=2;
			for (int i=0; i<NUM_BALLS; i++)
			{
				ball[i]->setzVelocity(0.0);
				ball[i]->setzCentre(0.0);
				ROTATE_X=0.0;
				ROTATE_Y=0.0;
				ROTATE_Z=0.0;
				rotateVar->reset();
				for (int i=0;i<16;i++)				//setting rotation matrix to the identity matrix
				{
					rotation_matrix[i]=0.0;
				}
				rotation_matrix[0]=1.0;
				rotation_matrix[5]=1.0;
				rotation_matrix[10]=1.0;
				rotation_matrix[15]=1.0;

			}
			break;
		}
		case 1 : {
			Dimensional_state=3;
			rotateVar->reset();
			ROTATE_X=0.0;
			ROTATE_Y=0.0;
			ROTATE_Z=0.0;
			for(int i=0; i<NUM_BALLS;i++) {
				float tempVar = rand()%101;
				tempVar /= 100.0;
				tempVar -= 0.5;
				tempVar *= 2.0;
				tempVar *= MAX_VELOCITY/2.0;
				tempVar += MAX_VELOCITY/2.0;
				ball[i]->setzVelocity(tempVar);
			}
			break;
		}
	}
}

void closeWindow(int ID) {							//To close the window
	mainScreenSaver->exitter();

}

void gravInducer(int ID)							//To toggle the grvity 
{
	gravGui=!gravGui;
}

void pauser(int ID)									//To Pause/Unpause the screensaver
{
	mainScreenSaver->togglePaused();
}

void increaseVelocity(int ID) {						//To increase the velocity
	if (selectedBall>=0)
		ball[selectedBall]->VelocityIncreaser();

}

void decreaseVelocity(int ID) {						//To decrease the velocity
	if (selectedBall>=0)
		ball[selectedBall]->VelocityDecreaser();
}

void selectionLeft(int ID) {						//To change the selected ball
	if(selectedBall >= 0) {
		ball[selectedBall]->setIsSelected(false);
		selectedBall= (selectedBall-1 >= 0)?(selectedBall-1) : (NUM_BALLS-1);
		ball[selectedBall]->setIsSelected(true);
	}
}

void selectionRight(int ID) {						//To change the selected Ball
	if(selectedBall >= 0) {
		ball[selectedBall]->setIsSelected(false);
		selectedBall=(selectedBall+1)%(NUM_BALLS);
		ball[selectedBall]->setIsSelected(true);
	}
		
}

void enableFullscreen(int ID) {						//To set fullscreen
	glutFullScreen();
	mainScreenSaver->toggleFullScreen(); 			//Sets it to true;
}

void rotateView(int ID) {
	//Do Nothing. - Function is handled by the GLU window's display function.
}

void resetRotation(int ID) {						//To reset the cube to its original position
	for (int i=0;i<16;i++) {
		rotation_matrix[i]=0.0;
	}
	rotation_matrix[0]=1.0;
	rotation_matrix[5]=1.0;
	rotation_matrix[10]=1.0;
	rotation_matrix[15]=1.0;
	ROTATE_X=0.0;
	ROTATE_Y=0.0;
	ROTATE_Z=0.0;

	rotateVar->reset();

}

void coefficientAcceptor(int ID) {					//To accept coefficient of restitution
	coefficientRestitution=coEfficient;
}

//Functions of the menu class
void Menu::createMenu() {
	glUserInterface = GLUI_Master.create_glui("GLUT",0,5,5); 
	this->handleMenu(glUserInterface);				//Creating the menu
	glUserInterface->set_main_gfx_window( mainScreenSaver->getWindowID() );//which window to send redisplay call to

}

//Function to add various kinds of buttons to the menu
void Menu::handleMenu(GLUI* glUserInterface)
{
	GLUI_Panel *panel1 = glUserInterface->add_panel( "Interact Smarter");
	radioGroup = glUserInterface->add_radiogroup_to_panel(panel1,&obj,3,shapeHandler);
	glUserInterface->add_radiobutton_to_group( radioGroup, "Kabira's mode (the best)" );
	glUserInterface->add_radiobutton_to_group( radioGroup, "Haroun's mode" );
	glUserInterface->add_radiobutton_to_group( radioGroup, "Harman's mode");

	GLUI_Panel *panel2 = glUserInterface->add_panel( "Mode");
	radioGroup2 = glUserInterface->add_radiogroup_to_panel(panel2,&obj2,3,dimensionHandler);
	glUserInterface->add_radiobutton_to_group( radioGroup2, "2D" );
	glUserInterface->add_radiobutton_to_group( radioGroup2, "3D (the best)" );

	glUserInterface->add_button("toggle gravity",5, (GLUI_Update_CB) gravInducer);
	glUserInterface->add_button("Pause",5, (GLUI_Update_CB) pauser);
	glUserInterface->add_button("Speed Up",5, (GLUI_Update_CB) increaseVelocity);
	glUserInterface->add_button("Speed Down",5, (GLUI_Update_CB) decreaseVelocity);
	glUserInterface->sync_live();
	glUserInterface->add_button("FullScreen",5, (GLUI_Update_CB) enableFullscreen);
	glUserInterface->add_button("<",5, (GLUI_Update_CB) selectionLeft);
	glUserInterface->add_column( false );
	glUserInterface->add_button(">",5, (GLUI_Update_CB) selectionRight);

	rotateVar=glUserInterface->add_rotation ("Rotation", rotation_matrix, 5, rotateView);
	glUserInterface->add_button("Reset Rotation",5, (GLUI_Update_CB) resetRotation);

	coefficientVar= glUserInterface->add_spinner("Coefficient", GLUI_SPINNER_FLOAT, &coEfficient, 5, (GLUI_Update_CB) coefficientAcceptor);
	coefficientVar->set_float_limits(0.0,1.0);


	GLUI_Panel *panel1_part2 = glUserInterface->add_panel ( "Exitter");
	glUserInterface->add_button_to_panel( panel1_part2, "Don't Kill Me!", 4, (GLUI_Update_CB) closeWindow);
	glUserInterface->sync_live();																						//For syncing variables between menu and code
}

#endif