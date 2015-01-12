/**
	The screenSaver class is called 
*/


#ifndef SCREEN_SAVER_H
	#define SCREEN_SAVER_H

#include <vector>
#include <pthread.h>	
class ScreenSaver {
private:
	bool isPaused;
	bool isFullScreen;
	int windowID;
	int numThreads; ///Contains the number of threads requested by the make command.
	Table* table;
	vector<Ball*> balls;
	vector<pthread_t> threads;
public:
	ScreenSaver(int n) {
		numThreads = n;
		windowID = -1;
		isFullScreen = false;
		isPaused = false;
	};
	void exitter(); ///Closes windows and destroys objects.
	void init(); /// function to initialize views, camera etc for glut.
	void makeObjects(Table* table, vector<Ball*>& ballList); ///function to make the table and the objects which will be displayed.
	void reshape(int w , int h); ///function to handle reshaping of windows
	void keyHandler(unsigned char key, int x , int y); ///function to handle the keys pressed by the user - including , escape, spacebar and F
	void display(); ///function to handle the actual display jobs.
	void execute(); ///Begins the entire program.
};

#endif