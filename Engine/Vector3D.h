////////////////////////////////////////////////////
// File name: Vector3D.h
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "Precision.h"

////////////////////////////////////////////////////
// Class name: Vector3D
////////////////////////////////////////////////////

class Vector3D {
public:
	Vector3D();
	Vector3D(real, real, real);
	real x, y, z;
	Vector3D operator+(real);
	void operator+=(real);
	Vector3D operator+(Vector3D&);
	void operator+=(Vector3D&);
	Vector3D operator*(real);
	void operator*=(real);
	real operator*(Vector3D&);
	real magnitude();
	void normalize();
	void addScaledVector(Vector3D&, real);
private:
};