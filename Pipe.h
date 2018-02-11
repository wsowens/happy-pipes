#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
#include <ctime>

#ifndef PIPE_H
#define PIPE_H

enum {DOWN, UP, RIGHT, LEFT, SIZE};

class Pipe
{
    struct Line
    {
        int x1, y1, x2, y2;
    };

private:
    SDL_Rect boundingBox = {0, 0, 900, 1200};
    SDL_Color primary;
    int width = 4;
    int increment = 4;
    int currentDirect;
    SDL_Point currentPos;
    std::vector<SDL_Point> positions;
    bool stop = false;
    std::vector<Line> lineStack;
    void wraparound();
public:
    Pipe(int direct = DOWN, SDL_Color color = {0xFF, 0, 0}, SDL_Point position = {100, 100});
    void grow();
    void change_direction(int direct);

    //accessor methods
    int get_width();
    SDL_Color get_color();
    std::vector<SDL_Point> get_positions();
    Line peek_line();
    int get_position_count();

};

#endif
