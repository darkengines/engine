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
#include <stdlib.h>
#include "Precision.h"

////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////

typedef struct {
	real x, y, z;
} Vertex;

typedef struct {
	int v1, v2, v3;
	int t1, t2, t3;
	int n1, n2, n3;
} Face;

////////////////////////////////////////////////////
// Class name: Model
////////////////////////////////////////////////////

using namespace std;

class Model {
private:
public:
	Vertex *vertices, *textures, *normals;
	int verticesCount, texturesCount, normalsCount, facesCount;
	Face* faces;
	Model();
	int Initialize(const char*);
private:
	int loadModel(const char*);
	int loadCounts(const char*);
	int loadData(const char*);
};

#endif