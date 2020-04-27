#ifdef WIN32
#include <sdl2.2.0.5\build\native\include\SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <cburggie.h>
#include <forward_list>
#include <array>
#include <functional>

// private variables
namespace EventHandler {
	unsigned long eventType;
	std::array<std::forward_list<std::function<void(SDL_Event *)>>, eventCount> registeredEvents;
}

// registers callbacks to be called when event fires
// takes an optional parameter of type SDL_Event* which is the pointer to SDL's event data
bool EventHandler::RegisterEvent(event e, std::function<void(SDL_Event *eventData)> callback) {
	registeredEvents[(signed long)e].push_front(callback);
	return true;
}

bool EventHandler::RegisterEvent(event e, std::function<void(void)> callback) {
	registeredEvents[(signed long)e].push_front([callback](SDL_Event *e) { callback(); });
	return true;
}

// fires a custom event
int EventHandler::PushEvent(event e) {
	SDL_Event sdl_event;
	SDL_UserEvent sdl_userevent;

	sdl_userevent.type = eventType;
	sdl_userevent.code = (signed long)e;
	sdl_userevent.data1 = nullptr;
	sdl_userevent.data2 = nullptr;

	sdl_event.type = SDL_USEREVENT;
	sdl_event.user = sdl_userevent;

	return SDL_PushEvent(&sdl_event);
}

// private - handles the SDL event by calling all of our events
void EventHandler::DispatchEvents(EventHandler::event e, SDL_Event *eventData) {
	for each (std::function<void(SDL_Event *)>callback in registeredEvents[(signed long)e])
	{
		callback(eventData);
	}
}

// init the SDL event library
bool EventHandler::Init() {
	eventType = SDL_RegisterEvents(1);
	return (eventType != 0xFFFFFFFF);
}

