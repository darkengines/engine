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

	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window) {
		cout<<"SDL_CreateWindow error "<<SDL_GetError()<<endl;
		return -1;
	}
	//TODO: add error check
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
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
	Matrix4* camera = new Matrix4();
	camera->Identity();
	camera->Camera(2,2,2,0,0,0,0,1,0);
	Matrix4* projection = new Matrix4();
	projection->Identity();
	projection->Perspective(1.22, 1024.0/768.0, 1.0, 100.0);
	Matrix4* modelView = new Matrix4();
	Object* object = new Object();
	char* attr[] = {{"in_Vertex"},{"in_Normal"}, {"in_Texture"}};
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
	model->Initialize("Models/cube.obj");

	Texture* texture = new Texture();
	texture->Initialize("Textures/penguins.tga");

	float j = 0;
	GLuint indices, vertices;
	glGenBuffers(1, &vertices);

	glBindBuffer(GL_ARRAY_BUFFER, vertices);
	glBufferData(GL_ARRAY_BUFFER, model->indicesCount*sizeof(float)*3*3, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, model->indicesCount*3*sizeof(float), model->vertices);
	glBufferSubData(GL_ARRAY_BUFFER, model->indicesCount*3*sizeof(float), model->indicesCount*3*sizeof(float), model->normals);
	glBufferSubData(GL_ARRAY_BUFFER, model->indicesCount*3*2*sizeof(float), model->indicesCount*3*sizeof(float), model->UVs);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->facesCount*3*sizeof(unsigned int), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,model->facesCount*3*sizeof(unsigned int), model->indices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	float cam[3] = {3, 3, 3};
	Uint32 ticks, lastTicks;
	ticks = lastTicks = 0;
	while (!*done) {
		
		ticks = SDL_GetTicks();
		if (ticks - lastTicks < 17) {
			SDL_Delay( 17 - (ticks - lastTicks));
		}
		lastTicks = SDL_GetTicks();
		
		modelView->Identity();
		
		modelView->Save();
		//modelView->Translate(0.0,0.0,0.0);
		
		modelView->Rotate(0,1,0,j);
		//modelView->Rotate(1,0,0,3.14);
		//modelView->Scale(0.0002, 0.0002, 0.0002);
		
		Frame();
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "modelView"), 1, GL_TRUE, modelView->values);
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "camera"), 1, GL_TRUE, camera->values);
		glUniform3f(glGetUniformLocation(shader->program, "camVector"), -1,-1,-1);
		glBindTexture(GL_TEXTURE_2D, texture->textureID);
		glUniform1i(glGetUniformLocation(shader->program, "texture2d"),0);

		glBindBuffer(GL_ARRAY_BUFFER, vertices);

		glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT,GL_TRUE, 0,(char*)(model->indicesCount*3*sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT,GL_FALSE, 0,(char*)(model->indicesCount*3*2*sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
		glDrawElements(GL_TRIANGLES, model->facesCount*3, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		modelView->Load();
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "modelView"), 1, GL_TRUE, modelView->values);
		j+=0.01;
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
	glDeleteBuffers(1, &vertices);
	glDeleteBuffers(1, &indices);

	delete modelView;
	delete projection;
}