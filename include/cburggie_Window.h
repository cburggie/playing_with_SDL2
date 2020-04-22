#ifndef _CBURGGIE_WINDOW_H
#define _CBURGGIE_WINDOW_H

#include <cburggie.h>
#include <list>

namespace cburggie
{
	class Window
	{
		private:
			SDL_Window * window;
			SDL_Renderer * renderer;
			int width;  //in pixels
			int height; //in pixels
			std::list<Element*> elements;

		public:
			Window();
			~Window();
			int close();

			int addElement(Element * element);

			int setBackgroundColor(SDL_Color c);
			int clear();
			int updateAll();
			int drawAll();
			int present();

	};
}

#endif
