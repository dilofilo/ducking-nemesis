 #ifndef BALL_H
	#define BALL_H
using namespace std;
vector<float> vecZero{ 0.0 , 0.0 , 0.0};
static float gravity = 0.0;
#define GRAVITY 0.001;
static float coefficientRestitution = 0.8;
#define PI 3.14159265359
static int NUM_SLICES = 50;
static int NUM_STACKS = 50;
#define OFFSET 0.001

class Ball {
private:
	///Physical Parameters
	vector<float> position;
	vector<float> velocity;
	float mass;
	float myColour[4];
	float radius;
	///Visual Parameters (GUI)
	vector<float> color;
	bool isSelected;
	int timeSinceCollision;
public:

	Ball(vector<float> pos = vecZero , vector<float> velo = vecZero , float _radius = 0.1 , vector<float> _color = vecZero) {
		position = pos;
		velocity = velo;
		radius = _radius;
		color = _color;
		timeSinceCollision = 0;
			//myColor needed for lighting
			myColour[3] = 1.0;
			myColour[0] =color[0];
			myColour[1] =color[1];
			myColour[2] =color[2];
		color.push_back (1.0); /// For lighting
		isSelected = false;
		mass = pow(radius, 3);
	} //Constructor Done
	~Ball() {
		//delete[] myColour;
	}	

	///Set/Get functions
	float getxCentre() { return position[0] ; }
	float getyCentre() { return position[1] ; }
	float getzCentre() { return position[2] ; }
	void setxCentre(float _x) { position[0] = _x ; }
	void setyCentre(float _y) { position[1] = _y ; }
	void setzCentre(float _z) { position[2] = _z ; }
	float getxVelocity() { return velocity[0] ; }
	float getyVelocity() { return velocity[1] ; }
	float getzVelocity() { return velocity[2] ; }
	void setxVelocity(float _x) { velocity[0] = _x ; }
	void setyVelocity(float _y) { velocity[1] = _y ; }
	void setzVelocity(float _z) { velocity[2] = _z ; }
	void setTimeSinceCollision ( int time ) { timeSinceCollision = time; }
	void VelocityIncreaser();
	void VelocityDecreaser();
	void changeColor();

	vector<float> getPosition() { return position; }
	vector<float> getVelocity() { return velocity; }
	void setPosition(vector<float> newPos) { position = newPos; }
	void setVelocity(vector<float> newVelocity) { velocity = newVelocity;}
	float getRadius() { return radius; }
	void setRadius(float _r) { radius = _r; }
	float getMass() { return mass; }
	void setMass(float _m) { mass = _m ;}
	vector<float> getColor() { return color; }
	void setColor( vector<float> _color ) { color = _color; }
	void setIsSelected(bool tempVar) { isSelected = tempVar; }
	void toggleSelect() { isSelected = !isSelected ; }

	///Speed control functions
	float getSpeed() {
		float speed = 0;
		for(int i=0; i<velocity.size() ; i++) {
			speed += pow(velocity[i] , 2);
		}
		return speed;
	}
	//Slows down by given ratio
	void slowDown(float ratio) {
		for(int i=0; i<velocity.size() ; i++)
			velocity[i] /= ratio ;
	}

	void display();
	void reshape(int w, int h , int oldWidth , int oldHeight);
	
	//void* ballThread(void* args); //Not part of the ball class, just packaged along with it. //Can now be found in ballThreads.cpp

	void displace(float dt); //displaces ball
	void handleWallCollision(Table* _table);
	void pullApart(vector<float> targetPosition, vector<float> targetVelocity, float targetRadius);

	///Receives the collision handle and updates itself accordingly.
	void handleBallCollision(vector<float> targetPosition , vector<float> targetVelocity , float targetMass , float targetRadius);
};

vector<Ball*> ball; //CHANGE BALL TO BALLS YADAYADYAYDAYDYAD

#endif