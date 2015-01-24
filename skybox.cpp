#include <SDL/SDL.h>

GLuint skyBoxFace;	

unsigned int loadTexture(char* filename) {
	unsigned int id;
	glGenTextures(1, &id);
	SDL_Surface* img=SDL_LoadBMP(filename); //load the bmp image
	glBindTexture(GL_TEXTURE_2D,id);       //and use the texture, we have just generated
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); //same if the image bigger
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);      //we do it for vertically and horizontally (previous line)

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_BGR,GL_UNSIGNED_SHORT_5_5_5_1, img->pixels); //SHORT_5_6_5,img->pixels);        //we make the actual texture
	cout << img->format->BytesPerPixel << "\n";
	SDL_FreeSurface(img);   //we delete the image, we don't need it anymore
	
	return id;     //and we return the id
}


void old_loadTexture(char* fileName , int fileWidth , int fileHeight) {
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

   glBindTexture(GL_TEXTURE_2D, skyBoxFace);
   gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
                     GL_RGBA,           // internal texture storage format
                     fileWidth,             // texture width
                     fileHeight,            // texture height
                     GL_RGBA,           // pixel format
                     GL_UNSIGNED_BYTE,	// color component format
                     image);    // pointer to texture image

   glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
   glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


void displaySkybox() {
	
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D ,  skyBoxFace);
	glBegin(GL_QUADS);
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( _cornersTHREE_D[4][0] , _cornersTHREE_D[4][1] , 2*_cornersTHREE_D[4][2]);
		glTexCoord2d( 1.0 ,  0.0);
		glVertex3f( _cornersTHREE_D[5][0] , _cornersTHREE_D[5][1] , 2*_cornersTHREE_D[5][2]);
		glTexCoord2d( 1.0 ,  1.0);
		glVertex3f( _cornersTHREE_D[6][0] , _cornersTHREE_D[6][1] , 2*_cornersTHREE_D[6][2]);
		glTexCoord2d( 0.0 ,  1.0);
		glVertex3f( _cornersTHREE_D[7][0] , _cornersTHREE_D[7][1] , 2*_cornersTHREE_D[7][2]);
		glDisable(GL_TEXTURE_2D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D , 0);
	

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

}


void killSkybox() {
	glDeleteTextures(1 , &skyBoxFace);
}

void initSkybox() {
	skyBoxFace =loadTexture("skybox.bmp");
}
