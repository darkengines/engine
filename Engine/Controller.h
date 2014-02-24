#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#ifndef _OBJECT_H_
	#include "Object.h"	
	#define _OBJECT_H_
#endif

class Controller {
public:
	Controller();
	Controller(Controller& from);
	~Controller();
	static const Rtti Type;
	virtual const Rtti& GetType() const;
};


#endif