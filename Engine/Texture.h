////////////////////////////////////////////////////
// File name: Texture.h
////////////////////////////////////////////////////

#ifndef _TEXTURE_H
#define _TESTURE_H_

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
// Typedefs
////////////////////////////////////////////////////

typedef struct {
	unsigned char idLength;
	unsigned char colormapType;
	unsigned char imageType;
	short cmEntryFirst;
	short cmLength;
	unsigned char cmSize;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	unsigned char pixelDepth;
	unsigned char imageDescriptor;
} TGAHeader;

typedef struct {
	unsigned int width;
	unsigned int height;
	GLenum format;
	int internalFormat;
	unsigned int id;
	unsigned char* data;
} GLTexture;

////////////////////////////////////////////////////
// Class name: Texture
////////////////////////////////////////////////////

using namespace std;

class Texture {
private:
public:
	Texture();
	int Initialize(const char*);
	GLTexture texture;
	GLuint textureID;

private:
	int loadImage(const char*);
	int getTextureInfo(GLTexture*, TGAHeader*);
	void readTGA24Bits(FILE* , GLTexture*);
	void readTGA32Bits(FILE* , GLTexture*);
	void readTGA16Bits(FILE* , GLTexture*);
	void readTGA8Bits(FILE* , GLTexture*, unsigned char*);
	void readTGAGray8Bits(FILE* , GLTexture*);
	void readTGAGray16Bits(FILE* , GLTexture*);
	void readTGA24BitsRLE(FILE* , GLTexture*);
	void readTGA32BitsRLE(FILE* , GLTexture*);
	void readTGA16BitsRLE(FILE* , GLTexture*);
	void readTGA8BitsRLE(FILE* , GLTexture*, unsigned char*);
	void readTGAGray8BitsRLE(FILE* , GLTexture*);
	void readTGAGray16BitsRLE(FILE* , GLTexture*);
};

#endif