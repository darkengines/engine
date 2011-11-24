////////////////////////////////////////////////////
// File name: Inputs.h
////////////////////////////////////////////////////

#ifndef _INPUTS_H_
#define _INPUTS_H_

////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////

#include <SDL\SDL.h>
#include <iostream>

////////////////////////////////////////////////////
// Class name: Inputs
////////////////////////////////////////////////////

using namespace std;

class Inputs {
private:
	SDL_Event events;
public:
	Inputs();
	int Perform();
	void (*ptrLeave)();
private:
	int CaptureEvents();
};

#endif