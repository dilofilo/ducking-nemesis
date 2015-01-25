#ifndef BALL_THREADS_H
	#define BALL_THREADS_H

#include "includes.h"
#include "ball.h"
#include "equationSolver.h"

///This struct can be used to pass more data if ever required.
		struct BallThreadParameters {
			int ID;
		BallThreadParameters(int x) { ID = x;}
		};
  
///The message that will be sent between threads
		struct BallDetailsMessage {
			int receiverID;
			int senderID;
			std::vector<float> senderVelocity;
			std::vector<float> senderPosition;
			float senderMass;
			float senderRadius;
		};


///The parameters passed into every thread are in this form. It can be changed if necessary
	std::vector<pthread_t> vecBallThread;					//Threads
	std::vector<pthread_mutex_t> vecMutexBallPthreads;		//Lock for every thread

	vector<bool> threadTerminate;							//Termination Boolean
	vector<pthread_mutex_t> vecMutexThreadTerminate;		//Termination Mutex

	std::vector< std::queue<BallDetailsMessage> > mailBox; 	//Mailbox for each thread.
	std::vector<pthread_mutex_t> vecMutexMailBox;			//Lock for every ball's mailbox
	std::vector<pthread_cond_t> vecCondMailBoxReceived;		//Conditional variable for mailbox
	
	//Interaction between timer and each thread.
	pthread_mutex_t mutexStateVariableUpdate;				//Lock for timer to update booleans
	std::vector<bool> vecShouldBallUpdate;					//Boolean indicator
	static int numBallUpdates;								//Number of balls indicator to avoid an O(n) check
	std::vector<pthread_cond_t> vecCondBallUpdateBegin;		//Conditional variables to begin the update of every thread - Sent to every worker thread
	pthread_cond_t condBallUpdateComplete;					//Conditional variable for update completition - Sent to parent thread


///Function to send a message. The receiver's ID is present in the message itself.
void sendMessage(BallDetailsMessage &msg);

///Barrier synchronization method can be implemented using the waitForMessages function
void waitForMessages(int threadID);

///One to one synchronization can be implemented using the waitForMessage function
void waitForMessage(int threadID);

///The control function for every thread
void* ballThread(void* args);

///Initialization for threads.
void threadInit();


#endif