////////////////////////////////////////////////////
// File name: SmartPointer.h
////////////////////////////////////////////////////

#ifndef _SMARTPOINTER_H_
#define _SMARTPOINTER_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include "ReferenceCount.h"

////////////////////////////////////////////////////
// Class name: SmartPointer
////////////////////////////////////////////////////
template <typename T>
class SmartPointer {
private:
	T* pData;
	ReferenceCount* referenceCount;
public:
	SmartPointer(): pData(0), referenceCount(0) {
		referenceCount = new ReferenceCount();
		referenceCount->AddRef();
	}
	SmartPointer(T* pValue): pData(pValue), referenceCount(0) {
		referenceCount = new ReferenceCount();
		referenceCount->AddRef();
	}
	SmartPointer(const SmartPointer<T>& from): pData(from.pData), referenceCount(from.referenceCount) {
		referenceCount->AddRef();
	}
	~SmartPointer() {
		if (!referenceCount->Release()) {
			delete pData;
			delete referenceCount;
		}
	}
	T& operator* ()
    {
        return *pData;
    }

    T* operator-> ()
    {
        return pData;
    }
    
    SmartPointer<T>& operator = (const SmartPointer<T>& sp)
    {
        // Assignment operator
        if (this != &sp) // Avoid self assignment
        {
            // Decrement the old reference count
            // if reference become zero delete the old data
            if(referenceCount->Release() == 0)
            {
                delete pData;
                delete referenceCount;
            }

            // Copy the data and reference pointer
            // and increment the reference count
            pData = sp.pData;
            referenceCount = sp.referenceCount;
            referenceCount->AddRef();
        }
        return *this;
    }

	bool operator ==(const SmartPointer<T>& sp) {
		return pData == sp.pData;
	}
	bool operator !=(const T* sp) {
		return pData != sp;
	}
};

#endif