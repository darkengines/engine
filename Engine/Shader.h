////////////////////////////////////////////////////
// File name: Shader.h
////////////////////////////////////////////////////

#ifndef _SHADER_H_
#define _SHADER_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include <GL\glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <list>

////////////////////////////////////////////////////
// Namespace
////////////////////////////////////////////////////

using namespace std;
class Shader;

////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////

typedef struct {
	char* pixelShaderPath;
	char* vertexShaderPath;
	Shader* shader;
} LoadedShader;

////////////////////////////////////////////////////
// Class name: Shader
////////////////////////////////////////////////////

class Shader {
private:
	static list<LoadedShader*> loaded;
	GLuint vertexShader;
	GLuint pixelShader;

public:
	Shader();
	int Initialize(const char*, const char*, char**, int);
	void Use();
	void Shutdown();
	GLuint program;
private:
	int loadShader(GLuint*, const char*, GLenum);
	int loadProgram(GLuint*, GLuint, GLuint, char**, int);
	int bindProgramAttributes(GLuint*, char**, int);
	LoadedShader* isShaderLoaded(const char*, const char*);
	int registerShader(const char*, const char*, Shader*);
};

#endif
