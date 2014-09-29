#ifndef _RTTI_H_
#define _RTTI_H_

#include "String.h"

class Rtti {
	private:
	public:
	Rtti(const char* name, const Rtti* baseType, const int size) {
		_name = String(name);
		_baseType = baseType;
		_size = size;
	}
	~Rtti() {}
	const String& GetName() const {
		return _name;
	}
	bool IsExactly(const Rtti& type) const {
		return &type == this;
	}
	bool IsDerived(const Rtti& type) const {
		const Rtti* pSearch = this;
		while (pSearch) {
			if (pSearch == &type) return true;
			pSearch = pSearch->_baseType;
		}
		return false;
	}
	int GetSize() {
		return _size;
	}
	private:
	int _size;
	String _name;
	const Rtti* _baseType;
};

#endif