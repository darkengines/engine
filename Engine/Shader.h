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

////////////////////////////////////////////////////
// Class name: Shader
////////////////////////////////////////////////////

using namespace std;

class Shader {
private:
	GLuint vertexShader;
	GLuint pixelShader;
	//GLuint program;

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
};

#endif
