#ifndef _TPOINTER_H_
#define _TPOINTER_H_

#include "Object.h"

template <class T> class TPointer {
private:

public:
	TPointer(T* object = 0) {
		_object = object;
		if (_object) {
			_object->IncrementReferences();
		}
	}
	TPointer(const TPointer& from) {
		_object = from._object;
		if (_object) {
			_object->IncrementReferences();
		}
	}
	~TPointer() {
		if (_object) {
			_object->DecrementReferences();
			_object = 0;
		}
	}

	operator T*() const {
		return _object;
	}
	T& operator*() const {
		return *_object;
	}
	T* operator->() const {
		return _object;
	}

	TPointer& operator=(T* object) {
		if (object != _object) {
			if (object) {
				object->IncrementReferences();
			}
			if (_object) {
				_object->DecrementReferences();
			}
			_object = object;
		}
		return *this;
	}
	TPointer& operator=(const TPointer& reference) {
		*this = reference._object;
		return *this;
	}
	bool operator==(T* object) const {
		return _object == object;
	}
	bool operator!=(T* object) const {
		return _object != object;
	}
	bool operator==(const TPointer& reference) const {
		return _object == reference;
	}
	bool operator!=(const TPointer& reference) const {
		return _object != reference;
	}
protected:
	T* _object;
};

#endif