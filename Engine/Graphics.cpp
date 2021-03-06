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
	objects = list<SmartPointer<Spatial>>();
	perspective = glm::mat4();
	modelView = glm::mat4();
	cameraView = glm::mat4();
}

int Graphics::Initialize() {
	GLenum result = 0;
	result = glewInit();
	if (result != GLEW_OK) {
		cout << "glewInit error " << glewGetErrorString(result) << endl;
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

	list<SmartPointer<Spatial>>::iterator current;
	current = objects.begin();
	while (current != objects.end()) {

		glUseProgram((*current)->shader->program);

		cameraView = glm::lookAt(camera->position, camera->position + camera->lookAt, camera->vertical);
		float* values = glm::value_ptr(cameraView);
		modelView = glm::mat4();
		modelView = glm::translate(modelView, (*current)->position);
		modelView = glm::rotate(modelView, glm::angle((*current)->rotation), glm::axis((*current)->rotation));

		glUniformMatrix4fv(glGetUniformLocation((*current)->shader->program, "projection"), 1, GL_FALSE, glm::value_ptr(perspective));
		glUniformMatrix4fv(glGetUniformLocation((*current)->shader->program, "modelView"), 1, GL_FALSE, glm::value_ptr(modelView));
		glUniformMatrix4fv(glGetUniformLocation((*current)->shader->program, "camera"), 1, GL_FALSE, glm::value_ptr(cameraView));
		glUniform3f(glGetUniformLocation((*current)->shader->program, "camVector"), camera->lookAt.x, camera->lookAt.y, camera->lookAt.z);

		glBindTexture(GL_TEXTURE_2D, (*current)->texture->textureID);
		glUniform1i(glGetUniformLocation((*current)->shader->program, "texture2d"), 0);

		glBindBuffer(GL_ARRAY_BUFFER, (*current)->model->GLData);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, (char*)((*current)->model->dataCount * 12));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (char*)((*current)->model->dataCount * 2 * 12));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*current)->model->GLIndices);

		glDrawElements(GL_TRIANGLES, (*current)->model->indicesCount * 3, GL_UNSIGNED_INT, 0);

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

int Graphics::AddObject(SmartPointer<Spatial> object) {
	objects.push_back(object);
	return 0;
}

int Graphics::UseCamera(Camera* c) {
	camera = c;
	return 0;
}

int Graphics::SetPerspective(real angle, real ratio, real near, real far) {
	perspective = glm::perspective(angle, ratio, near, far);
	float* values = glm::value_ptr(perspective);
	return 0;
}