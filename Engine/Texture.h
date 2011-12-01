////////////////////////////////////////////////////
// File name: Texture.h
////////////////////////////////////////////////////

#ifndef _TEXTURE_H
#define _TEXTURE_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <gl\glew.h>
#include <SDL\SDL_image.h>

////////////////////////////////////////////////////
// Class name: Texture
////////////////////////////////////////////////////

using namespace std;

class Texture {
private:
public:
	Texture();
	int Initialize(const char*);
	GLuint textureID;

private:
	int loadImage(const char*);
};

#endif