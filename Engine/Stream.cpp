#include "Stream.h"

Stream::Stream() {

}

Stream::~Stream() {

}

bool Stream::Insert(Object* object) {

}
bool Stream::Remove(Object* object) {

}
void Stream::RemoveAll() {

}

int Stream::GetObjectCount() {

}
Object* Stream::GetObjectAt(int i) const {

}
bool Stream::IsTopLevel(Object* object) {

}

bool Stream::Load(char* buffer, int size) {
}
bool Stream::Save(char*& buffer, int& size) {

}

bool Stream::Load(const char* fileName) {

}
bool Stream::Save(const char* fileName) {

}

int Stream::GetMemoryUsed() const {

}
int Stream::GetDiskUsed() const {

}