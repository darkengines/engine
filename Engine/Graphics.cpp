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
	glEnable(GL_DEPTH_TEST);
	return 0;
}

void Graphics::Shutdown() {
}

int Graphics::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return 0;
}