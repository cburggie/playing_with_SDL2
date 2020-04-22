#ifndef _CBURGGIE_APP_H
#define _CBURGGIE_APP_H

#include <cburggie.h>
#include <SDL2/SDL.h>

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
