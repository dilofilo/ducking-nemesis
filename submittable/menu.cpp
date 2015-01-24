#ifndef MENU_CPP
	#define MENU_CPP

//############################# THE VIRTUAL GHOST OF HAROUN SHALL GIVE YOU A TODO LIST.
// This requires comments..
void shapeHandler(int ID){
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
	//glutSetWindow(mainScreenSaver->getWindowID());
}

void dimensionHandler(int ID) {
	switch(obj2) {
		case 0 : {
			Dimensional_state=2;
			for (int i=0; i<NUM_BALLS; i++)
			{
				ball[i]->setzVelocity(0.0);
				ball[i]->setzCentre(0.0);
				ROTATE_X=0;
				ROTATE_Y=0;
				ROTATE_Z=0;
				for (int i=0;i<16;i++)
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
			break;
		}
	}
	//glutSetWindow(mainScreenSaver->getWindowID());
}

void closeWindow(int ID) {
	mainScreenSaver->exitter();

}

void gravInducer(int ID)
{
	gravGui=!gravGui;
}

void Pauser(int ID)
{
	mainScreenSaver->togglePaused();
}

void increaseVelocity(int ID) {
	if (selectedBall>=0)
		ball[selectedBall]->VelocityIncreaser();

}

void decreaseVelocity(int ID) {
	if (selectedBall>=0)
		ball[selectedBall]->VelocityDecreaser();
}

void selectionLeft(int ID) {
	if(selectedBall >= 0) {
		ball[selectedBall]->setIsSelected(false);
		selectedBall= (selectedBall-1 >= 0)?(selectedBall-1) : (NUM_BALLS-1);
		ball[selectedBall]->setIsSelected(true);
	}
}

void selectionRight(int ID) {
	if(selectedBall >= 0) {
		ball[selectedBall]->setIsSelected(false);
		selectedBall=(selectedBall+1)%(NUM_BALLS);
		ball[selectedBall]->setIsSelected(true);
	}
		
}

void enableFullscreen(int ID) {
	glutFullScreen();
	mainScreenSaver->toggleFullScreen(); //Sets it to true;
}

void rotateView(int ID) {
	//Do Nothing. - Function is handled by the GLU window's display function.
}

void resetRotation(int ID) {
	for (int i=0;i<16;i++) {
		rotation_matrix[i]=0.0;
	}
	rotation_matrix[0]=1.0;
	rotation_matrix[5]=1.0;
	rotation_matrix[10]=1.0;
	rotation_matrix[15]=1.0;
	rotatewala->reset();

}

void coefficientAcceptor(int ID) {
	coefficientRestitution=coEfficient;
}

void Menu::createMenu() {
	glUserInterface = GLUI_Master.create_glui("GLUT",0,5,5); 
	this->handleMenu(glUserInterface);	//Creating the menu
	//glUserInterface ->add_statictext("Choose Mode");
	//glUserInterface->add_separator();
	glUserInterface->set_main_gfx_window( mainScreenSaver->getWindowID() );//which window to send redisplay call to

}


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
	glUserInterface->add_button("Pause",5, (GLUI_Update_CB) Pauser);
	glUserInterface->add_button("Speed Up",5, (GLUI_Update_CB) increaseVelocity);
	glUserInterface->add_button("Speed Down",5, (GLUI_Update_CB) decreaseVelocity);
	glUserInterface->sync_live();
	//glUserInterface->add_checkbox("Kabira's Mode (the best)", &mode )
	glUserInterface->add_button("FullScreen",5, (GLUI_Update_CB) enableFullscreen);
	glUserInterface->add_button("<",5, (GLUI_Update_CB) selectionLeft);
	glUserInterface->add_column( false );
	glUserInterface->add_button(">",5, (GLUI_Update_CB) selectionRight);

	//  Rotation Matrix 
	 
	rotatewala=glUserInterface->add_rotation ("Rotation", rotation_matrix, 5, rotateView);
	glUserInterface->add_button("Reset Rotation",5, (GLUI_Update_CB) resetRotation);

	coefficientwala= glUserInterface->add_spinner("Coefficient", GLUI_SPINNER_FLOAT, &coEfficient, 5, (GLUI_Update_CB) coefficientAcceptor);
	coefficientwala->set_float_limits(0.0,1.0);


	GLUI_Panel *panel1_part2 = glUserInterface->add_panel ( "Exitter");
	glUserInterface->add_button_to_panel( panel1_part2, "Don't Kill Me!", 4, (GLUI_Update_CB) closeWindow);
	glUserInterface->sync_live();
}

#endif