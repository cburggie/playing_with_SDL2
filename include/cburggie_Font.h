#ifndef _CBURGGIE_FONTS_H
#define _CBURGGIE_FONTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace cburggie
{
	class Font
	{
		//static members
		private:
			static bool module_initialized;
			static int object_count;

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
			int openFont(SDL_Renderer *r, const char * path, int font_size = 12); //returns -1 on fail
			void setColor(SDL_Color c);
			int getHeight() const; //gets height of rendered text in pixels
			void getSize(const char* text, SDL_Rect* r);
			int getFontSize() const;
			SDL_Texture * renderText(const char * text) const;
			SDL_Texture * renderText(const std::string &text) const;
	};
}

#endif
