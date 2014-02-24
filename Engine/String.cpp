#include "String.h"

String::String() {length = 0;data = 0;}

String::String(const char* pcString) {
		length = strlen(pcString);
		data = (char*)malloc(length+1);
		data[length] = '\0';
		memcpy(data, pcString, length);
}
String::String(const String& from) {
	String(from.data);
}
int String::GetMemoryUsed() const {
	return length;
}
int String::GetDiskUsed() const {
	return length+sizeof(length);
}
String& String::operator=(const String& rString) {
	length = rString.length;
	data = (char*)realloc(data, length+1);
	data[length]= '\0';
	memcpy(data, rString.data, length);
	return *this;
}
String& String::operator=(const char* pcString) {
	length = strlen(pcString);
	data = (char*)realloc(data, length+1);
	data[length]= '\0';
	memcpy(data, pcString, length);
	return *this;
}
char* String::GetString() const {
	return data;
}
bool String::operator==(const String& rString) const {
	if (rString.length == length) {
		return !strcmp(data, rString.data);
	}
	return false;
}
bool String::operator!=(const String& rString) const {
	return !this->operator==(rString);
}
String::~String() {
	if (data) {
		free(data);
	}
}