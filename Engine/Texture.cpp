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
	glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_LockSurface(surface);

	int i = 0;
	/*while (i<surface->h*surface->w) {

	}*/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(surface);

	/*FILE* file;

	file = fopen(source, "rb");

	TGAHeader header;
	fread((char*)(&(header.idLength)), 1, 1, file);
	fread((char*)(&(header.colormapType)), 1, 1, file);
	fread((char*)(&(header.imageType)), 1, 1, file);
	fread((char*)(&(header.cmEntryFirst)), 2, 1, file);
	fread((char*)(&(header.cmLength)), 2, 1, file);
	fread((char*)(&(header.cmSize)), 1, 1, file);
	fread((char*)(&(header.xOrigin)), 2, 1, file);
	fread((char*)(&(header.yOrigin)), 2, 1, file);
	fread((char*)(&(header.width)), 2, 1, file);
	fread((char*)(&(header.height)), 2, 1, file);
	fread((char*)(&(header.pixelDepth)), 1, 1, file);
	fread((char*)(&(header.imageDescriptor)), 1, 1, file);

	getTextureInfo(&texture, &header);
	unsigned char* colorMap = 0;

	if (header.colormapType) {
		colorMap = (unsigned char*)malloc(header.cmLength*header.cmSize>>3);
		fread((char*)colorMap, header.cmLength*header.cmSize>>3, 1, file);
	}

	texture.data = (unsigned char*)malloc(texture.width*texture.height*texture.internalFormat);

	switch (header.imageType) {
		case (0): {
			break;
		}
		case (1): {
			readTGA8Bits(file, &texture, colorMap);
			break;
		}
		case (2): {
			switch (header.pixelDepth) {
				case (16): {
					readTGA16Bits(file, &texture);
					break;
				}
				case (24): {
					readTGA24Bits(file, &texture);
					break;
				}
				case (32): {
					readTGA32Bits(file, &texture);
					break;
				}
			}
			break;
		}
		case (3): {
			switch (header.pixelDepth) {
				case (8): {
					readTGAGray8Bits(file, &texture);
					break;
				}
				case (16): {
					readTGAGray16Bits(file, &texture);
					break;
				}
			}
			break;
		}
		case (9): {
			readTGA8BitsRLE(file, &texture, colorMap);
			break;
		}
		case (10): {
			switch (header.pixelDepth) {
				case (16): {
					readTGA16BitsRLE(file, &texture);
					break;
				}
				case (24): {
					readTGA24BitsRLE(file, &texture);
					break;
				}
				case (32): {
					readTGA32BitsRLE(file, &texture);
					break;
				}
			}
			break;
		}
		case (11): {
			switch (header.pixelDepth) {
				case (8): {
					readTGAGray8BitsRLE(file, &texture);
					break;
				}
				case (16): {
					readTGAGray16BitsRLE(file, &texture);
					break;
				}
			}
			break;
		}
	}

	if (colorMap) {
		free(colorMap);
	}
	fclose(file);*/
	return 0;
}

int Texture::getTextureInfo(GLTexture* texture, TGAHeader* header) {

	texture->width = header->width;
	texture->height = header->height;

	switch (header->imageType) {
		case (1): {// 8 bits color index
		}
		case (3): { // Greyscale 8 bits
		}
		case (9): { // 8 bits color index (RLE)
		}
		case (11): { // Greyscale 8 bits (RLE)
			if (header->pixelDepth == 8) {
				texture->format = GL_LUMINANCE;
				texture->internalFormat = 1;
			} else {
				texture->format = GL_LUMINANCE_ALPHA;
				texture->internalFormat = 2;
			}
			break;
		}
		case (2): { // BGR 16-24-32 bits
		}
		case (10): { // BGR 16-24-32 (RLE)
			if (header->pixelDepth <=24) {
				texture->format = GL_RGB;
				texture->internalFormat = 3;
			} else {
				texture->format = GL_RGBA;
				texture->internalFormat = 4;
			}
			break;
		}
	}

	return 0;
}

