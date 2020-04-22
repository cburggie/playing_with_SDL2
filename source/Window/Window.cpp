#include <cburggie.h>
#include <list>
#include <iostream>

cburggie::Window::Window()
{
	window = NULL;
	renderer = NULL;
	width = cburggie::constants::window_width;
	height = cburggie::constants::window_height;
	elements = std::list<Element*>();
}





cburggie::Window::~Window()
{
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
		}

		elements.pop_front();
	}

	//destroy SDL_Renderer object
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	//destroy SDL_Window object
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	return 0;
}





int cburggie::Window::addElement(Element* element)
{
	elements.push_back(element);
	return element->setRenderingContext(renderer);
}





int cburggie::Window::setBackgroundColor(SDL_Color c)
{
	return SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,c.a);
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



