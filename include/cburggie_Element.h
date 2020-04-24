#ifndef _CBURGGIE_ELEMENT_H
#define _CBURGGIE_ELEMENT_H

#include <cburggie.h>
#include <string>

namespace cburggie
{
	class Element
	{
		private:
			SDL_Texture * texture;
			SDL_Renderer * renderer; //renderer texture draws to
			int height;
			int width;

		protected:
			SDL_Rect draw_rect; //position and height-width data

		public:
			Element();
			~Element();
			int close();

			int setRenderingContext(SDL_Renderer * renderer);
			int createFromImageFile(const char * path);
			int createFromImageFile(const std::string path);
			int createFromSurface(SDL_Surface * surface);
			int createFromText(Font & font, const char * text);
			int createFromText(Font & font, const std::string & text);

			int getWidth() const;
			int getHeight() const;

			int getDrawWidth() const;
			int getDrawHeight() const;
			int getDrawX() const;
			int getDrawY() const;

			int setDrawPosition(int y, int x);
			int moveDrawPosition(int dy, int dx);

			int setDrawSize(int width, int height);
			int setDrawScaleFactor(double s);

			int update();
			int draw();
	};
}

#endif
