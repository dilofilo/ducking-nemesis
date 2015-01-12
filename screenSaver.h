/**
	The screenSaver class is called 
*/


#ifndef SCREEN_SAVER_H
	#define SCREEN_SAVER_H

class ScreenSaver {
private:
	int numThreads;

public:
	ScreenSaver(int n);
	void ballThread(void* ballIdx);	
	void execute();
};

#endif