#ifndef SKYBOX_H
	#define SKYBOX_H

#include "includes.h"

unsigned int 	loadTexture(char* filename);
GLuint 			generateTexture();
void 			drawFaces();
void 			displaySkybox();
void 			killSkybox();
void 			initSkybox();

#endif