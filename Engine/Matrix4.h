////////////////////////////////////////////////////
// File name: Matrix4.h
////////////////////////////////////////////////////

#ifndef _MATRIX4_H_
#define _MATRIX4_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include <math.h>
#include <stdlib.h>
#include "Precision.h"

////////////////////////////////////////////////////
// Class name: Matrix4
////////////////////////////////////////////////////

class Matrix4 {
private:
	real* values;
public:
	Matrix4();
	void Identity();
	void Zero();
	void Clone(Matrix4*);
	Matrix4* operator*(Matrix4*);
	void operator*=(Matrix4*);
	Matrix4* operator+(Matrix4*);
	void operator+=(Matrix4*);
private:
	void product(Matrix4*, Matrix4*);
	void addition(Matrix4*, Matrix4*);
};

#endif