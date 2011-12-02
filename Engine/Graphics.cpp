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
	objects = list<Object*>();
	perspective = new Matrix4();
	modelView = new Matrix4();
	cameraView = new Matrix4();
}

int Graphics::Initialize() {
	GLenum result = 0;
	result = glewInit();
	if (result != GLEW_OK) {
		cout<<"glewInit error "<<glewGetErrorString(result)<<endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.2, 0.2, 0.2, 1.0);
	return 0;
}

void Graphics::Shutdown() {
}

int Graphics::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	list<Object*>::iterator current;
	current = objects.begin();
	while (current != objects.end()) {

		glUseProgram((*current)->shader->program);

		cameraView->Identity();
		cameraView->Camera(camera->position.x,
						   camera->position.y,
						   camera->position.z,
						   0, 0, 0, 0, 1, 0);

		modelView->Identity();

		modelView->Translate((*current)->position.x, (*current)->position.y, (*current)->position.z);

		if (!((*current)->rotationBase.x == (*current)->rotationBase.y == (*current)->rotationBase.z == 0)) {
			modelView->Rotate((*current)->rotationBase.x, (*current)->rotationBase.y, (*current)->rotationBase.z, (*current)->rotationAngle);
		}
		
		glUniformMatrix4fv(glGetUniformLocation((*current)->shader->program, "projection"), 1, GL_TRUE, perspective->values);
		glUniformMatrix4fv(glGetUniformLocation((*current)->shader->program, "modelView"), 1, GL_TRUE, modelView->values);
		glUniformMatrix4fv(glGetUniformLocation((*current)->shader->program, "camera"), 1, GL_TRUE, cameraView->values);
		glUniform3f(glGetUniformLocation((*current)->shader->program, "camVector"), -1,-1,-1);

		glBindTexture(GL_TEXTURE_2D, (*current)->texture->textureID);
		glUniform1i(glGetUniformLocation((*current)->shader->program, "texture2d"),0);
		
		glBindBuffer(GL_ARRAY_BUFFER, (*current)->model->GLData);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (char*)((*current)->model->dataCount));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (char*)((*current)->model->dataCount*2));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*current)->model->GLIndices);

		glDrawElements(GL_TRIANGLES, (*current)->model->indicesCount*3, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		current++;
	}

	return 0;
}

int Graphics::AddObject(Object* object) {
	objects.push_back(object);
	return 0;
}

int Graphics::UseCamera(Camera* c) {
	camera = c;
	return 0;
}

int Graphics::SetPerspective(real angle, real ratio, real near, real far) {
	perspective->Identity();
	perspective->Perspective(angle, ratio, near, far);
	return 0;
}