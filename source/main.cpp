
#include <SDL2/SDL.h>
#include <iostream>

#include <cburggie_Font.h>

static const char * font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";

static SDL_Window * window = NULL;
static SDL_Renderer * renderer = NULL;
static SDL_Texture * texture = NULL;
static SDL_Rect rect;
static const char * text = "Hello, world!";
static const int font_size = 20;
static const int window_width = 640;
static const int window_height = 400;



static void log(const char * s)
{
	std::cout << s << std::endl;
}



static void render()
{
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,texture,NULL,&rect);
	SDL_RenderPresent(renderer);
}



int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO |SDL_INIT_EVENTS) < 0)
	{
		log("SDL_Init() failed");
		return -1;
	}

	window = SDL_CreateWindow(
			"cburggie::Font test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			window_width, window_height,
			SDL_WINDOW_RESIZABLE
		);

	if (window == NULL)
	{
		log("SDL_CreateWindow() failed");
		SDL_Quit();
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == NULL)
	{
		log("SDL_CreateRenderer() failed");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	//initialize font system and create a font object
	cburggie::Font::Init();
	cburggie::Font font;


	//open font file and exit if failure
	if (font.openFont(renderer,font_path,font_size))
	{
		log("cburggie:Font::openFont() failed");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//render text to a SDL_Texture object, exit if failure
	texture = font.renderText(text);
	if (texture == NULL)
	{
		log("cburggie::Font::renderText() failed");
		cburggie::Font::Quit();
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	//setup the position rectangle for the texture
	rect.x = 0; rect.y = 0;
	font.getSize(text,&rect);

	//run while no SDL_Quit event is created
	SDL_Event event;
	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
		}

		render();
	}

	cburggie::Font::Quit();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

