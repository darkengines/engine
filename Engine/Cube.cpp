////////////////////////////////////////////////////
// File name: Cube.cpp
////////////////////////////////////////////////////

#include "Cube.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Cube::Cube() {
	model = new Model();
	model->Initialize("Models/dragon.mod", true);
	texture = new Texture();
	texture->Initialize("Textures/BIG.JPG", true);
	shader = new Shader();
	char* attr[3] = {{"in_Vertex"}, {"in_Normal"}, {"in_Texture"}};
	shader->Initialize("Shaders/couleurs.vert", "Shaders/couleurs.frag", attr, 3);
}

String Cube::ToString() {
	return String("Dragon");
}