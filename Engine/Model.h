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
#include <stdlib.h>
#include "Precision.h"

////////////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////////////

typedef struct {
	real x, y, z;
} Point;

typedef struct {
	unsigned int v, t, n;
} PointIndice;

////////////////////////////////////////////////////
// Class name: Model
////////////////////////////////////////////////////

using namespace std;

class Model {
private:
public:
	Point *vertices, *UVs, *normals;
	unsigned int* indices;
	int verticesCount, indicesCount, normalsCount, facesCount, UVsCount;
	int verticesOffset, normalsOffset, UVsOffset;
	Model();
	int Initialize(const char*);
private:
	int loadModel(const char*);
	int loadCounts(const char*);
	int loadData(const char*);
};

#endif