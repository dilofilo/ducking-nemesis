#ifndef EQUATION_SOLVER_CPP
	#define EQUATION_SOLVER_CPP

#include "includes.h"
///Some vector based functions which are required to solve the system of equations. 

vector<float> addVectors( vector<float> a , vector<float> b) { // returns a+b
	if (a.size() != b.size()) {
		cout << "INCORRECT DIMENSIONS ERROR!";
	} else {
		vector<float> sum(a.size(),0);
		for(int i=0; i< a.size() ; i++ ) sum[i] = a[i]+b[i] ;
		return sum;
	}
}

float dotProduct( vector<float> a , vector<float> b ) { // returns a.b
	if (a.size() != b.size()) {
		cout << "INCORRECT DIMENSIONS ERROR!";
	} else {
		float dot = 0;
		for(int i=0; i< a.size() ; i++ ) dot += a[i]*b[i] ;
		return dot;	
	}
}

vector<float> ScalarMult(vector<float> vec , float x) { // returns x.vec
	vector<float> result(vec.size() , 0);
	for(int i=0; i< vec.size() ; i++) result[i] = vec[i]*x;
	
	return result;
}

///Function that accepts parameters of two balls and returns the new velocities.
//Documentation provided.
pair< vector<float> , vector<float> > solveBallCollision( vector<float> velocityA , vector<float> velocityB , vector<float> posA , vector<float> posB , float massA , float massB , float e = 1.0) {
	pair< vector<float>  , vector<float> > velocities;
	velocities.first.resize(velocityA.size());
	velocities.second.resize(velocityB.size());
	vector<float> deltaPos = addVectors( posA , ScalarMult(posB , -1.0)); 
	float deltaPosMagnitude = sqrt( dotProduct( deltaPos , deltaPos) );
	deltaPos = ScalarMult( deltaPos, 1.0 / deltaPosMagnitude );					//Unit vector in direction of common normal

	//Vector formula described in documentation.
	velocities.first =  addVectors( velocityA , ScalarMult( deltaPos, ( dotProduct(deltaPos, addVectors( ScalarMult(velocityB,massB*(1.0+e)/(massA+massB)), ScalarMult(velocityA,-1.0*(1.0+e)*massB/(massA+massB)))))));  
	velocities.second = addVectors( velocityB , ScalarMult( deltaPos, ( dotProduct(deltaPos, addVectors( ScalarMult(velocityA,massA*(1.0+e)/(massA+massB)), ScalarMult(velocityB,-1.0*(1.0+e)*massA/(massA+massB)))))));
	
	return velocities;
}

#endif