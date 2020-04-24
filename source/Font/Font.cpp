
#include <cburggie.h>
#include <string>

#ifdef WIN32
#include <sdl2.2.0.5\build\native\include\SDL.h>
#include <sdl2_ttf.v140.2.0.14\build\native\include\SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif



// ##### STATIC MEMBERS #####
bool cburggie::Font::module_initialized = false;




// ##### OBJECT MEMBERS #####

int cburggie::Font::Init()
{
	if (module_initialized || TTF_Init())
	{
		return -1;
	}

	module_initialized = true;
	return 0;
}



bool cburggie::Font::isInit()
{
	return module_initialized;
}



int cburggie::Font::Quit()
{
	if (!module_initialized)
	{
		cburggie::logger("cburggie::Font::Quit() called when not initialized");
		return -1;
	}

	TTF_Quit();
	module_initialized = false;
	return 0;
}




// ##### NON-STATIC MEMBERS #####
cburggie::Font::Font()
{
	font_height = 0;
	font_size = 0;
	font = NULL;
	renderer = NULL;
	color = { 255, 255, 255 };
}



cburggie::Font::~Font()
{

	renderer = NULL;
}



int cburggie::Font::open(cburggie::Window & window, const std::string & path, int font_size) { return open(window, path.c_str(), font_size); }
int cburggie::Font::open(cburggie::Window & window, const char * path, int font_size)
{
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}

	font = TTF_OpenFont(path.c_str(), font_size);

	if (font == NULL)
	{
		//TTF_OpenFont() failed for some reason
		renderer = NULL;
		font_height = 0;
		return -1;
	}

	renderer = window.getRenderingContext();
	this->font_size = font_size;
	font_height = TTF_FontHeight(font) + TTF_FontLineSkip(font);

	return 0;
}


int cburggie::Font::close()
{
	if (font == NULL) return -1;

	TTF_CloseFont(font);
	font = NULL;
	return 0;
}

void cburggie::Font::setColor(SDL_Color c)
{
	color = c;
}

int cburggie::Font::getHeight() const
{
	return font_height;
}


void cburggie::Font::getSize(const std::string & text, SDL_Rect* r) { getSize(text.c_str(), r); }
void cburggie::Font::getSize(const char * text, SDL_Rect* r)
{
	TTF_SizeText(font,text,&r->w,&r->h);
}


SDL_Texture * cburggie::Font::renderText(const std::string & text) const { return renderText(text.c_str()); }
SDL_Texture * cburggie::Font::renderText(const const char * text) const
{
	SDL_Surface * s = NULL;
	SDL_Texture * t = NULL;

	s = TTF_RenderText_Blended(font,text,color);
	if (s == NULL) return NULL;
	
	t = SDL_CreateTextureFromSurface(renderer,s);
	SDL_FreeSurface(s);

	return t;
}


