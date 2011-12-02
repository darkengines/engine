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
	//SDL_ShowCursor(0);
	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_INPUT_GRABBED);
	
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
	inputs->CaptureEvents();
	SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	SDL_WarpMouseInWindow(window, 1024/2, 768/2); //center that bitch
	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
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
	camera->Camera(5,5,5,0,0,0,0,1,0);
	camera->Save();
	Matrix4* projection = new Matrix4();
	projection->Identity();
	projection->Perspective(1.22, 1024.0/768.0, 0.001, 100.0);
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
	model->Initialize("Models/cube.obj", true);

	Model* model2 = new Model();
	model2->Initialize("Models/sphere.obj", true);

	Texture* texture = new Texture();
	texture->Initialize("Textures/penguins.tga", true);
	Texture* texture2 = new Texture();
	texture2->Initialize("Textures/penguins.tga", true);

	float j = 0;

	float cam[3] = {3, 3, 3};
	Uint32 ticks, lastTicks;
	ticks = lastTicks = 0;
	modelView->Identity();
	modelView->Save();
	bool up, down;
		up = down = 0;
	while (!*done) {
		
		ticks = SDL_GetTicks();
		if (ticks - lastTicks < 16) {
			SDL_Delay( 16 - (ticks - lastTicks));
		}
		lastTicks = SDL_GetTicks();
		
		/*camera->Load();
		camera->Save();*/

		

		while (!inputs->events.empty()) {
			events = inputs->events.front();
			inputs->events.pop();
			switch (events.type) {
				case (SDL_KEYDOWN): {
					switch (events.key.keysym.sym) {
						case (SDLK_UP): {
							up = true;
							break;
						}
						case (SDLK_DOWN): {
							down = true;
							break;
						}
					}
					break;
				}
				case (SDL_KEYUP): {
					switch (events.key.keysym.sym) {
						case (SDLK_UP): {
							up = false;
							break;
						}
						case (SDLK_DOWN): {
							down = false;
							break;
						}
						case (SDLK_ESCAPE): {
							*done = true;
							break;
						}
					}
					break;
				}
				case (SDL_MOUSEMOTION): {
					cout<<events.motion.x<<", "<<events.motion.y<<endl;
					cout<<events.motion.xrel<<", "<<events.motion.yrel<<endl;
					break;
				}
				case (SDL_QUIT): {
					*done = 1;
				}
			}
		}

		if (up) {
			cout<<"UP"<<endl;
			camera->Translate(0.1,0.1,0.1);
		}
		if (down) {
			cout<<"DOWN"<<endl;
			camera->Translate(-0.1,-0.1,-0.1);
		}

		modelView->Load();
		modelView->Save();
		
		//modelView->Translate(0.0,0.0,0.0);
		
		//modelView->Rotate(0,1,0,j);
		//modelView->Rotate(1,0,0,3.14);
		modelView->Scale(0.5, 0.5, 0.5);
		
		Frame();
		
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "modelView"), 1, GL_TRUE, modelView->values);
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "camera"), 1, GL_TRUE, camera->values);
		glUniform3f(glGetUniformLocation(shader->program, "camVector"), -1,-1,-1);
		glBindTexture(GL_TEXTURE_2D, texture->textureID);
		glUniform1i(glGetUniformLocation(shader->program, "texture2d"),0);

		glBindBuffer(GL_ARRAY_BUFFER, model->GLData);

		glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT,GL_TRUE, 0,(char*)model->dataCount);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT,GL_FALSE, 0,(char*)(model->dataCount*2));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->GLIndices);
		glDrawElements(GL_TRIANGLES, model->indicesCount, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(model->GLIndices);
		glDisableVertexAttribArray(model->GLData);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		modelView->Load();
		modelView->Save();

		//modelView->Rotate(1,1,1,j);
		modelView->Translate(3, 0, 0);
		//modelView->Scale(0.5, 0.5, 0.5);
		
		glBindTexture(GL_TEXTURE_2D, texture2->textureID);
		glUniform1i(glGetUniformLocation(shader->program, "texture2d"),0);

		glUniformMatrix4fv(glGetUniformLocation(shader->program, "modelView"), 1, GL_TRUE, modelView->values);
		glBindBuffer(GL_ARRAY_BUFFER, model2->GLData);

		glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT,GL_TRUE, 0,(char*)(model2->dataCount));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT,GL_FALSE, 0,(char*)(model2->dataCount*2));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model2->GLIndices);
		glDrawElements(GL_TRIANGLES, model2->indicesCount, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(model2->GLIndices);
		glDisableVertexAttribArray(model2->GLData);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		modelView->Load();
		modelView->Save();
		glUniformMatrix4fv(glGetUniformLocation(shader->program, "modelView"), 1, GL_TRUE, modelView->values);
		j+=0.02;
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