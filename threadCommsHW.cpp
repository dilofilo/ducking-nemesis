#include <vector>
#include <iostream>

using namespace std;

enum MessageInstruction { INSTRUCT_A = 1 , INSTRUCT_B = 2 };

struct ThreadMessage {
	int senderID;
	int receiverID;
	MessageInstruction
};

static vector<ThreadMessage> mailbox;

void* thread(void* args) {
	
}

int main(int argc,char** argv) {


	return 0;
}