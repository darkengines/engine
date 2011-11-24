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

Matrix4::~Matrix4() {
	free(this->values);
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
	product(this, matrix, result);
	return result;
}

void Matrix4::operator*=(Matrix4* matrix) {
	Matrix4* result = new Matrix4();
	product(this, matrix, result);
	this->Clone(result);
	delete result;
}

Matrix4* Matrix4::operator+(Matrix4* matrix) {
	Matrix4* result = new Matrix4();
	addition(this, matrix, result);
	return result;
}

void Matrix4::operator+=(Matrix4* matrix) {
	Matrix4* result = new Matrix4();
	addition(this, matrix, result);
	this->Clone(result);
	delete result;
}

void Matrix4::addition(Matrix4* m1, Matrix4* m2, Matrix4* m3) {
	int i = 0;
	while (i<16) {
		m3->values[i] = m1->values[i]+m2->values[i];
		i++;
	}
}

void Matrix4::product(Matrix4* m1, Matrix4* m2, Matrix4* m3) {
	int i,j,k;
	m3->Zero();
	i = 0;
	while (i<4) {
		j=0;
		while (j<4) {
			k = 0;
			while (k<4) {
				m3->values[i*4+j] += m1->values[i*4+k]*m2->values[4*k+j];
				k++;
			}
			j++;
		}
		i++;
	}
}

void Matrix4::Print() {
	int i = 0;
	while (i<16) {
		printf("%5.f", values[i]);
		if (i%4==3) printf("\n");
		i++;
	}
}