#ifndef _STRING_H_
#define _STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class String {
private:
	int length;
	char* data;
public:
	String();
	String(const String&);
	String(const char* pcString);
	~String();
	int GetMemoryUsed() const;
	int GetDiskUsed() const;
	char* GetString() const;
	String& operator=(const String& rcString);
	String& operator=(const char* pcString);
	bool operator==(const String& rcString) const;
	bool operator!=(const String& rcString) const;
	//operator unsigned int() const;
private:
};

#endif