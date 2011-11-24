////////////////////////////////////////////////////
// File name: Inputs.cpp
////////////////////////////////////////////////////

#include "Inputs.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

Inputs::Inputs() {

}

int Inputs::CaptureEvents() {
	return SDL_PollEvent(&events);
}

int Inputs::Perform() {
	if (CaptureEvents()) {
		switch (events.type) {
			case (SDL_KEYDOWN): {
				switch (events.key.keysym.sym) {
					case (SDLK_ESCAPE): {
						(*ptrLeave)();
						break;
					}
				}
				break;
			}
		}
	}
	return 0;
}