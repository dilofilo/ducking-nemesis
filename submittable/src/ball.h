 #ifndef BALL_H
	#define BALL_H

#include "includes.h"
#include "table.h"
#include "equationSolver.h"

class Ball {
private:
	///Physical Parameters
	vector<float> 	position;
	vector<float> 	velocity;
	float 			mass;
	float 			myColour[4];
	float 			radius;
	///Visual Parameters (GUI)
	vector<float> 	color;
	bool 			isSelected;
	int 			timeSinceCollision;
public:

	Ball(vector<float> pos  , vector<float> velo  , float _radius  , vector<float> _color ) {
		position = pos;
		velocity = velo;
		radius = _radius;
		color = _color;
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
	}	

	///Set/Get functions
	
	//Positions
	float 			getxCentre() { return position[0] ; }
	float 			getyCentre() { return position[1] ; }
	float 			getzCentre() { return position[2] ; }
	void  			setxCentre(float _x) { position[0] = _x ; }
	void  			setyCentre(float _y) { position[1] = _y ; }
	void  			setzCentre(float _z) { position[2] = _z ; }
	void 			setPosition(vector<float> newPos) { position = newPos; }
	void 			displace(float dt); //displaces ball

	//Velocities	
	float 			getxVelocity() { return velocity[0] ; }
	float 			getyVelocity() { return velocity[1] ; }
	float 			getzVelocity() { return velocity[2] ; }
	void  			setxVelocity(float _x) { velocity[0] = _x ; }
	void  			setyVelocity(float _y) { velocity[1] = _y ; }
	void  			setzVelocity(float _z) { velocity[2] = _z ; }
	vector<float>	getPosition() { return position; }
	vector<float> 	getVelocity() { return velocity; }
	void 			setVelocity(vector<float> newVelocity) { velocity = newVelocity;}
	void 			VelocityIncreaser();
	void 			VelocityDecreaser();
	
	//Radius and Mass
	float 			getRadius() { return radius; }
	void 			setRadius(float _r) { radius = _r; }
	float 			getMass() { return mass; }
	void 			setMass(float _m) { mass = _m ;}
	void 			setTimeSinceCollision(int _t) { timeSinceCollision = _t; }
	//Colors
	void 			changeColor();
	vector<float> 	getColor() { return color; }
	void 			setColor( vector<float> _color ) { color = _color; }

	//Booleans
	void 			setIsSelected(bool tempVar) { isSelected = tempVar; }
	void 			toggleSelect() { isSelected = !isSelected ; }

	
	///Speed control functions
	float 	getSpeed() {
		float speed = 0;
		for(int i=0; i<velocity.size() ; i++) {
			speed += pow(velocity[i] , 2);
		}
		return speed;
	}
	//Slows down by given ratio
	void 	slowDown(float ratio) {
		for(int i=0; i<velocity.size() ; i++)
			velocity[i] /= ratio ;
	}

	//Collision Functions
	void 			handleWallCollision(Table* _table);
	void 			handleBallCollision(vector<float> targetPosition , vector<float> targetVelocity , float targetMass , float targetRadius);

	//Graphics functions
	void 			ballMaterial();
	void 			display();
	void 			reshape(int w, int h , int oldWidth , int oldHeight);
	
};


#endif