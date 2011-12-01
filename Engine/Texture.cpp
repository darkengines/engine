////////////////////////////////////////////////////
// File name: Texture.cpp
////////////////////////////////////////////////////

#include "Texture.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Texture::Texture() {}
int Texture::Initialize(const char* source) {
	loadImage(source);
	return 0;
}

int Texture::loadImage(const char* source) {


	SDL_Surface* surface;
	surface = IMG_Load(source);
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	GLenum colorFormat;
	if (surface->format->BytesPerPixel <= 24) {
		colorFormat = surface->format->Rshift > surface->format->Bshift ? GL_BGR : GL_RGB;
	} else {
		colorFormat = surface->format->Rshift > surface->format->Bshift ? GL_BGRA : GL_RGBA;
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,
				 0,
				 surface->format->BytesPerPixel,
				 surface->w, surface->h,
				 0,
				 colorFormat,
				 GL_UNSIGNED_BYTE,
				 surface->pixels
	);
	SDL_FreeSurface(surface);
	return 0;
}