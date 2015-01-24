#ifndef BALL_THREADS_CPP
	#define BALL_THREADS_CPP

///This struct can be used to pass more data if ever required.
struct BallThreadParameters {
	int ID;
	BallThreadParameters(int x) { ID = x;}
};
  
///The message that will be sent
struct BallDetailsMessage {
	int receiverID;
	int senderID;
	std::vector<float> senderVelocity;
	std::vector<float> senderPosition;
	float senderMass;
	float senderRadius;
};

///A function that modularly posts messages.
void sendMessage(BallDetailsMessage &msg) {
	pthread_mutex_lock( &vecMutexMailBox[ msg.receiverID ]);
		mailBox[msg.receiverID].push(msg);
		pthread_cond_signal( &vecCondMailBoxReceived[ msg.receiverID ]); //Post the message and notify the receiver.
	pthread_mutex_unlock(&vecMutexMailBox[ msg.receiverID ]);
}

///Deprecated - implements barrier synchro mode
void waitForMessages(int threadID) {
	pthread_mutex_lock( &vecMutexMailBox[threadID]);
	while(mailBox[threadID].size() < NUM_BALLS ) {
		pthread_cond_wait(&vecCondMailBoxReceived[threadID] , &vecMutexMailBox[threadID]);
	}
	pthread_mutex_unlock( &vecMutexMailBox[threadID] );
}

///Supported - implements One to One synchronization
void waitForMessage(int threadID) {
	while(mailBox[threadID].empty()) {
		pthread_cond_wait(&vecCondMailBoxReceived[threadID] , &vecMutexMailBox[threadID]);
	}
}

///The thread
void* ballThread(void* args) {
	BallThreadParameters* arg = (BallThreadParameters*)args ;
	int ID = arg->ID;
	float myMass = ball[ID]->getMass();
	float myRadius = ball[ID]->getRadius();
	while(true) {
		//Thread for exitting from the thread.
		pthread_mutex_lock(&vecMutexThreadTerminate[ID] );
			if(threadTerminate[ID]) {
				pthread_mutex_unlock(&vecMutexThreadTerminate[ID]);
				break;
			}
		pthread_mutex_unlock(&vecMutexThreadTerminate[ID] );

		//Functional Code.
		pthread_mutex_lock(&vecMutexBallPthreads[ID]);
		while(numBallUpdates == 0 || !vecShouldBallUpdate[ID] )
			pthread_cond_wait(&vecCondBallUpdateBegin[ID] , &vecMutexBallPthreads[ID]);
		while( (numBallUpdates > 0) && ( vecShouldBallUpdate[ID] ) ) {
			pthread_mutex_lock(&mutexStateVariableUpdate);
			numBallUpdates--;
			vecShouldBallUpdate[ID] = false;
			pthread_mutex_unlock(&mutexStateVariableUpdate);
			//Timer-related things have been started.

			///Generate N messages, and push them all.
			for(int i=0; i<NUM_BALLS; i++) {
				if ( i!= ID) {
					//Construct a message which contains present thread's data.
					BallDetailsMessage msg;
						msg.senderID = ID;
						msg.senderRadius = myRadius;
						msg.senderMass = myMass;
						msg.senderVelocity = ball[ID]->getVelocity();
						msg.senderPosition = addVectors(ball[ID]->getPosition() , ScalarMult( ball[ID]->getVelocity(), DELTA_T));
						msg.receiverID = i; 
						sendMessage(msg); //Send message to everyone.
				} //Message sent.
			}

			#if defined(DEBUG) || defined(THREAD_DEBUG)
				cout << "thread: " << ID <<	" will now begin waiting \n";		
			#endif
			//waitForMessages(ID); //Deprecated

			///Process messages received.
			for(int i = 1 ; i< NUM_BALLS; i++) { //Pop n-1 messages.
				pthread_mutex_lock(&vecMutexMailBox[ID]);	
				///Wait to receive atleast one message.
				waitForMessage(ID);
				//ASSERT : MailBox is not empty.
					BallDetailsMessage msg = mailBox[ID].front();
						mailBox[ID].pop();
					///BallToBall Collisions
					ball[ID]->handleBallCollision(msg.senderPosition , msg.senderVelocity , msg.senderMass , msg.senderRadius); //Changes the velocity,not the 
				
				pthread_mutex_unlock(&vecMutexMailBox[ID]);
			}
			
			//Ensure that ball isn't speeding
			float ratio = ball[ID]->getSpeed() / MAX_VELOCITY;
			if ( ratio >= 1.0) {
				ball[ID]->slowDown(ratio);
			}

			//Self explanotry code follows
			ball[ID]->handleWallCollision(table);
			ball[ID]->displace(DELTA_T);

			//Updates have ended
			pthread_cond_signal(&condBallUpdateComplete);
		}
		pthread_mutex_unlock(&vecMutexBallPthreads[ID]);
	}
}

///Function called for initializing all the thread-related variables
void threadInit() {
	numBallUpdates = NUM_BALLS;
	vecMutexBallPthreads.resize(NUM_BALLS);
	vecCondBallUpdateBegin.resize(NUM_BALLS);
	vecBallThread.resize(NUM_BALLS);
	vecShouldBallUpdate.resize(NUM_BALLS , true);
	vecMutexMailBox.resize(NUM_BALLS);
	vecCondMailBoxReceived.resize(NUM_BALLS);
	mailBox.resize(NUM_BALLS);

	threadTerminate.resize(NUM_BALLS,false);
	vecMutexThreadTerminate.resize(NUM_BALLS);

	pthread_mutex_init(&mutexStateVariableUpdate , NULL);
	for(int i = 0; i< NUM_BALLS ; i++) {
		pthread_mutex_init(&vecMutexBallPthreads[i] , NULL);
		pthread_cond_init(&vecCondBallUpdateBegin[i] , NULL);
		//pthread_cond_init(&vecCondBallUpdateComplete[i] , NULL);
		pthread_cond_init(&condBallUpdateComplete , NULL);
		pthread_mutex_init(&vecMutexMailBox[i] , NULL);
		pthread_cond_init(&vecCondMailBoxReceived[i] , NULL);

		pthread_mutex_init(&vecMutexThreadTerminate[i] , NULL);
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