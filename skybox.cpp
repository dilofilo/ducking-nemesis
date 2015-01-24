#include <SDL/SDL.h>

static GLuint skyBoxFace;	

unsigned int loadTexture(char* filename) {
	unsigned int id;
	glGenTextures(1, &id);
	SDL_Surface* img=SDL_LoadBMP(filename); //load the bmp image
	
	//Processing image
	    GLenum texture_format;
		GLint  nOfColors;
		nOfColors = img->format->BytesPerPixel;
        if (nOfColors == 4)     // contains an alpha channel
        {
                if (img->format->Rmask == 0x000000ff) //Magical Code from the internet
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3)     // no alpha channel
        {
                if (img->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("warning: the image is not truecolor..  this will probably break\n");
                // this error should not go unhandled
        }



	glBindTexture(GL_TEXTURE_2D,id);       //and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);      //we do it for vertically and horizontally (previous line)

	glTexImage2D(GL_TEXTURE_2D,0,nOfColors,img->w,img->h,0,texture_format,GL_UNSIGNED_BYTE, img->pixels); //SHORT_5_6_5,img->pixels);        //we make the actual texture
	cout << img->format->BytesPerPixel << "\n";
	SDL_FreeSurface(img);   //we delete the image, we don't need it anymore
	
	return id;     //and we return the id
}


#define imgW 512
#define imgH 512
GLbyte img[imgW][imgH][4]; //RGBA
GLuint generateTexture() {
	srand(time(NULL));
	GLuint id;
	glGenTextures(1,&id);
	for(int c=0; c< imgW; c++) {
		for(int r=0; r<imgH; r++) {
			if ( (rand()%10000) > 9995 ) {
				img[c][r][0] = 255;
				img[c][r][1] = 255;
				img[c][r][2] = 255;
			} else {
				img[c][r][0] = 0;
				img[c][r][1] = 0;
				img[c][r][2] = 0;
			}
			img[c][r][3] = 1.0;

		}
	}

	//Assert : img generated;
	glBindTexture(GL_TEXTURE_2D , id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);      //we do it for vertically and horizontally (previous line)

	glTexImage2D(GL_TEXTURE_2D , 0, GL_RGBA , imgW , imgH , 0 , GL_RGBA , GL_UNSIGNED_BYTE , img);

	return id;
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

void drawFaces() {
	glBindTexture(GL_TEXTURE_2D ,  skyBoxFace);
	glBegin(GL_QUADS); //Front
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( X_CAM - 1.0 , Y_CAM + -1.0 , Z_CAM - 1.0);
		glTexCoord2d( 1.0 ,  0.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + -1.0 , Z_CAM - 1.0);
		glTexCoord2d( 1.0 ,  1.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + 1.0 , Z_CAM - 1.0);
		glTexCoord2d( 0.0 ,  1.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + 1.0 , Z_CAM - 1.0);
	glEnd();
	glBegin(GL_QUADS); //Back
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( X_CAM - 1.0 , Y_CAM + -1.0 , Z_CAM + 1.0);
		glTexCoord2d( 1.0 ,  0.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + -1.0 , Z_CAM + 1.0);
		glTexCoord2d( 1.0 ,  1.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + 1.0 , Z_CAM + 1.0);
		glTexCoord2d( 0.0 ,  1.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + 1.0 , Z_CAM + 1.0);
	glEnd();
	glBegin(GL_QUADS); //Right
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + -1.0 , Z_CAM + -1.0);
		glTexCoord2d( 1.0 ,  0.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + -1.0 , Z_CAM + 1.0);
		glTexCoord2d( 1.0 ,  1.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + 1.0 , Z_CAM + 1.0);
		glTexCoord2d( 0.0 ,  1.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + 1.0 , Z_CAM + -1.0);
	glEnd();
	glBegin(GL_QUADS); //Left
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + -1.0 , Z_CAM + 1.0);
		glTexCoord2d( 1.0 ,  0.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + -1.0 , Z_CAM + -1.0);
		glTexCoord2d( 1.0 ,  1.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + 1.0 , Z_CAM + -1.0);
		glTexCoord2d( 0.0 ,  1.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + 1.0 , Z_CAM + +1.0);
	glEnd();
	glBegin(GL_QUADS); //Botom
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + -1.0 , Z_CAM + 1.0);
		glTexCoord2d( 1.0 ,  0.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + -1.0 , Z_CAM + 1.0);
		glTexCoord2d( 1.0 ,  1.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + -1.0 , Z_CAM + -1.0);
		glTexCoord2d( 0.0 ,  1.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + -1.0 , Z_CAM + -1.0);
	glEnd();
	glBegin(GL_QUADS); //Top
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + 1.0 , Z_CAM + 1.0);
		glTexCoord2d( 1.0 ,  0.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + 1.0 , Z_CAM + 1.0);
		glTexCoord2d( 1.0 ,  1.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + 1.0 , Z_CAM + -1.0);
		glTexCoord2d( 0.0 ,  1.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + 1.0 , Z_CAM + -1.0);
	glEnd();


}

void displaySkybox() {
	
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	
	//Undoing the translation here.
	drawFaces();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

}


void killSkybox() {
	glDeleteTextures(1 , &skyBoxFace);
}

void initSkybox() {
	skyBoxFace = loadTexture("starfield.bmp");
	glBindTexture(GL_TEXTURE_2D , skyBoxFace);
}
