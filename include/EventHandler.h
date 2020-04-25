#pragma once
#include <cburggie.h>
#include <forward_list>
#include <array>
namespace EventHandler
{
	enum class event : signed long {
		kjasdhfk = __COUNTER__,
		FRAME_UPDATE = __COUNTER__,
		WALL_COLLIDE = __COUNTER__,
		event1 = __COUNTER__,
		event2 = __COUNTER__,
	};
	const signed long eventCount = __COUNTER__-1;

	// variables
	extern unsigned long eventType;
	extern std::array<std::forward_list<void(*) (void)>, eventCount> registeredEvents;

	//functions
	bool RegisterEvent(EventHandler::event e, void (*callback)(void));
	bool PushEvent(EventHandler::event e);
	void DispatchEvent(EventHandler::event e);
	bool Init();
	bool HandleEvents();
};

