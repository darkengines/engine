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
	graphics->SetPerspective(45.0f, 1440.0f/900.0f, 0.001, 100.0);
	return 0;
}

int System::InitializeWindow() {
	int result;
	result = SDL_Init(SDL_INIT_VIDEO);
	if (result < 0) {
		cout<<"SDL_Init error "<<SDL_GetError()<<endl;
		return -1;
	}
	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 900, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	SDL_ShowCursor(0);
	SDL_WM_GrabInput(SDL_GRAB_ON);
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
	inputs->CaptureEvents(window);
	if (graphics->Render()<0) {
		return -1;
	}
	SDL_GL_SwapWindow(window);
	return 0;
}

void Leave() {
	*done = 1;
}

void System::Run() {
	done = (int*) malloc(sizeof(int));
	*done = 0;
	bool up, down, left, right;
	up = down = left = right = 0;
	int mx, my;
	Uint32 ticks, lastTicks;
	ticks = lastTicks = 0;

	real theta = M_PI/4;
	real phi = -3*M_PI/4;

	Camera* camera = new Camera();
	camera->position.x = 10;
	camera->position.y = 10;
	camera->position.z = 10;
	camera->lookAt.x = -1;
	camera->lookAt.y = -1;
	camera->lookAt.z = -1;
	camera->vertical.x = 0.0;
	camera->vertical.y = 1.0;
	camera->vertical.z = 0.0;

	graphics->UseCamera(camera);

	real j = 0.0;

	SmartPointer<Spatial> cube = new Cube();
	graphics->AddObject(cube);

	Object::PrintInUse(stdout, "InUse");

	while (!*done) {
		ticks = SDL_GetTicks();
		if (ticks - lastTicks < 16) {
			SDL_Delay( 16 - (ticks - lastTicks));
		}
		lastTicks = SDL_GetTicks();
		
		Frame();

		while (!inputs->events.empty()) {
			events = inputs->events.front();
			inputs->events.pop();
			switch (events.type) {
			case (SDL_MOUSEBUTTONUP): {
				Cube* cube = new Cube();
				cube->position = camera->position;
				graphics->AddObject(cube);
				break;
			}
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
						case (SDLK_LEFT): {
							left = true;
							break;
						}
						case (SDLK_RIGHT): {
							right = true;
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
						case (SDLK_LEFT): {
							left = false;
							break;
						}
						case (SDLK_RIGHT): {
							right = false;
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
					
					theta += events.motion.xrel*0.001;
					phi -= events.motion.yrel*0.001;
					camera->lookAt.x = cosr(theta)*sinr(phi);
					camera->lookAt.y = cosr(phi);
					camera->lookAt.z = sinr(theta)*sinr(phi);

					break;
				}
					
				case (SDL_QUIT): {
					*done = 1;
					break;
				}
			}
		}
		if (up) {
			glm::vec3 pos;
			glm::vec3 front = camera->lookAt;
			front = glm::normalize(front);
			camera->position += front*0.1f;
		}
		if (down) {
			glm::vec3 pos;
			glm::vec3 front = camera->lookAt;
			front = glm::normalize(front);
			camera->position -= front*0.1f;
		}
		if (left) {
			glm::vec3 strafe = glm::cross(camera->lookAt,camera->vertical);
			strafe = glm::normalize(strafe);
			camera->position -= strafe*0.1f;
		}
		if (right) {
			glm::vec3 strafe = glm::cross(camera->lookAt,camera->vertical);
			strafe = glm::normalize(strafe);
			camera->position += strafe*0.1f;
		}
	}

}