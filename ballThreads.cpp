#ifndef BALL_THREADS_CPP
	#define BALL_THREADS_CPP

#include <vector>
#include <queue>
#include <pthread.h>
///The message that will be sent
struct BallDetailsMessage {
	int receiverID;
	int senderID;
	std::vector<float> senderVelocity;
	std::vector<float> senderNextPosition;
	float senderMass;
	float senderRadius;
};
///Mailbox for each thread.
std::vector< std::queue<BallDetailsMessage> > mailBox;

///All the variables needed for threading
	
	//Unnecessary lock for each thread
	std::vector<pthread_mutex_t> vecMutexBallPthreads;

	//Interaction between timer and each thread.
	static int numBallUpdates;
	std::vector<pthread_cond_t> vecCondBallUpdateBegin;
	//vector<pthread_cond_t> vecCondBallUpdateComplete; //DEPRECATED
	pthread_mutex_t mutexStateVariableUpdate;
	std::vector<bool> vecShouldBallUpdate;
	std::vector<pthread_t> vecBallThread;
	pthread_cond_t condBallUpdateComplete;

	//Communication locks
	std::vector<pthread_mutex_t> vecMutexMailBox;
	std::vector<pthread_cond_t> vecCondMailBoxReceived;


///A function that modularly posts messages.
void sendMessage(BallDetailsMessage &msg) {
	pthread_mutex_lock( vecMutexMailBox[ msg.receiverID ]); //TODO
		mailBox[msg.receiverID].push_back(msg);
		pthread_cond_signal(vecCondMailBoxReceived[ msg.receiverID ]); //Post the message and notify the receiver.
	pthread_mutex_unlock();
}

///Function that makes calling thread wait until it has received N messages
void waitForMessages(int threadID) {
	pthread_mutex_lock( &vecMutexMailBox[threadID])
	while(mailBox[threadID].size() < NUM_BALLS ) {
		pthread_cond_wait(&vecCondMailBoxReceived[threadID] , &vecMutexMailBox[threadID]);
	}
	pthread_mutex_unlock( &vecMutexMailBox[threadID] );
}

///The thread's function
void* ballThread(void* args) {
	BallThreadParameters* arg = (BallThreadParameters*)args ;
	int ID = arg->ID;
	float myMass = ball[ID].getMass();
	float myRadius = ball[ID].getRadius();

	//TODO
	while(true) {
		pthread_mutex_lock(&vecMutexBallPthreads[ID]);
		while(numBallUpdates == 0)
			pthread_cond_wait(&vecCondBallUpdateBegin[ID] , &vecMutexBallPthreads[ID]);
		while( (numBallUpdates > 0) && ( vecShouldBallUpdate[ID] ) ) {
			pthread_mutex_lock(&mutexStateVariableUpdate);
			numBallUpdates--;
			vecShouldBallUpdate[ID] = false;
			pthread_mutex_unlock(&mutexStateVariableUpdate);
			//Timer-related things have been started.


			///Updates begin

			//All the updating goes here.
			ball[ID]->handleWallCollision(table);
			
			///Generate N messages, and push them all.
			for(int i=0; i<NUM_BALLS; i++) {
				if ( i!= ID) {
					BallDetailsMessage msg = new BallDetailsMessage();
						msg.senderID = ID;
						msg.senderRadius = myRadius;
						msg.senderMass = myMass;
						msg.senderVelocity = ball[ID].getVelocity();
						msg.senderNextPosition = addVector( ball[ID].getPosition() , DELTA_T*msg.senderVelocity);
						msg.receiverID = i;
						sendMessage(msg); //Also signals.
				} //Message created
			}

			
			///Can be replaced by a wait within the process messages part. That might speed up the entire process by a little bit.
			waitForMessages(ID);

			///Process messages received.
			for(int i = 1 ; i< NUM_BALLS; i++) { //Pop n messages.
				pthread_mutex_lock(vecMutexMailBox[ID]);	
				BallDetailsMessage msg = mailBox.front();
					mailBox.pop();
				///BallToBall Collisions
				ball[ID]->handleBallCollision(msg.senderNextPosition , msg.senderVelocity , msg.senderMass , msg.senderRadius); //Changes the velocity,not the 

				pthread_mutex_unlock(vecMutexMailBox[ID]);
			}
			ball[ID]->displace(DELTA_T);
			//Updates have ended
		}
		pthread_cond_signal(&condBallUpdateComplete);
		pthread_mutex_unlock(&vecMutexBallPthreads[ID]);
	}
}

///Function called for initializing all the thread-related variables
void threadInit() {
	vecMutexBallPthreads.resize(NUM_BALLS);
	//vecCondBallUpdateComplete.resize(NUM_BALLS);
	vecCondBallUpdateBegin.resize(NUM_BALLS);
	vecBallThread.resize(NUM_BALLS);
	numBallUpdates = NUM_BALLS;
	vecShouldBallUpdate.resize(NUM_BALLS , true);

	pthread_mutex_init(&mutexStateVariableUpdate , NULL);
	for(int i = 0; i< NUM_BALLS ; i++) {
		pthread_mutex_init(&vecMutexBallPthreads[i] , NULL);
		pthread_cond_init(&vecCondBallUpdateBegin[i] , NULL);
		//pthread_cond_init(&vecCondBallUpdateComplete[i] , NULL);
		pthread_cond_init(&condBallUpdateComplete , NULL);
	}

	for(int i = 0 ; i<NUM_BALLS ; i++) {
		BallThreadParameters* args = new BallThreadParameters(i);
		int rc = pthread_create(&vecBallThread[i] , NULL , ballThread , (void*)args);
			if(rc) {
				cout << "THREAD CREATION FAILED. YOU SHOULD PROBABLY NEVER SEE THIS MESSAGE.\n"	;
			}
	}
}

#endif