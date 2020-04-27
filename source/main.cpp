#ifdef WIN32
#include <sdl2.2.0.5\build\native\include\SDL.h>
#include <sdl2_image.v140.2.0.1\build\native\include\SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include <iostream>
#include <string>

#include <cburggie.h>
#include <EventHandler.h>

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
static const char * image_path = "E:\\Programming Projects\\playing_with_SDL2\\Debug\\image.jpg";
#else
static const char * image_path = "image.png";
#endif





static void loop()
{
	if (text->getDrawY() + dy < 0 ||
			text->getDrawY() + text->getDrawHeight() + dy > window->getHeight())
	{
		dy *= -1;
		EventHandler::PushEvent(EventHandler::event::WALL_COLLIDE);
	}

	if (text->getDrawX() + dx < 0 ||
			text->getDrawX() + text->getDrawWidth() + dx > window->getWidth())
	{
		dx *= -1;
		EventHandler::PushEvent(EventHandler::event::WALL_COLLIDE);
	}

	text->moveDrawPosition(dy,dx);
}





static void render()
{
	window->clear();
	window->drawAll();
	window->present();
}





int main(int argc, char * argv[])
{
	//init SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
	{
		cburggie::logger("SDL_Init() failed");
		return -1;
	}
	EventHandler::RegisterEvent(EventHandler::event::SDL_QUIT, [] {
		cburggie::logger("calling SDL_Quit()...");
		SDL_Quit();
	});


	//create Window object
	window = new cburggie::Window();
	EventHandler::RegisterEvent(EventHandler::event::SDL_QUIT, [] {
		cburggie::logger("calling cburggie::Window::close()...");
		window->close(); //deletes all associated elements

		cburggie::logger("deleting cburggie::Window object...");
		delete window;
	});



	//init SDL2_image
	#ifdef WIN32
	int imgflags = IMG_INIT_JPG | IMG_INIT_TIF;
	#else
	int imgflags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
	#endif
	if (IMG_Init(imgflags) != imgflags)
	{
		cburggie::logger("IMG_Init() failed");
		SDL_Quit();
		return -1;
	}
	EventHandler::RegisterEvent(EventHandler::event::SDL_QUIT, [] {
		cburggie::logger("calling IMG_Quit()...");
		IMG_Quit();
	});




	//init SDL2_ttf
	cburggie::Font::Init();
	cburggie::Font font;
	font.open(*window, cburggie::constants::font_path, font_size);
	EventHandler::RegisterEvent(EventHandler::event::SDL_QUIT, [] {
		cburggie::logger("calling cburggie::Font::Quit()...");
		cburggie::Font::Quit();
	});



	//create Element object from image
	image = window->createElement();
	image->createFromImageFile(image_path);

	//set Window size to image size
	window->setSize(image->getWidth(), image->getHeight());



	//create Element object from Font and string
	text = window->createElement();
	text->createFromText(font, message_text);

	font.close();

	EventHandler::Init();
	//setup a timer to create a SDL_USEREVENT regularly
	SDL_TimerID FrameUpdateAndRenderTimer = SDL_AddTimer(
		frame_delay_ms,
		[] (Uint32 interval, void*param) {
			EventHandler::PushEvent(EventHandler::event::FRAME_UPDATE);
			return interval;
		},
		nullptr
	);
	EventHandler::RegisterEvent(EventHandler::event::SDL_QUIT, [FrameUpdateAndRenderTimer] {
		cburggie::logger("calling SDL_RemoveTimer...");
		SDL_RemoveTimer(FrameUpdateAndRenderTimer);
	});

	EventHandler::RegisterEvent(EventHandler::event::FRAME_UPDATE, [] {
		loop();
		render();
	});

	EventHandler::RegisterEvent(EventHandler::event::WALL_COLLIDE, [] {
		std::cout << "boop\n";
	});

	EventHandler::RegisterEvent(EventHandler::event::SDL_QUIT, [](SDL_Event* e) {
		std::cout << e->quit.timestamp << "\n";
		std::cout << "quit1\n";
	});
	EventHandler::RegisterEvent(EventHandler::event::SDL_QUIT, [] {
		std::cout << "quit2\n";
	});
	render();

	EventHandler::HandleEvents();
	

	window = NULL;
	text = NULL;
	image = NULL;

	cburggie::logger("ending program");
	return 0;
}

