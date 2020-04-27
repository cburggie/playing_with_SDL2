#pragma once
#include <cburggie.h>
#include <forward_list>
#include <array>
#include <functional>
namespace EventHandler
{
	enum class event : signed long {
		//Built in events from https://wiki.libsdl.org/SDL_EventType
		SDL_QUIT = __COUNTER__,
		SDL_APP_TERMINATING = __COUNTER__,
		SDL_APP_LOWMEMORY = __COUNTER__,
		SDL_APP_WILLENTERBACKGROUND = __COUNTER__,
		SDL_APP_DIDENTERBACKGROUND = __COUNTER__,
		SDL_APP_WILLENTERFOREGROUND = __COUNTER__,
		SDL_APP_DIDENTERFOREGROUND = __COUNTER__,
		SDL_WINDOWEVENT = __COUNTER__,
		SDL_SYSWMEVENT = __COUNTER__,
		SDL_KEYDOWN = __COUNTER__,
		SDL_KEYUP = __COUNTER__,
		SDL_TEXTEDITING = __COUNTER__,
		SDL_TEXTINPUT = __COUNTER__,
		SDL_KEYMAPCHANGED = __COUNTER__,
		SDL_MOUSEMOTION = __COUNTER__,
		SDL_MOUSEBUTTONDOWN = __COUNTER__,
		SDL_MOUSEBUTTONUP = __COUNTER__,
		SDL_MOUSEWHEEL = __COUNTER__,
		SDL_JOYAXISMOTION = __COUNTER__,
		SDL_JOYBALLMOTION = __COUNTER__,
		SDL_JOYHATMOTION = __COUNTER__,
		SDL_JOYBUTTONDOWN = __COUNTER__,
		SDL_JOYBUTTONUP = __COUNTER__,
		SDL_JOYDEVICEADDED = __COUNTER__,
		SDL_JOYDEVICEREMOVED = __COUNTER__,
		SDL_CONTROLLERAXISMOTION = __COUNTER__,
		SDL_CONTROLLERBUTTONDOWN = __COUNTER__,
		SDL_CONTROLLERBUTTONUP = __COUNTER__,
		SDL_CONTROLLERDEVICEADDED = __COUNTER__,
		SDL_CONTROLLERDEVICEREMOVED = __COUNTER__,
		SDL_CONTROLLERDEVICEREMAPPED = __COUNTER__,
		SDL_FINGERDOWN = __COUNTER__,
		SDL_FINGERUP = __COUNTER__,
		SDL_FINGERMOTION = __COUNTER__,
		SDL_DOLLARGESTURE = __COUNTER__,
		SDL_DOLLARRECORD = __COUNTER__,
		SDL_MULTIGESTURE = __COUNTER__,
		SDL_CLIPBOARDUPDATE = __COUNTER__,
		SDL_DROPFILE = __COUNTER__,
		SDL_DROPTEXT = __COUNTER__,
		SDL_DROPBEGIN = __COUNTER__,
		SDL_DROPCOMPLETE = __COUNTER__,
		SDL_AUDIODEVICEADDED = __COUNTER__,
		SDL_AUDIODEVICEREMOVED = __COUNTER__,
		SDL_RENDER_TARGETS_RESET = __COUNTER__,
		SDL_RENDER_DEVICE_RESET = __COUNTER__,

		// Custom Events
		kjasdhfk = __COUNTER__,
		FRAME_UPDATE = __COUNTER__,
		WALL_COLLIDE = __COUNTER__,
		event1 = __COUNTER__,
		event2 = __COUNTER__,
	};
	const signed long eventCount = __COUNTER__;

	// variables
	extern unsigned long eventType;
	extern std::array<std::forward_list<std::function<void (SDL_Event *)>>, eventCount> registeredEvents;

	//functions
	bool RegisterEvent(EventHandler::event e, std::function<void (SDL_Event*)>);
	bool RegisterEvent(EventHandler::event e, std::function<void (void)>);
	//**FIXME** can we (do we need) an UnregisterEvent(...)?
	int PushEvent(EventHandler::event e);
	void DispatchEvents(EventHandler::event e, SDL_Event *eventData);
	bool Init();
	bool HandleEvents();
};

