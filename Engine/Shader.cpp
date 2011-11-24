////////////////////////////////////////////////////
// File name: Shader.cpp
////////////////////////////////////////////////////

#include "Shader.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Shader::Shader() {

}

int Shader::Initialize(const char* vertexShaderSource, const char* pixelShaderSource, char** attributes, int attributesCount) {

	int result;
	result = loadShader(&vertexShader, vertexShaderSource, GL_VERTEX_SHADER);
	if (result < 0) {
		cout<<"loadShader error"<<endl;
		return -1;
	}
	result = loadShader(&pixelShader, pixelShaderSource, GL_FRAGMENT_SHADER);
	if (result < 0) {
		cout<<"loadShader error"<<endl;
		return -1;
	}
	result = loadProgram(&program, vertexShader, pixelShader, attributes, attributesCount);
	if (result < 0) {
		cout<<"loadProgram error"<<endl;
		return -1;
	}
	return 0;
}

int Shader::loadShader(GLuint* shader, const char* source, GLenum shaderType) {
	FILE* file = 0;
	int size = 0;
	char* shaderSource;
	*shader = glCreateShader(shaderType);
	if (!*shader) {
		cout<<"glCreateShader error "<<glGetError()<<endl;
	}
	file = fopen(source, "r");
	if (!file) {
		cout<<"Shader fopen error"<<endl;
		return -1;
	}
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	if (!size) {
		cout<<"Empty shader source"<<endl;
		return -1;
	}
	rewind(file);
	shaderSource = (char*)malloc(sizeof(char)*size+1);
	memset(shaderSource, '\0', size+1);
	if (!shaderSource) {
		cout<<"Shader malloc error"<<endl;
		return -1;
	}
	fread(shaderSource, size, 1, file);
	glShaderSource(*shader, 1, (const GLchar**)&shaderSource, 0);
	free(shaderSource);

	glCompileShader(*shader);
	GLint shaderParam;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &shaderParam);
	if (shaderParam != GL_TRUE) {
		int errorSize;
		glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &errorSize);
		char* error = (char*) malloc(errorSize+1);
		error[errorSize] = '\0';
		glGetShaderInfoLog(*shader, errorSize, &errorSize, error);
		cout<<"Shader "<<source<<" compilation error "<<error<<endl;
		free(error);
		return -1;
	}
	return 0;
}

int Shader::loadProgram(GLuint* program, GLuint vertexShader, GLuint pixelShader, char** attributes, int attributesCount) {
	*program = glCreateProgram();
	if (!*program) {
		cout<<"glCreateProgram error "<<glGetError()<<endl;
		return -1;
	}
	glAttachShader(*program, vertexShader);
	glAttachShader(*program, pixelShader);
	bindProgramAttributes(program, attributes, attributesCount);
	glLinkProgram(*program);
	GLint programParam;
	glGetProgramiv(*program, GL_LINK_STATUS, &programParam);
	if (programParam != GL_TRUE) {
		int errorSize;
		glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &errorSize);
		char* error = (char*) malloc(errorSize+1);
		error[errorSize] = '\0';
		glGetProgramInfoLog(*program, errorSize, &errorSize, error);
		cout<<"Program link error "<<error<<endl;
		free(error);
		return -1;
	}
	return 0;
}

int Shader::bindProgramAttributes(GLuint* program, char** attributes, int attributesCount) {
	int i = 0;
	while (i<attributesCount) {
		glBindAttribLocation(*program, i, attributes[i]);
		i++;
	}
	return 0;
}

void Shader::Shutdown() {
	glDeleteShader(vertexShader);
	glDeleteShader(pixelShader);
	glDeleteProgram(program);
}

void Shader::Use() {
	glUseProgram(program);
}