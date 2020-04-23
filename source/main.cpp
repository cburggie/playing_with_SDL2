#ifdef WIN32
#include <sdl2.2.0.5\build\native\include\SDL.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include <iostream>

#include <cburggie.h>

#ifdef WIN32
static const char * font_path = "c:\\windows\\fonts\\DejaVuSansMono.ttf";
#else
static const char * font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf";
#endif

/*
static SDL_Window * window = NULL;
static SDL_Renderer * renderer = NULL;
static SDL_Texture * texture = NULL;
static SDL_Rect rect;
static const SDL_Color black = { 0, 0, 0, 255 };
*/

static cburggie::Window * window = NULL;
static cburggie::Element * image = NULL;
static cburggie::Element * text = NULL;

static const char * message_text = "Hello, world!";
static const int font_size = 20;
static const Uint32 frame_delay_ms = 20;
static int dx = 2, dy = 2;

#ifdef WIN32
static const char * image_path = "";
#else
static const char * image_path = "image.png";
#endif





static void loop()
{
	if (text->getDrawY() + dy < 0 ||
			text->getDrawY() + text->getDrawHeight() + dy > window->getHeight())
	{
		dy *= -1;
	}

	if (text->getDrawX() + dx < 0 ||
			text->getDrawX() + text->getDrawWidth() + dx > window->getWidth())
	{
		dx *= -1;
	}

	text->moveDrawPosition(dy,dx);
	/*
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
	*/
}





static void render()
{
	window->clear();
	window->drawAll();
	window->present();
	/*
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,texture,NULL,&rect);
	SDL_RenderPresent(renderer);
	*/
}





static Uint32 FrameUpdateAndRenderEventID = 0;
static Uint32 UserEventPusher(Uint32 interval, void* eventID_ptr)
{
	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = *((Uint32*) eventID_ptr);
	userevent.data1 = NULL;
	userevent.data2 = NULL;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return interval;
}





int main(int argc, char * argv[])
{
	//init SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
	{
		cburggie::logger("SDL_Init() failed");
		return -1;
	}

	//create Window object
	window = new cburggie::Window();



	//init SDL2_image
	int imgflags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
	if (IMG_Init(imgflags) != imgflags)
	{
		cburggie::logger("IMG_Init() failed");
		SDL_Quit();
		return -1;
	}



	//init SDL2_ttf
	cburggie::Font::Init();
	cburggie::Font font;
	font.openFont(*window, font_path, font_size);



	//create Element object from image
	image = window->createElement();
	image->createFromImageFile(image_path);

	//set Window size to image size
	window->setSize(image->getWidth(), image->getHeight());



	//create Element object from Font and string
	text = window->createElement();
	text->createFromText(font, message_text);


	//setup a timer to create a SDL_USEREVENT regularly
	FrameUpdateAndRenderEventID = SDL_RegisterEvents(1);
	SDL_TimerID FrameUpdateAndRenderTimer = SDL_AddTimer(
				frame_delay_ms,
				UserEventPusher,
				(void*)(&FrameUpdateAndRenderEventID)
			);

	if (FrameUpdateAndRenderTimer == 0)
	{
		cburggie::logger("SDL_AddTimer() failed");
	}



	//run until SDL_QUIT, catch userevents and handle them
	SDL_Event event;
	bool running = true;
	while (running)
	{
		render();

		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				cburggie::logger("SDL_QUIT event received");
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



	//clean up and exit
	cburggie::logger("calling SDL_RemoveTimer...");
	SDL_RemoveTimer(FrameUpdateAndRenderTimer);

	cburggie::logger("calling cburggie::Window::close()...");
	text = NULL;
	image = NULL;
	window->close(); //deletes all associated elements

	cburggie::logger("deleting cburggie::Window object...");
	delete window;

	cburggie::logger("calling cburggie::Font::Quit()...");
	cburggie::Font::Quit();

	cburggie::logger("calling IMG_Quit()...");
	IMG_Quit();

	cburggie::logger("calling SDL_Quit()...");
	SDL_Quit();

	/* OLD
	cburggie::Font::Quit();
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	*/

	cburggie::logger("ending program");
	return 0;
}

