#ifndef EQUATION_SOLVER_H
	#define EQUATION_SOLVER_H


vector<float> 	addVectors( vector<float> a , vector<float> b );
float			dotProduct( vector<float> a , vector<float> b );
vector<float> 	ScalarMult( vector<float> vec , float x );
pair< vector<float> , vector<float> > solveBallCollision( vector<float> velocityA , vector<float> velocityB , vector<float> posA , vector<float> posB , float massA , float massB , float e = 1.0);

#endif