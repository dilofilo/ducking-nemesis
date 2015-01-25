#ifndef SKYBOX_CPP
	#define SKYBOX_CPP
	
//Changes
//skyBoxFace is declared in inc
#include "skybox.h"
#include "screenSaver.h"

	static GLuint skyBoxFace;	// This is what contains the texture.
	extern float X_CAM 						;
	extern float Y_CAM 						;
	extern float Z_CAM 						;

unsigned int loadTexture(char* filename) {
	unsigned int id;
	glGenTextures(1, &id);
	SDL_Surface* img=SDL_LoadBMP(filename); //load the bmp image
	
	//Processing image - need the format ( RGBA , BGRA etc)
	    GLenum texture_format;
		GLint  nOfColors;
		nOfColors = img->format->BytesPerPixel;
        
        if (nOfColors == 4) {
                if (img->format->Rmask == 0x000000ff) //Magical Code from the internet
                        texture_format = GL_RGBA;
                else
                        texture_format = GL_BGRA;
        } else if (nOfColors == 3) {    // no alpha channel
                if (img->format->Rmask == 0x000000ff)
                        texture_format = GL_RGB;
                else
                        texture_format = GL_BGR;
        } else {
                printf("fake image. Expect big time texture errors.\n");
        }


	glBindTexture(GL_TEXTURE_2D,id);       //and use the texture, we have just generated
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);      
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);      
	glTexImage2D(GL_TEXTURE_2D,0,nOfColors,img->w,img->h,0,texture_format,GL_UNSIGNED_BYTE, img->pixels); //Generate the texture.
	#if defined(DEBUG) || defined(SKYBOX_DEBUG)
		cout << img->format->BytesPerPixel << "\n"; //Ensure that the format is as expected etc.
	#endif
	SDL_FreeSurface(img);   //free memory. Avoid leaks.
	
	return id;     			//return the id
}

//Fun Function
#define imgW 512
#define imgH 512
GLbyte img[imgW][imgH][4]; //RGBA
///This function can fake generate a star field. An ugly starfield, but random white lights anyway. It exploits pixel data format of .bmp files
GLuint generateTexture() {
	srand(time(NULL));
	GLuint id;
	glGenTextures(1,&id);
	for(int c=0; c< imgW; c++) {
		for(int r=0; r<imgH; r++) {
			if ( (rand()%10000) > 9995 ) {			// Tiny Chance. CHANGE HERE!!!!!!
				img[c][r][0] = 255; 				//Set it to white
				img[c][r][1] = 255; 				//Set it to white
				img[c][r][2] = 255; 				//Set it to white
			} else {
				img[c][r][0] = 0; 					//Set it to black
				img[c][r][1] = 0;					//Set it to black
				img[c][r][2] = 0;					//Set it to black
			}
			img[c][r][3] = 1.0;						//Opaque regardless

		}
	}

	//Assert : img generated;
	glBindTexture(GL_TEXTURE_2D , id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //if the texture is smaller, than the image, we get the avarege of the pixels next to it
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); //same if the image bigger
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);      
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);      

	glTexImage2D(GL_TEXTURE_2D , 0, GL_RGBA , imgW , imgH , 0 , GL_RGBA , GL_UNSIGNED_BYTE , img);

	return id;
}


//Draws faces of the cube.
	//NOTE : presently forced to draw a background because it looks cooler.
void drawFaces() {
	glBindTexture(GL_TEXTURE_2D ,  skyBoxFace);
	glBegin(GL_QUADS); 									//Front
		glTexCoord2d( 0.0 ,  0.0);
		glVertex3f( X_CAM - 1.0 , Y_CAM + -1.0 , Z_CAM - 1.0);
		glTexCoord2d( 1.0 ,  0.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + -1.0 , Z_CAM - 1.0);
		glTexCoord2d( 1.0 ,  1.0);
		glVertex3f( X_CAM + 1.0 , Y_CAM + 1.0 , Z_CAM - 1.0);
		glTexCoord2d( 0.0 ,  1.0);
		glVertex3f( X_CAM + -1.0 , Y_CAM + 1.0 , Z_CAM - 1.0);
	glEnd();
	#if defined(DEBUG) || defined(SKYBOX_DEBUG)
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
	#endif

}

//Takes care of enables and disables of openGL
void displaySkybox() {
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D ,  skyBoxFace);
	drawFaces();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}


// Initialization and memory handling
void killSkybox() {
	glDeleteTextures(1 , &skyBoxFace);
}

void initSkybox() {
	skyBoxFace = loadTexture("../rsc/starfield.bmp");
	glBindTexture(GL_TEXTURE_2D , skyBoxFace);
}

#endif