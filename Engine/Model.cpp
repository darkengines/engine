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

list<LoadedModel*> Model::loaded = list<LoadedModel*>();

Model::Model() {}
int Model::Initialize(const char* source, bool loadOnce) {
	if (loadOnce) {
		LoadedModel* model = 0;
		if ((model = isModelLoaded(source)) > 0) {
			indicesCount = model->model->indicesCount;
			dataCount = model->model->dataCount;
			GLData = model->model->GLData;
			GLIndices = model->model->GLIndices;
		} else {
			loadModel(source);
			registerModel(source, this);
		}
	} else {
		loadModel(source);
	}
	return 0;
}

LoadedModel* Model::isModelLoaded(const char* source) {
	LoadedModel* result = 0;
	string src = source;
	int cmp = 0;
	bool over = 0;
	list<LoadedModel*>::iterator current;
	current = loaded.begin();
	while (!over && result == 0 && current != loaded.end()) {
		cmp = src.compare((*current)->path);
		if (!cmp) {
			result = (*current);
		}
		over = cmp < 0;
		current++;
	}
	return result;
}

int Model::registerModel(const char* source, Model* model) {
	string src = source;
	LoadedModel* store = (LoadedModel*)malloc(sizeof(LoadedModel));
	store->model = model;
	store->path = (char*)malloc(strlen(source)+1);
	memcpy(store->path, source, strlen(source));
	store->path[strlen(source)] = '\0';
	int cmp = 0;
	bool over = 0;
	list<LoadedModel*>::iterator current;
	current = loaded.begin();
	while (!over && current!= loaded.end()) {
		cmp = src.compare((*current)->path);
		if (cmp <= 0) {
			loaded.insert(current, store);
			over = 1;
		}
		current++;
	}

	if (!over) {
		loaded.push_back(store);
	}

	return 0;
}

int Model::loadModel(const char* source) {
	Point *vertices, *normals, *UVs;
	vertices = normals = UVs = 0;
	unsigned int* indices = 0;
	
	unsigned verticesCount = 0;
	unsigned normalsCount = 0;
	unsigned UVsCount = 0;
	unsigned facesCount = 0;
	

	ifstream file;
	file.open(source);
	if (!file.good()) {
		cout<<source<<" open error"<<endl;
		return -1;
	}
	char input;

	file.get(input);
	while(!file.eof()) {
		if (input == 'v') {
			file.get(input);
			if (input == ' ') {
				verticesCount++;
			}
			if (input == 't') {
				UVsCount++;
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

	char foo;
	Point *verticesPoints, *texturePoints, *normalsPoints;
 	verticesPoints = (Point*)malloc(sizeof(Point)*verticesCount);
	texturePoints = (Point*)malloc(sizeof(Point)*UVsCount);
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
	UVs = (Point*)malloc(sizeof(Point)*indicesCount);
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
			UVs[k].x = texturePoints[pointsIndices[i].t].x;
			UVs[k].y = texturePoints[pointsIndices[i].t].y;
			normals[k].x = normalsPoints[pointsIndices[i].n].x;
			normals[k].y = normalsPoints[pointsIndices[i].n].y;
			normals[k].z = normalsPoints[pointsIndices[i].n].z;
			k++;
		} else {
			indices[i] = indices[j-1];
		}
		i++;
	}
	dataCount = indicesCount*sizeof(Point);
	indicesCount = facesCount*sizeof(PointIndice);
	free(verticesPoints);
	free(texturePoints);
	free(normalsPoints);
	free(pointsIndices);


	glGenBuffers(1, &GLData);
	glBindBuffer(GL_ARRAY_BUFFER, GLData);
	glBufferData(GL_ARRAY_BUFFER, dataCount*3, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataCount, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, dataCount, dataCount, normals);
	glBufferSubData(GL_ARRAY_BUFFER, dataCount*2, dataCount, UVs);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &GLIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GLIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indicesCount, indices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	free(vertices);
	free(normals);
	free(UVs);
	free(indices);

	return 0;
}