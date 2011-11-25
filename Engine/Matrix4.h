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
#include <stdio.h>
#include "Precision.h"
#include "Vector3.h"
#include <stack>

////////////////////////////////////////////////////
// Class name: Matrix4
////////////////////////////////////////////////////

using namespace std;

class Matrix4 {
private:
public:
	Matrix4();
	~Matrix4();
	real* values;
	void Identity();
	void Zero();
	void Clone(Matrix4*);
	Matrix4* operator*(Matrix4*);
	void operator*=(Matrix4*);
	Matrix4* operator+(Matrix4*);
	void operator+=(Matrix4*);
	void Print();
	void Translate(real, real, real);
	void Scale(real, real, real);
	void Rotate(real, real, real, real);
	void Perspective(real, real, real, real);
	void Camera(real, real, real, real, real, real, real ,real ,real);
	void Save();
	void Load();
private:
	void product(Matrix4*, Matrix4*, Matrix4*);
	void addition(Matrix4*, Matrix4*, Matrix4*);
	void push();
	void pop();
	stack<real*> matrixStack;
};

#endif