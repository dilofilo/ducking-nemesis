#include <vector>

/**
	The main loop will create an array of balls which will handle their respective graphics and update their own positions etc. The main loop will merely handle the checking for collisions.
*/
class Ball {
	private:
		float xCentre,yCentre, radius;
		float xVelocity, yVelocity;
		float color[4];
		float mass;

	public:
			Ball(float _xCentre , float _yCentre , float radius)  {
				xCentre = _xCentre;
				yCentre = _yCentre;
				color[0] = 1.0;
				color[1] = 0.0;
				color[2] = 0.0;
				mass = pow(radius,3); 
			}
			Ball(const Ball& ball) {
				xCentre = ball.getxCentre();
				yCentre = ball.getyCentre();

			}
			~Ball();
			void display();
			void updateVelocity(Ball &collision);

			

}