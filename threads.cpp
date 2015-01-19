struct threadDetailsMessage {
	int receiverID;
	int senderID;
	vector<float> senderVelocity;
	vector<float> senderNextPosition;
	float senderMass;
	float senderRadius;
};


void* ballThread(void* args) {
	BallThreadParameters* arg = (BallThreadParameters*)args ;
	int ID = arg->ID;
	//TODO
	while(true) {
		vector<float> newPos;
		pthread_mutex_lock(&vecMutexBallPthreads[ID]);
		while(numBallUpdates == 0)
			pthread_cond_wait(&vecCondBallUpdateBegin[ID] , &vecMutexBallPthreads[ID]);
		while( (numBallUpdates > 0) && ( vecShouldBallUpdate[ID] ) ) {
			pthread_mutex_lock(&mutexStateVariableUpdate);
			numBallUpdates--;
			vecShouldBallUpdate[ID] = false;
			pthread_mutex_unlock(&mutexStateVariableUpdate);
			newPos = nextPos(DELTA_T);
			ball[ID]->setPosition(newPos);
		}
		pthread_cond_signal(&condBallUpdateComplete);
		pthread_mutex_unlock(&vecMutexBallPthreads[ID]);
	}
}
