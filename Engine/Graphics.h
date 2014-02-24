////////////////////////////////////////////////////
// File name: Graphics.h
////////////////////////////////////////////////////

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////
#include <GLM/mat4x4.hpp>
#include <GL\glew.h>
#include <iostream>
#include "Shader.h"
#include "Camera.h"
#include <glm/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include "Precision.h"
#include <list>
#include "Spatial.h"

////////////////////////////////////////////////////
// Class name: Graphics
////////////////////////////////////////////////////

using namespace std;

class Graphics {
private:
	list<SmartPointer<Spatial>> objects;
	glm::mat4 perspective;
	glm::mat4 modelView;
	glm::mat4 cameraView;
	Camera* camera;
public:
	Graphics();
	int Initialize();
	void Shutdown();
	int Render();
	int UseCamera(Camera*);
	int AddObject(SmartPointer<Spatial>);
	int SetPerspective(real, real, real, real);

private:
};

#endif