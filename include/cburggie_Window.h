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

			//associate an element to this window
			//the pointer is now owned by this object
			int addElement(Element * element);

			//set the background color of the window
			int setBackgroundColor(SDL_Color c);

			//draw solid color to window
			int clear();

			//call update() on all associated elements
			int updateAll();

			//draw all associated elements to this screen
			int drawAll();

			//update all changes drawn since last call to the screen
			void present();

	};
}

#endif
