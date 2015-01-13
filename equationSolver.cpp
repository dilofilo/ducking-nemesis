float* solveBallCollision(float vXBallA , float vYBallA , float massA ,  float vXBallB ,  float vYBallB , float massB , float deltaX , float deltaY)
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
