////////////////////////////////////////////////////
// File name: Vector.cpp
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "Vector3.h"


////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}
Vector3::Vector3(real x, real y, real z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3& Vector3::operator=(Vector3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
Vector3 Vector3::operator+(real v) {
	return Vector3(x+v, y+v, z+v);
}
void Vector3::operator+=(real v) {
	x+=v;
	y+=v;
	z+=v;
}
Vector3 Vector3::operator+(Vector3& v) {
	return Vector3(x+v.x, y+v.y, z+v.z);
}
void Vector3::operator+=(Vector3& v) {
	x+=v.x;
	y+=v.y;
	z+=v.z;
}

Vector3 Vector3::operator-(real v) {
	return Vector3(x-v, y-v, z-v);
}
void Vector3::operator-=(real v) {
	x-=v;
	y-=v;
	z-=v;
}
Vector3 Vector3::operator-(Vector3& v) {
	return Vector3(x-v.x, y-v.y, z-v.z);
}
void Vector3::operator-=(Vector3& v) {
	x-=v.x;
	y-=v.y;
	z-=v.z;
}

Vector3 Vector3::operator*(real v) {
	return Vector3(x*v, y*v, z*v);
}
void Vector3::operator*=(real v) {
	x*=v;
	y*=v;
	z*=v;
}
real Vector3::operator*(Vector3& v) {
	return x*v.x+y*v.y+z*v.z;
}
real Vector3::magnitude() {
	return sqrtr(x*x+y*y+z*z);
}
void Vector3::normalize() {
	real magnitude = this->magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}
void Vector3::addScaledVector(Vector3& v, real scale) {
	x += v.x*scale;
	y += v.y*scale;
	z += v.z*scale;
}

Vector3 Vector3::operator%(Vector3& v) {
	return Vector3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

void Vector3::operator%=(Vector3& v) {
	Vector3 temp = Vector3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
	x = temp.x;
	y = temp.y;
	z = temp.z;
}