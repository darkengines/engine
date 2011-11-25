////////////////////////////////////////////////////
// File name: Model.cpp
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "Model.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Model::Model() {}
int Model::Initialize(const char* source) {

	return 0;
}

int Model::loadModel(const char* source) {
	loadCounts(source);
	loadData(source);
	return 0;
}

int Model::loadCounts(const char* source) {
	ifstream file;
	file.open(source);
	if (!file.good()) {
		cout<<source<<" open error"<<endl;
		return -1;
	}
	verticesCount = 0;
	texturesCount = 0;
	normalsCount = 0;
	facesCount = 0;
	char input;

	file.get(input);
	while(!file.eof()) {
		if (input == 'v') {
			file.get(input);
			if (input = ' ') verticesCount++;
			if (input = 't') texturesCount++;
			if (input = 'n') normalsCount++;
		}
		if (input == 'f') {
			file.get(input);
			if (input == ' ') {
				facesCount++;
			}
		}
		while (input != '\n') file.get(input);
		file.get(input);
	}
	file.close();
	return 0;
}

int Model::loadData(const char* source) {
	ifstream file;
	file.open(source);
	if (!file.good()) {
		cout<<source<<" open error"<<endl;
		return -1;
	}
	vertices = (Vertex*)malloc(sizeof(Vertex)*verticesCount);
	textures = (Vertex*)malloc(sizeof(Vertex)*texturesCount);
	normals = (Vertex*)malloc(sizeof(Vertex)*normalsCount);
	faces = (Face*)malloc(sizeof(Face)*facesCount);

	int vertexIndex, textureIndex, normalIndex, faceIndex;
	vertexIndex = 0;
	textureIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	char input;
	file.get(input);
	while (!file.eof()) {
		if (input == 'v') {
			file.get(input);
			if (input == ' ') {
				file>>vertices[vertexIndex].x>>vertices[vertexIndex].y>>vertices[vertexIndex].z;
				vertices[vertexIndex].z *= -1;
				vertexIndex++;				
			}
			if (input == 'n') {
				file>>normals[normalIndex].x>>normals[normalIndex].y>>normals[normalIndex].z;
				normals[normalIndex].z *= -1;
				normalIndex++;				
			}
			if (input == 't') {
				file>>textures[textureIndex].x>>vertices[textureIndex].y;
				vertices[textureIndex].y = 1.0f - vertices[textureIndex].y;
				textureIndex++;				
			}			
		}
		if (input == 'f') {
			 file.get(input);
			 if (input == ' ') {
				file>>faces[faceIndex].v3>>faces[faceIndex].t3>>faces[faceIndex].n3
					>>faces[faceIndex].v2>>faces[faceIndex].t2>>faces[faceIndex].n2
					>>faces[faceIndex].v1>>faces[faceIndex].t1>>faces[faceIndex].n1;
				faceIndex++;
			 }
		}
		while (input != '\n') {
					file.get(input);
		}
		file.get(input);
	}
	file.close();
	return 0;
}