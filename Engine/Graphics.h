////////////////////////////////////////////////////
// File name: Graphics.h
////////////////////////////////////////////////////

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include <GL\glew.h>
#include <iostream>
#include "Shader.h"
#include "Camera.h"
#include "Matrix4.h"
#include "Precision.h"
#include <list>

////////////////////////////////////////////////////
// Class name: Graphics
////////////////////////////////////////////////////

using namespace std;

class Graphics {
private:
	list<Object*> objects;
	Matrix4* perspective;
	Matrix4* modelView;
	Matrix4* cameraView;
	Camera* camera;
public:
	Graphics();
	int Initialize();
	void Shutdown();
	int Render();
	int UseCamera(Camera*);
	int AddObject(Object*);
	int SetPerspective(real, real, real, real);

private:
};

#endif