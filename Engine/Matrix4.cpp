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
	product(matrix, this, result);
	return result;
}

void Matrix4::operator*=(Matrix4* matrix) {
	Matrix4* result = new Matrix4();
	product(matrix, this, result);
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
				m3->values[j*4+i] += m1->values[k*4+i]*m2->values[j*4+k];
				k++;
			}
			j++;
		}
		i++;
	}
}

void Matrix4::Translate(real x, real y, real z) {
	Matrix4* translator = new Matrix4();
	translator->Identity();
	translator->values[3] = x;
	translator->values[7] = y;
	translator->values[11] = z;
	*this*=translator;
	delete translator;
}

void Matrix4::Scale(real x, real y, real z) {
	Matrix4* scalor = new Matrix4();
	scalor->values[0] = x;
	scalor->values[5] = y;
	scalor->values[10] = z;
	scalor->values[15] = 1;
	*this*=scalor;
	delete scalor;
}

void Matrix4::Rotate(real x, real y, real z, real angle) {
	Matrix4* rotator = new Matrix4();
	Vector3 base(x, y, z);
	base.normalize();
	rotator->values[0] = base.x*base.x*(1-cosr(angle))+cosr(angle);
	rotator->values[1] = base.x*base.y*(1-cosr(angle))-base.z*sinr(angle);
	rotator->values[2] = base.x*base.z*(1-cosr(angle))+base.y*sinr(angle);

	rotator->values[4] = base.x*base.y*(1-cosr(angle))+base.z*sinr(angle);
	rotator->values[5] = base.y*base.y*(1-cosr(angle))+cosr(angle);
	rotator->values[6] = base.y*base.z*(1-cosr(angle))-base.x*sinr(angle);

	rotator->values[8] = base.x*base.z*(1-cosr(angle))-base.y*sinr(angle);
	rotator->values[9] = base.y*base.z*(1-cosr(angle))+base.x*sinr(angle);
	rotator->values[10] = base.z*base.z*(1-cosr(angle))+cosr(angle);

	rotator->values[15] = 1.0;
	*this*=rotator;
	delete rotator;
}

void Matrix4::Perspective(real angle, real ratio, real near, real far) {
	Matrix4* projector = new Matrix4();
	real f = 1/tanr(angle/2);
	projector->values[0] = f/ratio;
	projector->values[5] = f;
	projector->values[10] = (near+far)/(near-far);
	projector->values[11] = (2*near*far)/(near-far);
	projector->values[14] = -1;
	*this*=projector;
	delete projector;
}

void Matrix4::Camera(real eyeX, real eyeY, real eyeZ, real centerX, real centerY, real centerZ, real upX, real upY, real upZ) {
	Vector3 axe = Vector3(upX, upY, upZ);
	Vector3 look = Vector3(centerX, centerY, centerZ);
	Vector3 normal = Vector3();
	Vector3 newAxe = Vector3();
	Matrix4*  camerator = new Matrix4();
	normal = look%axe;
	newAxe = normal%look;
	normal.normalize();
	newAxe.normalize();
	look.normalize();

	camerator->values[0] = normal.x;
	camerator->values[1] = normal.y;
	camerator->values[2] = normal.z;
	camerator->values[4] = newAxe.x;
	camerator->values[5] = newAxe.y;
	camerator->values[6] = newAxe.z;
	camerator->values[8] = -look.x;
	camerator->values[9] = -look.y;
	camerator->values[10] = -look.z;
	camerator->values[15] = 1.0;
	*this*=camerator;
	delete camerator;
	this->Translate(-eyeX, -eyeY, -eyeZ);
}

void Matrix4::Print() {
	int i = 0;
	while (i<16) {
		printf("%8.2f", values[i]);
		if (i%4==3) printf("\n");
		i++;
	}
}

void Matrix4::push() {
	real* stored = (real*)malloc(sizeof(real)*16);
	int i = 0;
	while (i<16) {
		stored[i] = values[i];
		i++;
	}
	matrixStack.push(stored);
}

void Matrix4::pop() {
	real* stored = matrixStack.top();
	int i = 0;
	while (i<16) {
		values[i] = stored[i];
		i++;
	}
	free(stored);
	matrixStack.pop();
}

void Matrix4::Save() {
	push();
}

void Matrix4::Load() {
	pop();
}