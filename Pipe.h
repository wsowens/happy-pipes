#include <SDL2/SDL.h>
#include <vector>

#ifndef PIPE_H
#define PIPE_H

enum Direction{DOWN, UP, RIGHT, LEFT, SIZE};

class Pipe
{
private:
    int width = 4;
    int currentPos;
    int increment = 4;
    SDL_Color primary;
    int currentDirect;
    std::vector<int> directions;
public:
    Pipe(Direction direct = DOWN, SDL_Color color = {0xFF, 0, 0}, int pos = 100);
    void grow();
    void change_direction(int direct);
    int get_width();
    int get_position();
    int get_increment();
    SDL_Color get_color();
    std::vector<int> get_directions();
};

#endif
