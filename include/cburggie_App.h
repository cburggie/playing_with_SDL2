#ifndef _CBURGGIE_APP_H
#define _CBURGGIE_APP_H

#include <cburggie.h>



#ifdef WIN32
#include <sdl2.2.0.5\build\native\include\SDL.h>
#else
#include <SDL2/SDL.h>
#endif

namespace cburggie
{
	class App
	{
		private:
			bool Running;
			Window * window;

		protected:
			//Logger logger;

		public:
			App();
			~App();
			int OnInit();
			int OnExecute();
			int OnCleanup();

		protected:
			int OnEvent(SDL_Event * Event);
			int OnLoop();
			int OnRender();
	};
}

#endif
