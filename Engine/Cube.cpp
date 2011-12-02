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
	model->Initialize("Models/rifle.obj", true);
	texture = new Texture();
	texture->Initialize("Textures/penguins.jpg", true);
	shader = new Shader();
	char* attr[3] = {{"in_Vertex"}, {"in_Normal"}, {"in_Texture"}};
	shader->Initialize("Shaders/couleurs.vert", "Shaders/couleurs.frag", attr, 3);
}