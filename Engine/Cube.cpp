////////////////////////////////////////////////////
// File name: Cube.cpp
////////////////////////////////////////////////////

#include "Cube.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Cube::Cube() {
	Object();
	model = new Model();
	model->Initialize("Models/sphere.obj", true);
	texture = new Texture();
	texture->Initialize("Textures/DSCN1637.JPG", true);
	shader = new Shader();
	char* attr[3] = {{"in_Vertex"}, {"in_Normal"}, {"in_Texture"}};
	shader->Initialize("Shaders/couleurs.vert", "Shaders/couleurs.frag", attr, 3);
}