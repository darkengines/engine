#ifndef _REFERENCABLE_H_
#define _REFERENCABLE_H_

class Referencable {
public:
	virtual void IncrementReferences() = 0;
	virtual void DecrementReferences() = 0;
};

#endif