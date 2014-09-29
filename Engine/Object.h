#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <array>
#include <hash_map>
#include <vector>
#include <list>
#include "String.h"
#include "Rtti.h"
#include "SmartPointer.h"
#include <stack>

class Controller;

class Object {
private:
	String _name;
	static unsigned int _objectCount;
	int _references;
	std::list<SmartPointer<Controller>> _controllerList;
	std::list<SmartPointer<Object>> _childs;
protected:
	unsigned int _id;
public:
	static std::hash_map<unsigned int, Object*> InUse;
	Object();
	Object(Object& from);
	~Object();
	virtual const Rtti& GetType() const;
	bool IsExactly(const Rtti& type);
	bool IsDerived(const Rtti& type);
	bool IsExactlyTypeOf(const Object* object);
	bool IsDerivedTypeOf(const Object* object);
	template<class T> T* StaticCast(Object* object);
	template<class T> const T* StaticCast(const Object* object);
	template<class T> T* DynamicCast(Object* object);
	template<class T> const T* DynamicCast(const Object* object);
	void SetName(const String& name);
	const String& GetName() const;
	unsigned int GetId() const;
	void IncrementReferences();
	void DecrementReferences();
	int GetReferences() const;
	static void PrintInUse(FILE* file, const char* message);
	//virtual Object* GetObjectByName(const String& name) = 0;
	//virtual void GetObjectsByName(const String& name, std::vector<Object*>& objects);
	static const Rtti Type;

	void SetController(const SmartPointer<Controller>& controller);

	void RemoveController(const SmartPointer<Controller>& controller);
	void RemoveAllControllers();
	virtual String ToString() = 0;
	char* Serialize();
	void AddChild(SmartPointer<Object>);
private:
	static unsigned int getNextId();
};

#include "Controller.h"

#endif