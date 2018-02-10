#include <SDL2/SDL.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include "WindowWrapper.h"
#include "Pipe.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 1200


WindowWrapper init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL failed to initialize: " << SDL_GetError() << std::endl;
		throw "Init failed";
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;

    return WindowWrapper("Happy-Pipes", SCREEN_WIDTH, SCREEN_HEIGHT);
}

const char pathSeparator =
#ifdef _WIN32
	'\\';
#else
	'/';
#endif


void print_directions(std::vector<int> input);
void print_rect(SDL_Rect * rect)
{
    std::cout << rect->x << " " << rect->y << " " << rect->w << " " << rect->h << std::endl;
}

void bound_rect(SDL_Rect * rect)
{
//rect->x = (x > 0) x : -1 * x;
//    rect->y = (y > 0) y : -1 * y;
}

std::string get_execution_directory(std::string input)
{
    //looking for the last seperator
    int last = -1;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == pathSeparator)
			last = i;
	}
	if (last < 0)
		return "";
    //returns the path to the separator
	return input.substr(0, last + 1);
}

void render_pipe(SDL_Renderer * renderer, Pipe pipe)
{
    std::vector<int> pipeDirections = pipe.get_directions();
    print_directions(pipeDirections);
    if (pipeDirections.size() == 0)
        return;
    std::vector<SDL_Rect*> rects;
    std::cerr << "rendering some stuff\n";
    int currentX = SCREEN_WIDTH / 2;
    int currentY = SCREEN_HEIGHT /2;
    int width = 0;
    int height = 0;

    /*
    switch (pipeDirections[0])
    {
        case DOWN:
            currentY = 0;
            currentX = pipe.get_position();
            break;
        case UP:
            currentY = SCREEN_HEIGHT;
            currentX = pipe.get_position();
            break;
        case RIGHT:
            currentY = pipe.get_position();
            currentX = 0;
            break;
        case LEFT:
            currentY = pipe.get_position();
            currentX = SCREEN_WIDTH;
    }*/

    int i = 0;
    int currentDirect = pipeDirections[i];
    while (i < pipeDirections.size())
    {

        SDL_Rect * tempRect = new SDL_Rect;
        tempRect->x = currentX;
        tempRect->y = currentY;
        tempRect->w = 1;
        tempRect->h = 1;

        //the 'thickness' of the pipe is referenced, depending on if it's horizontal / vertical
        switch (currentDirect)
        {
            case DOWN:
            case UP:
                tempRect->w = pipe.get_width();
                break;
            case LEFT:
            case RIGHT:
                tempRect->h = pipe.get_width();
                break;
        }
        //while the pipes are the same, we render only one rectangle
        while (currentDirect == pipeDirections[++i] && i < pipeDirections.size())
        {
            //note that, growing down / right, we decrease the y / x
            switch (currentDirect)
            {
                case UP:
                    tempRect->y -= pipe.get_increment();
                case DOWN:
                    tempRect->h += pipe.get_increment();
                    break;
                case LEFT:
                    tempRect->x -= pipe.get_increment();
                case RIGHT:
                    tempRect->w += pipe.get_increment();
                    break;
            }
        }
        currentX = tempRect->x;
        currentY = tempRect->y;
        rects.push_back(tempRect);
        currentDirect = pipeDirections[i];
    }

    while (rects.size() > 0)
    {
        SDL_Rect * toRender = rects.back();
        print_rect(toRender);
        rects.pop_back();
        std::cerr << "rendering a fillrect\n";
        std::cout << pipe.get_color().r << "\n";
        SDL_SetRenderDrawColor(renderer, 0xFF, pipe.get_color().g, pipe.get_color().b, 0xFF);
        SDL_RenderFillRect(renderer, toRender);
        delete toRender;
    }

}

void print_directions(std::vector<int> input)
{
    using std::cout;
    for (int i = 0; i < input.size(); i++)
    {
        switch (input[i] % SIZE)
        {
            case 0:
                cout << "DOWN, ";
                break;
            case 1:
                cout << "UP, ";
                break;
            case 2:
                cout << "RIGHT, ";
                break;
            case 3:
                cout << "LEFT, ";
                break;

        }
    }
    cout << std::endl;
}

Pipe get_random_pipe()
{
    return Pipe();
}

void render_background(SDL_Renderer * renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0xFF);
    SDL_RenderClear(renderer);
}

int main(int argc, char** args)
{
    srand(time(0));
    std::string colorFilename = get_execution_directory(args[0]) + "COLORS";
    WindowWrapper mainWindow = init();
    SDL_Renderer * mainRenderer = mainWindow.getRenderer();

    render_background(mainRenderer, {0, 0, 0});


    std::vector<Pipe> pipes;
    pipes.push_back(get_random_pipe());
    SDL_Event e;
    bool quit = false;
    bool doRender = true;
    int count = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        //if (count++ < 500)
        //{
            render_background(mainRenderer, {0, 0, 0});
            for (int i = 0; i < pipes.size(); i++)
            {
                doRender = true;
                pipes[i].grow();
                if (rand() % 10 == 0)
                    pipes[i].change_direction(rand() % 2);
                render_pipe(mainRenderer, pipes[i]);
            }
        //}


        if (doRender)
        {
            SDL_RenderPresent(mainRenderer);
            doRender = false;
        }
    }

    SDL_Delay(1000);
}
