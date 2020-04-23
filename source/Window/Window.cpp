#include <cburggie.h>
#include <list>
#include <iostream>

cburggie::Window::Window()
{
	window = NULL;
	renderer = NULL;
	width = cburggie::constants::window_width;
	height = cburggie::constants::window_height;
	SDL_CreateWindowAndRenderer(width,height,0,&window,&renderer);
	elements = std::list<Element*>();
}





cburggie::Window::~Window()
{
	cburggie::logger("calling cburggie::Window::~Window()...");
	if (window != NULL || renderer != NULL || !elements.empty())
	{
		this->close();
	}
}





int cburggie::Window::close()
{
	//destroy associated Element objects
	Element* ep = NULL;
	while (!elements.empty())
	{
		ep = elements.front();

		if (ep != NULL)
		{
			ep->close();
			delete ep;
			ep = NULL;
		}

		elements.pop_front();
	}

	//destroy SDL_Renderer object
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	//destroy SDL_Window object
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}

	return 0;
}


SDL_Renderer * cburggie::Window::getRenderingContext() { return renderer; }

int cburggie::Window::getWidth() const { return width; }
int cburggie::Window::getHeight() const { return height; }

int cburggie::Window::setSize(int w, int h)
{
	int retval = 0;
	if (w < cburggie::constants::min_window_width)
	{
		w = cburggie::constants::min_window_width;
		retval |= 1;
	}

	if (h < cburggie::constants::min_window_height)
	{
		h = cburggie::constants::min_window_height;
		retval |= 2;
	}

	SDL_SetWindowSize(window, w, h);
	SDL_GetWindowSize(window,&width,&height);
	if (width != w || height != h)
	{
		retval |= 4;
	}

	return retval;
}






int cburggie::Window::addElement(Element* element)
{
	elements.push_back(element);
	return element->setRenderingContext(renderer);
}





int cburggie::Window::setBackgroundColor(int r, int g, int b, int a)
{
	//bounds check inputs
	if (r != (r & 0xff) || g != (g & 0xff) || b != (b & 0xff) || a != (a & 0xff))
	{
		return -1;
	}

	return SDL_SetRenderDrawColor(renderer,r,g,b,a);
}





int cburggie::Window::clear()
{
	return SDL_RenderClear(renderer);
}





int cburggie::Window::updateAll()
{
	int count = 0;
	for (std::list<Element*>::iterator iter = elements.begin();
			iter != elements.end();
			++iter)
	{
		if (*iter != NULL)
		{
			(*iter)->update();
			count++;
		}
	}

	return count;
}





int cburggie::Window::drawAll()
{
	int count = 0;

	for (std::list<Element*>::iterator iter = elements.begin();
			iter != elements.end();
			++iter)
	{
		if (*iter != NULL)
		{
			(*iter)->draw();
			count++;
		}
	}

	return count;
}





void cburggie::Window::present()
{
	SDL_RenderPresent(renderer);
}



