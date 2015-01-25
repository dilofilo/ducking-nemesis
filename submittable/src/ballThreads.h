#ifndef BALL_THREADS_H
	#define BALL_THREADS_H

#include "includes.h"
#include "ball.h"
#include "equationSolver.h"


///Function to send a message. The receiver's ID is present in the message itself.
//void sendMessage(BallDetailsMessage &msg);

///Barrier synchronization method can be implemented using the waitForMessages function
void waitForMessages(int threadID);

///One to one synchronization can be implemented using the waitForMessage function
void waitForMessage(int threadID);

///The control function for every thread
void* ballThread(void* args);

///Initialization for threads.
void threadInit();


#endif