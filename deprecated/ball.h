#ifndef BALL_H
	#define BALL_H
#include <vector>

/**
	The main loop will create an array of balls which will handle their respective graphics and update their own positions etc. The main loop will merely handle the checking for collisions.
*/
#define MAX_VELOCITY 10.0
class Ball {
	private:
		///Ordinary ball measurements (physical)

		float xCentre,yCentre, radius;
		float xVelocity, yVelocity;
		float color[4];
		float mass;
		float velocityLimit;
		///BallList needed to allow for checking collisions etc;
		int idx; //The index of the ball in the balllist.
		static vector<Ball*> BallList;
		float oldWidth , oldHeight;
		bool isSelected;
	public:
		///Constructor
			Ball(float _xCentre , float _yCentre , float _radius , float R , float G , float B , float _oldW , float _oldH)  {
				oldWidth = _oldW;
				oldHeight = _oldH;
				velocityLimit = MAX_VELOCITY;
				xCentre = _xCentre;
				yCentre = _yCentre;
				radius = _radius;
				color[0] = R; 
				color[1] = G;
				color[2] = B;
				color[3] = 1.0;
				mass = pow(radius,3); 
				isSelected = false;
				xVelocity = 0.0;
				yVelocity = 0.0;
			}
		///Copy Constructor because good practice
			Ball(Ball& ball) {
				xCentre = ball.getxCentre();
				yCentre = ball.getyCentre();
				radius = ball.getRadius();
				xVelocity = ball.getxVelocity();
				yVelocity = ball.getyVelocity();
				mass = ball.getMass();

			}
		///Destructor
			~Ball();

		///get and set methods!
			void setxCentre(float _x) { xCentre = _x; }
			void setyCentre(float _y) { yCentre = _y; }
			void setRadius(float _r) { radius = _r; }
			void setyVelocity(float _y) { yVelocity = _y; }
			void setxVelocity(float _x) { xVelocity = _x; }
			// void setMass(float _m) { mass = _m; }
			void setColor( float* _color ) { color[0] = _color[0]; color[1] = _color[1]; color[2] = _color[2]; color[3] = _color[3];}
			void setIdx(int _id) { idx = _id;}
			void setIsSelected(bool _x) { isSelected = _x; }

			bool getIsSelected() { return isSelected; }
			float getRadius() { return radius; }
			float getxCentre() {return xCentre;}
			float getyCentre() {return yCentre;}
			float getxVelocity() {return xVelocity;}
			float getyVelocity() {return yVelocity;}
			float getMass() {return mass;}
			int getIdx() { 	return idx;	}

			bool willBallCollide(Ball* ball) {
				float newDeltaX = this->getxCentre() + deltaT*this->getxVelocity()- ball->getxCentre() - deltaT*ball->getxVelocity();
				float newDeltaY = this->getyCentre() + deltaT*this->getyVelocity()- ball->getyCentre() - deltaT*ball->getyVelocity();
				return (((pow(newDeltaX ,2) + pow( newDeltaY , 2) ) ) < pow( ( this->getRadius() + ball->getRadius() ) , 2));
			}
		///display() function will be called by the ScreenSaver's display()
			void display();
		///check for collisions and update this ball if needed.
			//void checkCollisions(); Actually present in the screen saver ka code.
		///reshape() function for if reshapes are required.
			void reshape(int w , int h);

};

#endif