
GLuint skyBoxFace;	

void loadTexture(char* fileName , int fileWidth , int fileHeight) {
	//Read File
	unsigned char* image;
	unsigned char* garbage;
	FILE* file = fopen(fileName , "rb");
		if (file==NULL) return; //Error handling.

	image = (unsigned char*) malloc( fileWidth*fileHeight*3) ; // Magical 3. Maybe for RGB?
	fread( garbage , 1 , 54  , file);
	fread( image , 1 ,fileWidth*fileHeight*3 , file);
	fclose(file); //Handles fstream.

	for(int i=0; i <fileWidth*fileHeight ; i++) {
		//Swap image[i*3] and image[i*3 + 2]
		unsigned char R = image[3*i + 2];
		unsigned char B = image[3*i];

		image[3*i] = R;
		image[3*i + 2] = B;
	}

	//Generate texture
	glGenTextures(1 , &skyBoxFace);
	glBindTexture(GL_TEXTURE_2D , skyBoxFace);
	glTexEnvf(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, fileWidth, fileHeight ,GL_RGB, GL_UNSIGNED_BYTE, image );
	free(image); //Memory handled.
}

void displaySkybox() {
	glBindTexture(GL_TEXTURE_2D ,  skyBoxFace);

	glBegin(GL_QUADS);
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( _cornersTHREE_D[0][0] , _cornersTHREE_D[0][1] , -2*_cornersTHREE_D[0][2]);
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( _cornersTHREE_D[1][0] , _cornersTHREE_D[1][1] , -2*_cornersTHREE_D[1][2]);
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( _cornersTHREE_D[2][0] , _cornersTHREE_D[2][1] , -2*_cornersTHREE_D[2][2]);
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( _cornersTHREE_D[3][0] , _cornersTHREE_D[3][1] , -2*_cornersTHREE_D[3][2]);
	glEnd();
	
}


void killSkybox() {
	glDeleteTextures(1 , &skyBoxFace);
}

void initSkybox() {
	loadTexture("skybox.bmp" , 256 ,256);
	glEnable(GL_TEXTURE_2D);
}
