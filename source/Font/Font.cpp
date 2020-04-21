
#include <cburggie_Font.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>


// ##### STATIC MEMBERS #####
bool cburggie::Font::module_initialized = false;
int cburggie::Font::object_count = 0;



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
	if (!module_initialized || object_count > 0)
	{
		return -1;
	}

	TTF_Quit();
	return 0;
}




// ##### NON-STATIC MEMBERS #####
cburggie::Font::Font()
{
	object_count++;
	font_height = 0;
	font_size = 0;
	font = NULL;
	renderer = NULL;
	color = { 255, 255, 255 };
}



cburggie::Font::~Font()
{
	object_count--;
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}

	renderer = NULL;
}



int cburggie::Font::openFont(SDL_Renderer *r, const char * path, int font_size)
{
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}

	font = TTF_OpenFont(path, font_size);

	if (font == NULL)
	{
		//TTF_OpenFont() failed for some reason
		renderer = NULL;
		font_height = 0;
		return -1;
	}

	renderer = r;
	this->font_size = font_size;
	font_height = TTF_FontHeight(font) + TTF_FontLineSkip(font);

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


void cburggie::Font::getSize(const char* text, SDL_Rect* r)
{
	TTF_SizeText(font,text,&r->w,&r->h);
}


SDL_Texture * cburggie::Font::renderText(const char * text) const
{
	SDL_Surface * s = NULL;
	SDL_Texture * t = NULL;

	s = TTF_RenderText_Blended(font,text,color);
	if (s == NULL) return NULL;
	
	t = SDL_CreateTextureFromSurface(renderer,s);
	SDL_FreeSurface(s);

	return t;
}



SDL_Texture * cburggie::Font::renderText(const std::string &text) const
{
	return renderText(text.c_str());
}
