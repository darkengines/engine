////////////////////////////////////////////////////
// File name: Matrix4.cpp
////////////////////////////////////////////////////

#include "Matrix4.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Matrix4::Matrix4() {
	values = (real*)malloc(sizeof(real)*16);
	int i = 0;
	while (i<16) {
		values[i] = 0;
		i++;
	}
}

void Matrix4::Identity() {
	values[0] = 1;
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;
	values[4] = 0;
	values[5] = 1;
	values[6] = 0;
	values[7] = 0;
	values[8] = 0;
	values[9] = 0;
	values[10] = 1;
	values[11] = 0;
	values[12] = 0;
	values[13] = 0;
	values[14] = 0;
	values[15] = 1;
}

void Matrix4::Zero() {
	int i = 0;
	while (i < 16) {
		values[i] = 0;
		i++;
	}
}

void Matrix4::Clone(Matrix4* matrix) {
	int i = 0;
	while (i<16) {
		values[i] = matrix->values[i];
		i++;
	}
}

Matrix4* Matrix4::operator*(Matrix4* matrix) {
	Matrix4* result = new Matrix4();
	result->Clone(matrix);
	product(result, matrix);
	return result;
}

void Matrix4::operator*=(Matrix4* matrix) {
	product(this, matrix);
}

Matrix4* Matrix4::operator+(Matrix4* matrix) {
	Matrix4* result = new Matrix4();
	result->Clone(matrix);
	addition(result, matrix);
	return result;
}

void Matrix4::operator+=(Matrix4* matrix) {
	addition(this, matrix);
}

void Matrix4::addition(Matrix4* m1, Matrix4* m2, Matrix) {
	int i = 0;
	while (i<16) {

		i++;
	}
}