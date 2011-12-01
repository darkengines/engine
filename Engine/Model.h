////////////////////////////////////////////////////
// File name: Model.h
////////////////////////////////////////////////////

#ifndef _MODEL_H_
#define _MODEL_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <string>
#include <stdlib.h>
#include "Precision.h"
#include <GL/glew.h>

////////////////////////////////////////////////////
// Namespaces
////////////////////////////////////////////////////

using namespace std;
class Model;

////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////

typedef struct {
	real x, y, z;
} Point;

typedef struct {
	unsigned int v, t, n;
} PointIndice;

typedef struct {
	char* path;
	Model* model;
} LoadedModel;

////////////////////////////////////////////////////
// Class name: Model
////////////////////////////////////////////////////

class Model {
private:
	static list<LoadedModel*> Model::loaded;
public:
	unsigned int GLIndices;
	unsigned int GLData;
	unsigned int indicesCount, dataCount;
	Model();
	int Initialize(const char*, bool);
private:
	int loadModel(const char*);
	LoadedModel* isModelLoaded(const char*);
	int registerModel(const char*, Model*);
};

#endif