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
	loadModel(source);
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
			if (input == ' ') {
				verticesCount++;
			}
			if (input == 't') {
				texturesCount++;
			}
			if (input == 'n') {
				normalsCount++;
			}
		}
		if (input == 'f') {
			file.get(input);
			if (input == ' ') {
				facesCount++;
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

int Model::loadData(const char* source) {
	ifstream file;
	file.open(source);
	if (!file.good()) {
		cout<<source<<" open error"<<endl;
		return -1;
	}

	PointIndice* pointsIndices = (PointIndice*)malloc(sizeof(PointIndice)*facesCount*3);

	queue<int> problems;

	int vertexIndex, textureIndex, normalIndex, faceIndex, index, solved;

	vertexIndex = 0;
	textureIndex = 0;
	normalIndex = 0;
	faceIndex = 0;
	solved = 0;
	index = 0;

	char input, foo;

	// FILL
	Point *verticesPoints, *texturePoints, *normalsPoints;
	verticesPoints = (Point*)malloc(sizeof(Point)*verticesCount);
	texturePoints = (Point*)malloc(sizeof(Point)*texturesCount);
	normalsPoints = (Point*)malloc(sizeof(Point)*normalsCount);
	index = 0;
	file.close();
	file.open(source);

	while (file>>input) {
		if (input == 'v') {
			file.get(input);
			if (input == ' ') {
				file>>verticesPoints[vertexIndex].x>>verticesPoints[vertexIndex].y>>verticesPoints[vertexIndex].z;
				verticesPoints[vertexIndex].z *= -1.0;
				vertexIndex++;		
			}
			if (input == 'n') {
				file>>normalsPoints[normalIndex].x>>normalsPoints[normalIndex].y>>normalsPoints[normalIndex].z;
				normalsPoints[normalIndex].z *= -1.0;
				normalIndex++;				
			}
			if (input == 't') {
				file>>texturePoints[textureIndex].x>>texturePoints[textureIndex].y;
				texturePoints[textureIndex].y = 1.0f - texturePoints[textureIndex].y;
				textureIndex++;				
			}			
		}
		if (input == 'f') {
			 file.get(input);
			 if (input == ' ') {
				 file>>pointsIndices[index+2].v>>foo>>pointsIndices[index+2].t>>foo>>pointsIndices[index+2].n;
				 pointsIndices[index+2].v--;
				 pointsIndices[index+2].t--;
				 pointsIndices[index+2].n--;
				 file>>pointsIndices[index+1].v>>foo>>pointsIndices[index+1].t>>foo>>pointsIndices[index+1].n;
				 pointsIndices[index+1].v--;
				 pointsIndices[index+1].t--;
				 pointsIndices[index+1].n--;
				 file>>pointsIndices[index].v>>foo>>pointsIndices[index].t>>foo>>pointsIndices[index].n;
				 pointsIndices[index].v--;
				 pointsIndices[index].t--;
				 pointsIndices[index].n--;
				 index+=3;
			 }
		}
	}
	file.close();
	float t = 1;
	int i = 0;
	int j = 0;
	int contains = 0;
	indicesCount = 0;
	while (i<facesCount*3) {
		j = 0;
		contains = 0;
		while (!contains && j<i) {
			contains = pointsIndices[j].v == pointsIndices[i].v
					&& pointsIndices[j].t == pointsIndices[i].t
					&& pointsIndices[j].n == pointsIndices[i].n;
			j++;
		}
		if (!contains) {
			indicesCount++;
		}
		i++;
	}

	indices = (unsigned int*)malloc(sizeof(unsigned int)*facesCount*3);
	vertices = (Point*)malloc(sizeof(Point)*indicesCount);
	textures = (Point*)malloc(sizeof(Point)*indicesCount);
	normals = (Point*)malloc(sizeof(Point)*indicesCount);

	i = 0;
	j = 0;
	int k=0;
	contains = 0;
	while (i<facesCount*3) {
		j = 0;
		contains = 0;
		while (!contains && j<i) {
			contains = pointsIndices[j].v == pointsIndices[i].v
					&& pointsIndices[j].t == pointsIndices[i].t
					&& pointsIndices[j].n == pointsIndices[i].n;
			j++;
		}
		if (!contains) {
			indices[i] = k;
			vertices[k].x = verticesPoints[pointsIndices[i].v].x;
			vertices[k].y = verticesPoints[pointsIndices[i].v].y;
			vertices[k].z = verticesPoints[pointsIndices[i].v].z;
			textures[k].x = texturePoints[pointsIndices[i].t].x;
			textures[k].y = texturePoints[pointsIndices[i].t].y;
			normals[k].x = normalsPoints[pointsIndices[i].n].x;
			normals[k].y = normalsPoints[pointsIndices[i].n].y;
			normals[k].z = normalsPoints[pointsIndices[i].n].z;
			k++;
		} else {
			indices[i] = indices[j-1];
		}
		i++;
	}
	free(verticesPoints);
	free(texturePoints);
	free(normalsPoints);
	free(pointsIndices);
	return 0;
}