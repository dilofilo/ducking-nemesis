/**
	The screenSaver class is called 
*/


#ifndef SCREEN_SAVER_H
	#define SCREEN_SAVER_H

class ScreenSaver {
private:
	int numThreads;
	void init();
	void reshape(int w , int h);
	void keyHandler(unsigned char key, int x , int y);
	void display();
public:
	ScreenSaver(int n) {
		numThreads = n;
	};
	void ballThread(void* ballIdx);	
	void execute();
};

#endif