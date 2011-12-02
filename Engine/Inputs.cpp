////////////////////////////////////////////////////
// File name: Inputs.cpp
////////////////////////////////////////////////////

#include "Inputs.h"

////////////////////////////////////////////////////
// Body
////////////////////////////////////////////////////

int filter(void* userData, SDL_Event* event) {
	if (event->type == SDL_MOUSEMOTION) return 0;
}

Inputs::Inputs() {

}

int Inputs::CaptureEvents(SDL_Window* window) {
	SDL_Event event;
	bool mouseMoved = false;
	while (SDL_PollEvent(&event)) {
		if (!mouseMoved) {
			mouseMoved = event.type == SDL_MOUSEMOTION;
		}
		events.push(event);
	}
	if( mouseMoved) {
		SDL_SetEventFilter(filter, 0);
		SDL_WarpMouseInWindow(window, 512, 384);
		SDL_SetEventFilter(0, 0);
	}
	return 0;
}

int Inputs::Perform() {
	return 0;
}

