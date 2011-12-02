////////////////////////////////////////////////////
// File name: System.h
////////////////////////////////////////////////////

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "Graphics.h"
#include "Inputs.h"
#include <SDL\SDL.h>
#include <GL\GL.h>
#include "Matrix4.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Cube.h"
#include "Camera.h"
#include "Object.h"

////////////////////////////////////////////////////
// Class name: System
////////////////////////////////////////////////////

using namespace std;

class System {
private:
	Graphics* graphics;
	Inputs* inputs;
	SDL_Window* window;
	SDL_Event events;
public:
	System();
	int Initialize();
	bool Start();
	void Stop();
	void Shutdown();
	int Frame();
	void Run();
private:
	int InitializeWindow();
};

#endif