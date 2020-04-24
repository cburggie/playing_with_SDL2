#ifndef _CBURGGIE_H
#define _CBURGGIE_H
#include <string>

namespace cburggie
{
	namespace constants
	{
		extern const char * window_title;
		extern const char * font_path;
		extern const int min_window_width;
		extern const int window_width;
		extern const int min_window_height;
		extern const int window_height;
	}

	class App;
	class Font;
	class Window;
	class Element;
	class Logger;
}

#include "cburggie_App.h"
#include "cburggie_Font.h"
#include "cburggie_Window.h"
#include "cburggie_Element.h"
#include "cburggie_Logger.h"

#endif
