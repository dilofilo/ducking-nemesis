#ifndef MENU_H
	#define MENU_H

#include "includes.h"
#include "screenSaver.h"

//This class, and functions in the file and corresponding live variables (declared in includes.h) control the GLUI components - buttons etc.
class Menu { //Class to handle creation of menu.
public:
	void createMenu();	
	void handleMenu(GLUI* glUserInterface);
};
	//Functions can't be inside a class because of GLUI specifications
	void shapeHandler(int ID);
	void dimensionHandler(int ID);
	void closeWindow(int ID);
	void gravInducer(int ID);
	void Pauser(int ID);
	void increaseVelocity(int ID); 
	void decreaseVelocity(int ID);
	void selectionLeft(int ID); 
	void selectionRight(int ID);
	void enableFullscreen(int ID); 
	void rotateView(int ID);

#endif

