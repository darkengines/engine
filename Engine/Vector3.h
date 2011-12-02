////////////////////////////////////////////////////
// File name: Vector3.h
////////////////////////////////////////////////////

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "Precision.h"

////////////////////////////////////////////////////
// Class name: Vector3
////////////////////////////////////////////////////

class Vector3 {
public:
	Vector3();
	Vector3(real, real, real);
	real x, y, z;
	Vector3& operator=(Vector3&);
	Vector3 operator+(real);
	void operator+=(real);
	Vector3 operator+(Vector3&);
	void operator+=(Vector3&);
	Vector3 operator-(real);
	void operator-=(real);
	Vector3 operator-(Vector3&);
	void operator-=(Vector3&);
	Vector3 operator*(real);
	void operator*=(real);
	real operator*(Vector3&);
	Vector3 operator%(Vector3&);
	void operator%=(Vector3&);
	real magnitude();
	void normalize();
	void addScaledVector(Vector3&, real);
private:
};

#endif