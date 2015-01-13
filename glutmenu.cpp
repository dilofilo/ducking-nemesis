#include <iostream>
#include <GL/glut.h>
using namespace std;

int main()
{

	int menuidentifier;
	menuidentifier=glutCreateMenu(void (*func)(int value));
	//the function will handle the job based on menu entries
	//the return type of the function is the menu identifier
	void glutAddMenuEntry(char *name, int value);
	//name is what is displayed
	//value is what is passed to function
	void glutAttachMenu(int button);
	//when the menu appears
	return 0;
}