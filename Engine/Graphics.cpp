////////////////////////////////////////////////////
// File name: Graphics.cpp
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "Graphics.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Graphics::Graphics() {

}

int Graphics::Initialize() {
	GLenum result = 0;
	result = glewInit();
	if (result != GLEW_OK) {
		cout<<"glewInit error "<<glewGetErrorString(result)<<endl;
		return -1;
	}
	return 0;
}

void Graphics::Shutdown() {
}

int Graphics::Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	float vertices[] = {-0.5, -0.5, 0.0, 0.5, 0.5, -0.5};
	float colors[] = {0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0};
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
	return 0;
}