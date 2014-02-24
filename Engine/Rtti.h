#ifndef _RTTI_H_
#define _RTTI_H_

#include "String.h"

class Rtti {
	private:
	public:
	Rtti(const char* name, const Rtti* baseType) {
		_name = String(name);
		_baseType = baseType;
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
	private:
	String _name;
	const Rtti* _baseType;
};

#endif