void Texture::readTGA24Bits(FILE* file, GLTexture* texture) {
	int i = 0;
	while (i<texture->height*texture->width) {
		fread((char*)(texture->data+i*3+2), 1, 1, file);
		fread((char*)(texture->data+i*3+1), 1, 1, file);
		fread((char*)(texture->data+i*3), 1, 1, file);
		i++;
	}
}

void Texture::readTGA32Bits(FILE* file, GLTexture* texture) {
	int i = 0;
	while (i<texture->height*texture->width) {
		fread((char*)(texture->data+i*3+2), 1, 1, file);
		fread((char*)(texture->data+i*3+1), 1, 1, file);
		fread((char*)(texture->data+i*3), 1, 1, file);
		fread((char*)(texture->data+i*3+3), 1, 1, file);
		i++;
	}
}

void Texture::readTGA16Bits(FILE* file, GLTexture* texture) {
	int i = 0;
	unsigned short color, colorRight;
	while (i<texture->height*texture->width) {

		fread((char*)(&color), 1, 1, file);
		fread((char*)(&colorRight), 1, 1, file);
		colorRight <<= 8;
		color += colorRight;

		texture->data[i*3] = ((color & 0x7C00) >> 10)<<3;
		texture->data[i*3] = ((color & 0x03E0) >> 5)<<3;
		texture->data[i*3] = ((color & 0x001F) >> 0)<<3;
		i++;
	}
}

void Texture::readTGA8Bits(FILE* file, GLTexture* texture, unsigned char* colorMap) {
	int i = 0;
	unsigned char color;
	while (i<texture->height*texture->width) {
		fread((char*)(&color), 1, 1, file);
		texture->data[i*3+2] = colorMap[color*3];
		texture->data[i*3+1] = colorMap[color*3+1];
		texture->data[i*3+0] = colorMap[color*3+2];
		i++;
	}
}

void Texture::readTGAGray8Bits(FILE* file, GLTexture* texture) {
	fread((char*)(texture->data), texture->width*texture->height, 1, file);
}

void Texture::readTGAGray16Bits(FILE* file, GLTexture* texture) {
	fread((char*)(texture->data), texture->width*texture->height*2, 1, file);
}

void Texture::readTGA24BitsRLE(FILE* file, GLTexture* texture) {
	int i = 0;
	int size;
	unsigned char rgb[3];
	unsigned char packetHeader;
	unsigned char* ptr = texture->data;

	while (ptr < texture->data + texture->width * texture->height * 3) {
		fread((char*)(&packetHeader), 1, 1, file);
		size = 1+(packetHeader & 0x7f);

		if (packetHeader & 0x80) {
			fread((char*)rgb, 3, 1, file);
			i = 0;
			while (i<size) {
				ptr[0] = rgb[2];
				ptr[1] = rgb[1];
				ptr[2] = rgb[0];
				i++;
				ptr+=3;
			}
		} else {
			while (i<size) {
				fread((char*)(ptr+2), 1, 1, file);
				fread((char*)(ptr+1), 1, 1, file);
				fread((char*)(ptr+0), 1, 1, file);
				ptr += 3;
				i++;
			}
		}
	}
}

void Texture::readTGA32BitsRLE(FILE* file, GLTexture* texture) {
	int i = 0;
	int size;
	unsigned char rgb[4];
	unsigned char packetHeader;
	unsigned char* ptr = texture->data;

	while (ptr < texture->data + texture->width * texture->height * 4) {
		fread((char*)(&packetHeader), 1, 1, file);
		size = 1+(packetHeader & 0x7f);

		if (packetHeader & 0x80) {
			fread((char*)rgb, 4, 1, file);
			i = 0;
			while (i<size) {
				ptr[0] = rgb[2];
				ptr[1] = rgb[1];
				ptr[2] = rgb[0];
				ptr[3] = rgb[3];
				i++;
				ptr+=4;
			}
		} else {
			while (i<size) {
				fread((char*)(ptr+2), 1, 1, file);
				fread((char*)(ptr+1), 1, 1, file);
				fread((char*)(ptr+0), 1, 1, file);
				fread((char*)(ptr+3), 1, 1, file);
				ptr += 4;
				i++;
			}
		}
	}
}

