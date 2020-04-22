#ifdef WIN32
#include <sdl2.2.0.5\build\native\include\SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <iostream>

#include <cburggie_Font.h>

#ifdef WIN32
static const char * font_path = "c:\\windows\\fonts\\DejaVuSansMono.ttf";
#else
static const char * font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
#endif

static SDL_Window * window = NULL;
static SDL_Renderer * renderer = NULL;
static SDL_Texture * texture = NULL;
static SDL_Rect rect;
static const char * text = "Hello, world!";
static const int font_size = 20;
static const int window_width = 640;
static const int window_height = 400;
static const Uint32 frame_delay_ms = 10; //25 fps



static void log(const char * s)
{
	std::cout << s << std::endl;
}


static void loop()
{
	static int dy = 1;
	static int dx = 1;
	if (rect.y + dy < 0 ||
			rect.y + rect.h + dy > window_height)
	{
		dy *= -1;
	}

	if (rect.x + dx < 0 ||
			rect.x + rect.w + dx > window_width)
	{
		dx *= -1;
	}
	rect.y += dy;
	rect.x += dx;
}


static void render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,texture,NULL,&rect);
	SDL_RenderPresent(renderer);
}




static Uint32 FrameUpdateAndRenderEventID = 0;
static Uint32 FrameUpdateAndRenderEventPusher(Uint32 interval, void* param)
{
	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = FrameUpdateAndRenderEventID;
	userevent.data1 = NULL;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return interval;
}



int main(int argc, char * argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
	{
		log("SDL_Init() failed");
		return -1;
	}

	window = SDL_CreateWindow(
			"cburggie::Font test",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			window_width, window_height,
			//SDL_WINDOW_RESIZABLE
			0
		);

	if (window == NULL)
	{
		log("SDL_CreateWindow() failed");
		SDL_Quit();
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer,0,0,0,255);

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


	//setup a timer to create a SDL_USEREVENT every 40ms
	FrameUpdateAndRenderEventID = SDL_RegisterEvents(1);
	SDL_TimerID FrameUpdateAndRenderTimer = SDL_AddTimer(
				frame_delay_ms,
				FrameUpdateAndRenderEventPusher,
				NULL
			);

	if (FrameUpdateAndRenderTimer == 0)
	{
		log("SDL_AddTimer() failed");
	}

	//run while no SDL_Quit event is created
	SDL_Event event;
	bool running = true;
	while (running)
	{
		render();

		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_USEREVENT:
				if (event.user.type == FrameUpdateAndRenderEventID)
				{
					loop();
					render();
				}
				break;
			default:
				break;
		}

	}

	cburggie::Font::Quit();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

