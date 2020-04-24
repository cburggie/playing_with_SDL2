#ifndef _CBURGGIE_FONTS_H
#define _CBURGGIE_FONTS_H

#ifdef WIN32
#include <sdl2.2.0.5\build\native\include\SDL.h>
#include <sdl2_ttf.v140.2.0.14\build\native\include\SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <string>

namespace cburggie
{
	class Font
	{
		//static members
		private:
			static bool module_initialized;

		public:
			static int Init(); //returns -1 on fail
			static bool isInit();
			static int Quit();



		//non-static members
		private:
			int font_height;
			int font_size;
			TTF_Font* font;
			SDL_Renderer* renderer;
			SDL_Color color;

		public:
			Font();
			~Font();
			int open(Window & window, const char * path, int font_size = 12);
			int open(Window & window, const std::string & path, int font_size = 12); //returns -1 on fail
			int close();
			void setColor(SDL_Color c);
			int getHeight() const; //gets height of rendered text in pixels
			void getSize(const char * text, SDL_Rect * r);
			void getSize(const std::string & text, SDL_Rect* r);
			int getFontSize() const;
			SDL_Texture * renderText(const char * text) const;
			SDL_Texture * renderText(const std::string & text) const;
	};
}

#endif
