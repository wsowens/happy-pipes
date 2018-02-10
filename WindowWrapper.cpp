#include "WindowWrapper.h"


WindowWrapper::WindowWrapper(std::string name, int width, int height)
{
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	isValid = (window != NULL);
	renderer = nullptr;
}

SDL_Renderer * WindowWrapper::getRenderer()
{
	if (renderer == nullptr)
	   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	return renderer;
}

bool WindowWrapper::getIsValid()
{
    return isValid;
}

WindowWrapper::~WindowWrapper()
{
    if (window != NULL)
        SDL_DestroyWindow(window);
    window = NULL;
    if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);
	renderer = NULL;
}