void Texture::readTGA16BitsRLE(FILE* file, GLTexture* texture) {
	int i = 0;
	int size;
	unsigned char color, colorRight;
	unsigned char packetHeader;
	unsigned char* ptr = texture->data;

	while (ptr < texture->data + texture->width * texture->height * 3) {
		fread((char*)(&packetHeader), 1, 1, file);
		size = 1+(packetHeader & 0x7f);

		if (packetHeader & 0x80) {
			fread((char*)color, 1, 1, file);
			fread((char*)colorRight, 1, 1, file);
			colorRight <<= 8;
			color += colorRight;
			i = 0;
			while (i<size) {
				ptr[0] = ((color & 0x7C00) >> 10) <<3;
				ptr[1] = ((color & 0x7C00) >> 5) <<3;
				ptr[2] = ((color & 0x7C00) >> 0) <<3;
				i++;
				ptr+=3;
			}
		} else {
			while (i<size) {
				fread((char*)color, 1, 1, file);
				fread((char*)colorRight, 1, 1, file);
				colorRight <<= 8;
				color += colorRight;
				ptr[0] = ((color & 0x7C00) >> 10) <<3;
				ptr[1] = ((color & 0x7C00) >> 5) <<3;
				ptr[2] = ((color & 0x7C00) >> 0) <<3;
				i++;
				ptr+=3;
				ptr += 3;
				i++;
			}
		}
	}
}

void Texture::readTGA8BitsRLE(FILE* file, GLTexture* texture, unsigned char* colorMap) {
	int i = 0;
	int size;
	unsigned char color;
	unsigned char packetHeader;
	unsigned char* ptr = texture->data;

	while (ptr < texture->data + texture->width * texture->height * 3) {
		fread((char*)(&packetHeader), 1, 1, file);
		size = 1+(packetHeader & 0x7f);

		if (packetHeader & 0x80) {
			fread((char*)&color, 1, 1, file);
			i = 0;
			while (i<size) {
				ptr[0] = colorMap[color*3+2];
				ptr[1] = colorMap[color*3+1];
				ptr[2] = colorMap[color*3];
				i++;
				ptr+=3;
			}
		} else {
			while (i<size) {
				fread((char*)&color, 1, 1, file);
				ptr[0] = colorMap[color*3+2];
				ptr[1] = colorMap[color*3+1];
				ptr[2] = colorMap[color*3];
				ptr += 3;
				i++;
			}
		}
	}
}

void Texture::readTGAGray16BitsRLE(FILE* file, GLTexture* texture) {
	int i = 0;
	int size;
	unsigned char color;
	unsigned char alpha;
	unsigned char packetHeader;
	unsigned char* ptr = texture->data;

	while (ptr < texture->data + texture->width * texture->height) {
		fread((char*)(&packetHeader), 1, 1, file);
		size = 1+(packetHeader & 0x7f);

		if (packetHeader & 0x80) {
			fread((char*)color, 1, 1, file);
			fread((char*)alpha, 1, 1, file);
			i = 0;
			while (i<size) {
				ptr[0] = color;
				ptr[1] = alpha;
				i++;
				ptr+=2;
			}
		} else {
			while (i<size) {
				fread((char*)(ptr), 1, 1, file);
				fread((char*)(ptr+1), 1, 1, file);
				ptr+=2;
				i++;
			}
		}
	}
}

void Texture::readTGAGray8BitsRLE(FILE* file, GLTexture* texture) {
	int i = 0;
	int size;
	unsigned char color;
	unsigned char packetHeader;
	unsigned char* ptr = texture->data;

	while (ptr < texture->data + texture->width * texture->height) {
		fread((char*)(&packetHeader), 1, 1, file);
		size = 1+(packetHeader & 0x7f);

		if (packetHeader & 0x80) {
			fread((char*)color, 4, 1, file);
			i = 0;
			while (i<size) {
				ptr[0] = color;
				i++;
				ptr++;
			}
		} else {
			while (i<size) {
				fread((char*)(ptr), 1, 1, file);
				ptr ++;
				i++;
			}
		}
	}
}