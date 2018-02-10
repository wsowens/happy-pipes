#include <string>
#include <SDL2/SDL.h>

#ifndef WINDOWWRAPPER_H
#define WINDOWWRAPPER_H

class WindowWrapper {
    private:
		bool isValid;
        SDL_Window * window;
		SDL_Renderer * renderer;
	public:
		WindowWrapper(std::string name, int width, int height);

		SDL_Renderer * getRenderer();

		bool getIsValid();

	    ~WindowWrapper();
};

#endif
