#ifndef BALL_H
	#define BALL_H

vector<float> vecZero{ 0.0 , 0.0 , 0.0};

class Ball {
private:
	///Physical Parameters
	vector<float> position;
	vector<float> velocity;
	float mass;
	float radius;
	///Visual Parameters (GUI)
	vector<float> color;
	bool isSelected;

public:

	Ball(vector<float> pos = vecZero , vector<float> velo = vecZero , float _radius = 1.0 , vector<float> _color = vecZero) {
		position = pos;
		velocity = velo;
		radius = _radius;
		color = _color;
		isSelected = false;
		mass = pow(radius, 3);
	} //Constructor Done
	~Ball() {

	}	///Set/Get functions
	float getxCentre() { return position[0] ; }
	float getyCentre() { return position[1] ; }
	float getzCentre() { return position[2] ; }
	void setxCentre(float _x) { position[0] = _x ; }
	void setyCentre(float _y) { position[2] = _y ; }
	void setzCentre(float _z) { position[3] = _z ; }
	float getxVelocity() { return velocity[0] ; }
	float getyVelocity() { return velocity[1] ; }
	float getzVelocity() { return velocity[2] ; }
	void setxVelocity(float _x) { velocity[0] = _x ; }
	void setyVelocity(float _y) { velocity[2] = _y ; }
	void setzVelocity(float _z) { velocity[3] = _z ; }

	vector<float> getPosition() { return position; }
	vector<float> getVelocity() { return velocity; }
	void setPosition(vector<float> newPos) { position = newPos; }
	void setVelocity(vector<float> newVelocity) { velocity = newVelocity;}


	float getMass() { return mass; }
	void setMass(float _m) { mass = _m ;}
	vector<float> getColor() { return color; }
	void setColor( vector<float> _color ) { color = _color; }
	void toggleSelect() { isSelected = !isSelected ; }

	void display();
	void reshape(int w, int h , int oldWidth , int oldHeight);
	
	//void* ballThread(void* args); Not part of the ball class, just packaged along with it.

	vector<float> nextPos(float dt); //deprecated


	void displace(float dt); //displaces ball
	void handleWallCollision(Table* _table);
	///Receives the collision handle and updates itself accordingly.
	void handleBallCollision(vector<float>& deltaPosition , vector<float>& targetVelocity , float targetMass );
};

vector<Ball*> ball; //CHANGE BALL TO BALLS YADAYADYAYDAYDYAD

#endif