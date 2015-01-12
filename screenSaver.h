/**
	The screenSaver class is called 
*/


#ifndef SCREEN_SAVER_H
	#define SCREEN_SAVER_H

class ScreenSaver {
private:

	int numThreads; ///Contains the number of threads requested by the make command.
	void init(); /// function to initialize views, camera etc for glut.
	void reshape(int w , int h); ///function to handle reshaping of windows
	void keyHandler(unsigned char key, int x , int y); ///function to handle the keys pressed by the user - including , escape, spacebar and F
	void display(); ///function to handle the actual display jobs.

public:
	ScreenSaver(int n) {
		numThreads = n;
	};
	void ballThread(void* ballIdx);	
	void execute();
};

#endif