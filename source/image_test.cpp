#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static SDL_Window * window = NULL;
static SDL_Renderer * renderer = NULL;
static SDL_Surface * surface = NULL;
static SDL_Texture * texture = NULL;
static SDL_Rect rect;
static const char * filepath = "image.png";

static void render()
{
	SDL_SetRenderDrawColor(renderer,0,0,0,255); // set draw color to black
	SDL_RenderClear(renderer);// clear the frame
	SDL_RenderCopy(renderer,texture,NULL,&rect); // draw image to window
	SDL_RenderPresent(renderer); //present frame
}


int main(int argc, char * argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	surface = IMG_Load(filepath);

	rect.x = rect.y = 0;
	rect.w = surface->w;
	rect.h = surface->h;

	window = SDL_CreateWindow(
			"Dirt Cheap Image Viewer",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			rect.w, rect.h,
			0
		);

	renderer = SDL_CreateRenderer(window, -1, 0);
	texture = SDL_CreateTextureFromSurface(renderer,surface);

	bool running = true;
	SDL_Event event;
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



	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_FreeSurface(surface);

	IMG_Quit();
	SDL_Quit();

	return 0;
}
