////////////////////////////////////////////////////
// File name: System.cpp
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "System.h"
#include <iostream>
#include <stdlib.h>

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

int* done;

System::System() {
	graphics = new Graphics();
	inputs = new Inputs();
}

int System::Initialize() {
	int result = 0;
	if (InitializeWindow() < 0) return -1;

	if (graphics->Initialize()<0) return -1;
	SDL_GL_SwapWindow(window);
	return 0;
}

int System::InitializeWindow() {
	int result;

	result = SDL_Init(SDL_INIT_VIDEO);
	if (result < 0) {
		cout<<"SDL_Init error "<<SDL_GetError()<<endl;
		return -1;
	}

	window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window) {
		cout<<"SDL_CreateWindow error "<<SDL_GetError()<<endl;
		return -1;
	}
	//TODO: add error check
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetSwapInterval(1);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (!glContext) return -1;
	return 0;
}

void System::Shutdown() {
	if (graphics) {
		graphics->Shutdown();
		delete graphics;
		graphics = 0;
	}
	if (window) {
		SDL_GL_DeleteContext(window);
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

int System::Frame() {
	inputs->Perform();
	if (graphics->Render()<0) {
		return -1;
	}
	//SDL_GL_SwapWindow(window);
	return 0;
}

void Leave() {
	*done = 1;
}

void System::Run() {
	done = (int*) malloc(sizeof(int));
	*done = 0;
	inputs->ptrLeave = Leave;
	Shader* shader = new Shader();
	Matrix4* projection = new Matrix4();
	projection->Identity();
	projection->Perspective(1.22, 800.0/600.0, 0.0, 100.0);
	Matrix4* modelView = new Matrix4();
	char* attr[] = {{"in_Vertex"},{"in_Color"}};
	shader->Initialize("Shaders/couleurs.vert", "Shaders/couleurs.frag", attr, 2);
	shader->Use();
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "projection"), 1, GL_TRUE, projection->values);
	float vx[] = {0,0,0,1,0,0};
	float cx[] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};
	float vy[] = {0,0,0,0,1,0};
	float cy[] = {0.0, 1.0, 0.0, 0.0, 1.0, 0.0};
	float vz[] = {0,0,0,0,0,1};
	float cz[] = {0.0, 0.0, 1.0, 0.0, 0.0, 1.0};
	Model* model = new Model();
	model->Initialize("model.obj");
	float i = 0;
	while (!*done) {
		
		SDL_Delay(16.6);
		Frame();
		modelView->Identity();
		
		modelView->Camera(3,3,3,0,0,0,0,1,0);
		modelView->Save();
		modelView->Translate(1.0,1.0,1.0);
		modelView->Rotate(0,1,0,i);
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "modelView"), 1, GL_TRUE, modelView->values);
		/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, colors);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);*/

		i+=0.01;
		
		modelView->Load();
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "modelView"), 1, GL_TRUE, modelView->values);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vx);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, cx);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_LINES, 0, 3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vy);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, cy);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_LINES, 0, 3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vz);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, cz);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_LINES, 0, 3);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		
		

		SDL_GL_SwapWindow(window);

	}
	delete modelView;
	delete projection;
}