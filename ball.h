#ifndef BALL_H
	#define BALL_H
#include <vector>

/**
	The main loop will create an array of balls which will handle their respective graphics and update their own positions etc. The main loop will merely handle the checking for collisions.
*/

class Ball {
	private:
		///Ordinary ball measurements (physical)

		float xCentre,yCentre, radius;
		float xVelocity, yVelocity;
		float color[4];
		float mass;

		///BallList needed to allow for checking collisions etc;
		int idx; //The index of the ball in the balllist.
		static vector<Ball*> BallList;
	public:
		///Constructor
			Ball(float _xCentre , float _yCentre , float radius)  {
				xCentre = _xCentre;
				yCentre = _yCentre;
				color[0] = 1.0;
				color[1] = 0.0;
				color[2] = 0.0;
				color[3] = 1.0;
				mass = pow(radius,3); 
			}
		///Copy Constructor becaus good practice
			Ball(const Ball& ball) {
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
			void setyVelocity(float _y) { yCentre = _y; }
			void setxVelocity(float _x) { xVelocity = _x; }
			void setMass(float _m) { mass = _m; }
			void setColor( float* _color ) { color[0] = _color[0]; color[1] = _color[1]; color[2] = _color[2]; color[3] = _color[3];}

			float getxCentre() {return xCentre;}
			float getyCentre() {return yCentre;}
			float getxVelocity() {return xVelocity;}
			float getyVelocity() {return yVelocity;}
			float getMass() {return mass;}

			void setIdx(int _id) { idx = _id;}
			int getIdx() { 	return idx;	}
		///display() function will be called by the ScreenSaver's display()
			void display();
		///check for collisions and update this ball if needed.
			void checkCollisions();
		///this ball collides with ball2.
			void update(Ball &ball2);
		///draw() draws the ball on the screen.
			void draw(); //3d drawing.
		///reshape() function for if reshapes are required.
			void reshape();

};

#endif