#ifndef EQUATION_SOLVER_CPP
	#define EQUATION_SOLVER_CPP
#include <GL/glut.h>
#include <pthread.h>
#include <math.h>
#include <vector>
#include <queue>
#include <time.h>
#include <iostream>

///deprecated
float* old_solveBallCollision(float vXBallA , float vYBallA , float massA ,  float vXBallB ,  float vYBallB , float massB , float deltaX , float deltaY)
{
	/// Returns an array of four float numbers corresponding to VXA, VYA, VXB, 
	float vBallANormal,vBallAPerp,vBallBNormal,vBallBPerp;
	float vBallANormalFin,vBallAPerpFin,vBallBNormalFin,vBallBPerpFin;
	float vXBallAFin,vYBallAFin,vXBallBFin,vYBallBFin;
	float perpLength;
	perpLength=sqrt(deltaY*deltaY+deltaX*deltaX);
	
	float sinTheta=deltaY/perpLength;
	float cosTheta=deltaX/perpLength;

	vBallANormal=vXBallA*cosTheta+vYBallA*sinTheta;
	vBallAPerp=vYBallA*cosTheta - vXBallA*sinTheta;
	vBallBNormal=vXBallB*cosTheta+vYBallB*sinTheta;
	vBallBPerp=vYBallB*cosTheta- vXBallB*sinTheta;

	vBallAPerpFin=vBallAPerp;
	vBallBPerpFin=vBallBPerp;
	vBallANormalFin=((massA-massB)*vBallANormal+2*massB*vBallBNormal)/(massA+massB);
	vBallBNormalFin=((massB-massA)*vBallBNormal+2*massA*vBallANormal)/(massA+massB);

	vXBallAFin = vBallANormalFin*cosTheta - vBallAPerpFin*sinTheta;
	vYBallAFin= vBallANormalFin*sinTheta + vBallAPerpFin*cosTheta;
	vXBallBFin= vBallBNormalFin*cosTheta - vBallBPerpFin*sinTheta;
	vYBallBFin= vBallBNormalFin*sinTheta + vBallBPerpFin*cosTheta;

	float* vFin=new float[4];
	vFin[0]=vXBallAFin;
	vFin[1]=vYBallAFin;
	vFin[2]=vXBallBFin;
	vFin[3]=vYBallBFin;

	return vFin;

}


/**
Some vector based functions which are required to solve the system of equations. 
*/
vector<float> addVectors( vector<float> a , vector<float> b) {
	if (a.size() != b.size()) {
		cout << "INCORRECT DIMENSIONS ERROR!";
	} else {
		vector<float> sum(a.size(),0);
		for(int i=0; i< a.size() ; i++ ) sum[i] = a[i]+b[i] ;
		return sum;
	}
}

float dotProduct( vector<float> a , vector<float> b ) {
	if (a.size() != b.size()) {
		cout << "INCORRECT DIMENSIONS ERROR!";
	} else {
		float dot = 0;
		for(int i=0; i< a.size() ; i++ ) dot += a[i]*b[i] ;
		return dot;	
	}
}

vector<float> ScalarMult(vector<float> vec , float x) {
	vector<float> result(vec.size() , 0);
	for(int i=0; i< vec.size() ; i++) result[i] = vec[i]*x;

	return result;
}



///Function that accepts parameters of two balls and returns the new velocities.
pair< vector<float> , vector<float> > solveBallCollision( const vector<float>& velocityA , const vector<float>& velocityB , const vector<float>& posA , const vector<float>& posB , float massA , float massB , float e = 1.0) {
	pair< vector<float>  , vector<float> > velocities;
	velocities.first.resize(velocityA.size());
	velocities.second.resize(velocityB.size());
	vector<float> deltaPos = addVectors( posA , ScalarMult(posB , -1.0)); 
	float deltaPosMagnitude = sqrt( dotProduct( deltaPos , deltaPos) );
	deltaPos = ScalarMult( deltaPos, 1.0 / deltaPosMagnitude );
	///Have fun with this code.
	//velocities.first  = addVectors(velocityA , ScalarMult( deltaPos , ( ScalarMult( addVectors( ScalarMult( velocityA , 1.0 - e ) , ScalarMult( ScalarMult( velocityB , 1.0 + e) , -1.0) ) ) , (massB/(massA + massB))))));
	//velocities.second = addVectors(velocityB , ScalarMult( deltaPos , ( ScalarMult( addVectors( ScalarMult( velocityB , 1.0 - e ) , ScalarMult( ScalarMult( velocityA , 1.0 + e) , -1.0) ) , (massA/(massA + massB))))));
	
	velocities.first  = addVectors( velocityA , ScalarMult( deltaPos , dotProduct( deltaPos , addVectors(ScalarMult( velocityA , 1.0-e ) , ScalarMult( velocityB , -1.0 - e ) ) )*( massB/(massA+massB) ) ));
	velocities.second = addVectors( velocityB , ScalarMult( deltaPos , dotProduct( deltaPos , addVectors(ScalarMult( velocityA , -1.0-e) , ScalarMult( velocityB , 1.0 - e )  ) )*( massA/(massA+massB) ) ));

	return velocities;
}

#endif