// main loop to capture events
bool EventHandler::HandleEvents() {
	bool running = true;
	while (running) {
		SDL_Event e;
		SDL_WaitEvent(&e);
		switch (e.type)
		{

		//Special Handling
		case SDL_USEREVENT:
			if (e.user.type == eventType) {
				DispatchEvents((event)e.user.code, &e);
			}
			break;
		case SDL_QUIT:
			DispatchEvents(EventHandler::event::SDL_QUIT, &e);
			running = false;
			break;

		// Standard event handling
		case SDL_APP_TERMINATING:
			DispatchEvents(EventHandler::event::SDL_APP_TERMINATING, &e);
			break;
		case SDL_APP_LOWMEMORY:
			DispatchEvents(EventHandler::event::SDL_APP_LOWMEMORY, &e);
			break;
		case SDL_APP_WILLENTERBACKGROUND:
			DispatchEvents(EventHandler::event::SDL_APP_WILLENTERBACKGROUND, &e);
			break;
		case SDL_APP_DIDENTERBACKGROUND:
			DispatchEvents(EventHandler::event::SDL_APP_DIDENTERBACKGROUND, &e);
			break;
		case SDL_APP_WILLENTERFOREGROUND:
			DispatchEvents(EventHandler::event::SDL_APP_WILLENTERFOREGROUND, &e);
			break;
		case SDL_APP_DIDENTERFOREGROUND:
			DispatchEvents(EventHandler::event::SDL_APP_DIDENTERFOREGROUND, &e);
			break;
		case SDL_WINDOWEVENT:
			DispatchEvents(EventHandler::event::SDL_WINDOWEVENT, &e);
			break;
		case SDL_SYSWMEVENT:
			DispatchEvents(EventHandler::event::SDL_SYSWMEVENT, &e);
			break;
		case SDL_KEYDOWN:
			DispatchEvents(EventHandler::event::SDL_KEYDOWN, &e);
			break;
		case SDL_KEYUP:
			DispatchEvents(EventHandler::event::SDL_KEYUP, &e);
			break;
		case SDL_TEXTEDITING:
			DispatchEvents(EventHandler::event::SDL_TEXTEDITING, &e);
			break;
		case SDL_TEXTINPUT:
			DispatchEvents(EventHandler::event::SDL_TEXTINPUT, &e);
			break;
		case SDL_KEYMAPCHANGED:
			DispatchEvents(EventHandler::event::SDL_KEYMAPCHANGED, &e);
			break;
		case SDL_MOUSEMOTION:
			DispatchEvents(EventHandler::event::SDL_MOUSEMOTION, &e);
			break;
		case SDL_MOUSEBUTTONDOWN:
			DispatchEvents(EventHandler::event::SDL_MOUSEBUTTONDOWN, &e);
			break;
		case SDL_MOUSEBUTTONUP:
			DispatchEvents(EventHandler::event::SDL_MOUSEBUTTONUP, &e);
			break;
		case SDL_MOUSEWHEEL:
			DispatchEvents(EventHandler::event::SDL_MOUSEWHEEL, &e);
			break;
		case SDL_JOYAXISMOTION:
			DispatchEvents(EventHandler::event::SDL_JOYAXISMOTION, &e);
			break;
		case SDL_JOYBALLMOTION:
			DispatchEvents(EventHandler::event::SDL_JOYBALLMOTION, &e);
			break;
		case SDL_JOYHATMOTION:
			DispatchEvents(EventHandler::event::SDL_JOYHATMOTION, &e);
			break;
		case SDL_JOYBUTTONDOWN:
			DispatchEvents(EventHandler::event::SDL_JOYBUTTONDOWN, &e);
			break;
		case SDL_JOYBUTTONUP:
			DispatchEvents(EventHandler::event::SDL_JOYBUTTONUP, &e);
			break;
		case SDL_JOYDEVICEADDED:
			DispatchEvents(EventHandler::event::SDL_JOYDEVICEADDED, &e);
			break;
		case SDL_JOYDEVICEREMOVED:
			DispatchEvents(EventHandler::event::SDL_JOYDEVICEREMOVED, &e);
			break;
		case SDL_CONTROLLERAXISMOTION:
			DispatchEvents(EventHandler::event::SDL_CONTROLLERAXISMOTION, &e);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			DispatchEvents(EventHandler::event::SDL_CONTROLLERBUTTONDOWN, &e);
			break;
		case SDL_CONTROLLERBUTTONUP:
			DispatchEvents(EventHandler::event::SDL_CONTROLLERBUTTONUP, &e);
			break;
		case SDL_CONTROLLERDEVICEADDED:
			DispatchEvents(EventHandler::event::SDL_CONTROLLERDEVICEADDED, &e);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			DispatchEvents(EventHandler::event::SDL_CONTROLLERDEVICEREMOVED, &e);
			break;
		case SDL_CONTROLLERDEVICEREMAPPED:
			DispatchEvents(EventHandler::event::SDL_CONTROLLERDEVICEREMAPPED, &e);
			break;
		case SDL_FINGERDOWN:
			DispatchEvents(EventHandler::event::SDL_FINGERDOWN, &e);
			break;
		case SDL_FINGERUP:
			DispatchEvents(EventHandler::event::SDL_FINGERUP, &e);
			break;
		case SDL_FINGERMOTION:
			DispatchEvents(EventHandler::event::SDL_FINGERMOTION, &e);
			break;
		case SDL_DOLLARGESTURE:
			DispatchEvents(EventHandler::event::SDL_DOLLARGESTURE, &e);
			break;
		case SDL_DOLLARRECORD:
			DispatchEvents(EventHandler::event::SDL_DOLLARRECORD, &e);
			break;
		case SDL_MULTIGESTURE:
			DispatchEvents(EventHandler::event::SDL_MULTIGESTURE, &e);
			break;
		case SDL_CLIPBOARDUPDATE:
			DispatchEvents(EventHandler::event::SDL_CLIPBOARDUPDATE, &e);
			break;
		case SDL_DROPFILE:
			DispatchEvents(EventHandler::event::SDL_DROPFILE, &e);
			break;
		case SDL_DROPTEXT:
			DispatchEvents(EventHandler::event::SDL_DROPTEXT, &e);
			break;
		case SDL_DROPBEGIN:
			DispatchEvents(EventHandler::event::SDL_DROPBEGIN, &e);
			break;
		case SDL_DROPCOMPLETE:
			DispatchEvents(EventHandler::event::SDL_DROPCOMPLETE, &e);
			break;
		case SDL_AUDIODEVICEADDED:
			DispatchEvents(EventHandler::event::SDL_AUDIODEVICEADDED, &e);
			break;
		case SDL_AUDIODEVICEREMOVED:
			DispatchEvents(EventHandler::event::SDL_AUDIODEVICEREMOVED, &e);
			break;
		case SDL_RENDER_TARGETS_RESET:
			DispatchEvents(EventHandler::event::SDL_RENDER_TARGETS_RESET, &e);
			break;
		case SDL_RENDER_DEVICE_RESET:
			DispatchEvents(EventHandler::event::SDL_RENDER_DEVICE_RESET, &e);
			break;
		default:
			break;
		}
	}
	return !running;
}



