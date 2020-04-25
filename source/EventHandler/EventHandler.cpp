#ifdef WIN32
#include <sdl2.2.0.5\build\native\include\SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <cburggie.h>
#include <forward_list>
#include <array>

// private variables
namespace EventHandler {
	unsigned long eventType;
	std::array<std::forward_list<void(*) (void)>, eventCount> registeredEvents;
}

// registers callbacks to be called when event fires
bool EventHandler::RegisterEvent(event e, void (*callback)(void)) {
	registeredEvents[(signed long)e].push_front(callback);
	return true;
}

// fires a custom event
bool EventHandler::PushEvent(event e) {
	SDL_Event sdl_event;
	SDL_UserEvent sdl_userevent;

	sdl_userevent.type = eventType;
	sdl_userevent.code = (signed long)e;
	sdl_userevent.data1 = nullptr;
	sdl_userevent.data2 = nullptr;
	
	sdl_event.type = SDL_USEREVENT;
	sdl_event.user = sdl_userevent;

	SDL_PushEvent(&sdl_event);

	return true;
}

// private - handles the SDL event by calling all of our events
void EventHandler::DispatchEvent(EventHandler::event e) {
	for each (void (*callback)(void) in registeredEvents[(signed long)e])
	{
		callback();
	}
}

// init the SDL event library
bool EventHandler::Init() {
	eventType = SDL_RegisterEvents(1);
	if (eventType == 0xFFFFFFFF) {
		return false;
	}
	EventHandler::eventType = eventType;
	return true;
}

// main loop to capture events
bool EventHandler::HandleEvents() {
	bool running = true;
	while (running) {
		SDL_Event e;
		SDL_WaitEvent(&e);
		switch (e.type)
		{
		case SDL_QUIT:
			cburggie::logger("SDL_QUIT event received");
			running = false;
			break;
		case SDL_USEREVENT:
			if (e.user.type == eventType) {
				DispatchEvent((event)e.user.code);
			}
			break;
		default:
			break;
		}
	}
	return !running;
}



