#ifndef _STREAM_H_
#define _STREAM_H_

#include "Object.h"

class Stream {
private:

public:
	Stream();
	~Stream();

	bool Insert(Object* object);
	bool Remove(Object* object);
	void RemoveAll();

	int GetObjectCount();
	Object* GetObjectAt(int i) const;
	bool IsTopLevel(Object* object);

	bool Load(char* buffer, int size);
	bool Save(char*& buffer, int& size);

	bool Load(const char* fileName);
	bool Save(const char* fileName);

	int GetMemoryUsed() const;
	int GetDiskUsed() const;
private:
};

#endif