#include <pthread.h>
#include <GL/glut.h>



#include <math.h>
#define PI 3.1415926535897932384626433832795
#define Z_CAMERA  10.0
#include <time.h>
#include <iostream>
#include <string>
#include <stringstream>


static int WIDTH = 640;
static int HEIGHT = 480;

#include <ball.h>
#include <ball.cpp>
#include <table.h>
#include <table.cpp>
#include <screenSaver.h>
#include <screenSaver.cpp>

#define XLL -1.0
#define YLL -1.0
#define XLR 1.0
#define YLR -1.0
#define XTR 1.0
#define YTR 1.0
#define XTL -1.0
#define YTL 1.0


using namespace std;

int main(int argc, char** argv) {
	
	//Code to convert string to int
	int numThreads = 0;
	string myString = argv[1];
	istringstream buffer(myString);
	buffer >> numThreads;
	//Code to convert numThreads to int is complete.

	screenSaver* obj = new screenSaver(numThreads);
	obj->execute(); //execute should not return.
	return 0;
}