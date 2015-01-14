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
	float getMass() { return mass; }
	void setMass(float _m) { mass = _m ;}
	vector<float> getColor() { return color; }
	void setColor( vector<float> _color ) { color = _color; }
	void toggleSelect() { isSelected = !isSelected ; }

	void display();
	void reshape(int w, int h , int oldWidth , int oldHeight);
};
#endif