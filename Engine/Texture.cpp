////////////////////////////////////////////////////
// File name: Texture.cpp
////////////////////////////////////////////////////

#include "Texture.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

list<LoadedTexture*> Texture::loaded = list<LoadedTexture*>();

Texture::Texture() {}
int Texture::Initialize(const char* source, bool loadOnce) {
	if (loadOnce) {
		LoadedTexture* texture = 0;
		if ((texture = isTextureLoaded(source))>0) {
			textureID = texture->texture->textureID;
		} else {
			loadImage(source);
			registerTexture(source, this);
		}
	} else {
		loadImage(source);
	}
	return 0;
}

LoadedTexture* Texture::isTextureLoaded(const char* source) {
	LoadedTexture* result = 0;
	string src = source;
	int cmp = 0;
	bool over = 0;
	list<LoadedTexture*>::iterator current;
	current = loaded.begin();
	while (!over && result == 0 && current != loaded.end()) {
		cmp = src.compare((*current)->path);
		if (!cmp) {
			result = (*current);
		}
		over = cmp < 0;
		current++;
	}
	return result;
}

int Texture::registerTexture(const char* source, Texture* texture) {
	string src = source;
	LoadedTexture* store = (LoadedTexture*)malloc(sizeof(LoadedTexture));
	store->texture = texture;
	store->path = (char*)malloc(strlen(source)+1);
	memcpy(store->path, source, strlen(source));
	store->path[strlen(source)] = '\0';
	int cmp = 0;
	bool over = 0;
	list<LoadedTexture*>::iterator current;
	current = loaded.begin();
	while (!over && current!= loaded.end()) {
		cmp = src.compare((*current)->path);
		if (cmp <= 0) {
			loaded.insert(current, store);
			over = 1;
		}
		current++;
	}

	if (!over) {
		loaded.push_back(store);
	}

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