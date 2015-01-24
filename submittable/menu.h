#ifndef MENU_H
	#define MENU_H
using namespace std;
#include <GL/glut.h>
#include <GL/glui.h>

///GLUI wali things
	int obj=0;
	int obj2=0;
	int gravGui=0;
	int buttonmanager=1;
	int modeNO=0;
	float rotation_matrix[16] = { 1.0, 0.0, 0.0, 0.0,
                              0.0, 1.0, 0.0, 0.0,
                              0.0, 0.0, 1.0, 0.0,
                              0.0, 0.0, 0.0, 1.0 };
    float coEfficient=1.0;
    GLUI_Rotation *rotatewala;
    GLUI_Spinner  *coefficientwala;

	GLUI_RadioGroup *radioGroup;
	GLUI_RadioGroup *radioGroup2;
	GLUI *glUserInterface;
	
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

class Menu {
public:
	void createMenu();
	
	void handleMenu(GLUI* glUserInterface);
}menu;
	
#endif

