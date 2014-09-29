#include "Object.h"

Object::Object() {
	_id = getNextId();
	InUse[_id] = this;
	_references = 0;
}
Object::Object(Object& from) {

}
Object::~Object() {
	InUse.erase(_id);
}
const Rtti& Object::GetType() const {
	return Type;
}
bool Object::IsExactly(const Rtti& type) {
	return GetType().IsExactly(type);
}
bool Object::IsDerived(const Rtti& type) {
	return GetType().IsDerived(type);
}
bool Object::IsExactlyTypeOf(const Object* object) {
	return GetType().IsExactly(object->GetType());
}
bool Object::IsDerivedTypeOf(const Object* object) {
	return GetType().IsDerived(object->GetType());
}
template<class T> T* Object::StaticCast(Object* object) {
	return (T*)object;
}
template<class T> const T* Object::StaticCast(const Object* object) {
	return (const T*)object;
}
template<class T> T* Object::DynamicCast(Object* object) {
	return object && object->IsDerived(T::Type) ? (T*)object : 0;
}
template<class T> const T* Object::DynamicCast(const Object* object) {
	return object && object->IsDerived(T::Type) ? (const T*)object : 0;
}
void Object::SetName(const String& name) {
	_name = name;
}
const String& Object::GetName() const {
	return _name;
}
unsigned int Object::GetId() const {
	return _id;
}
void Object::PrintInUse(FILE* file, const char* message) {
	fprintf(file, "%s:\n", message);
	unsigned int key = 0;
	std::hash_map<unsigned int, Object*>::iterator i, end;
	i = InUse.begin();
	end = InUse.end();
	while (i != end) {
		fprintf(file, "[id=%6u] [name=%32s]\n", i->second->_id, i->second->ToString().GetString());
		i++;
	}
}

void Object::SetController(const SmartPointer<Controller>& controller) {
	_controllerList.push_front(controller);
}

void Object::RemoveController(const SmartPointer<Controller>& controller) {
	_controllerList.remove(controller);
}
void Object::RemoveAllControllers() {
	_controllerList.clear();
}
unsigned int Object::getNextId() {
	return _objectCount++;
}
void Object::AddChild(SmartPointer<Object> child) {
	if (child != this) {
		this->_childs.push_back(child);
	}
}

unsigned int Object::_objectCount = 0;
const Rtti Object::Type("Object",0, sizeof(Object));
std::hash_map<unsigned int, Object*> Object::InUse;