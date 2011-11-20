////////////////////////////////////////////////////
// File name: Vector.cpp
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "Vector3D.h"

Vector3D::Vector3D() {
	x = 0;
	y = 0;
	z = 0;
}
Vector3D::Vector3D(real x, real y, real z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3D Vector3D::operator+(real v) {
	return Vector3D(x+v, y+v, z+v);
}
void Vector3D::operator+=(real v) {
	x+=v;
	y+=v;
	z+=v;
}
Vector3D Vector3D::operator+(Vector3D& v) {
	return Vector3D(x+v.x, y+v.y, z+v.z);
}
void Vector3D::operator+=(Vector3D& v) {
	x+=v.x;
	y+=v.y;
	z+=v.z;
}
Vector3D Vector3D::operator*(real v) {
	return Vector3D(x*v, y*v, z*v);
}
void Vector3D::operator*=(real v) {
	x*=v;
	y*=v;
	z*=v;
}
real Vector3D::operator*(Vector3D& v) {
	return x*v.x+y*v.y+z*v.z;
}
real Vector3D::magnitude() {
	return sqrtr(x*x+y*y+z*z);
}
void Vector3D::normalize() {
	real magnitude = this->magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}
void Vector3D::addScaledVector(Vector3D& v, real scale) {
	x += v.x*scale;
	y += v.y*scale;
	z += v.z*scale;
}
