#include "Pipe.h"
#include <iostream>

Pipe::Pipe(Direction direct, SDL_Color color, int pos)
{
    primary = color;
    currentDirect = direct;
    currentPos = 100;
}

void Pipe::grow()
{
    directions.push_back(currentDirect);
    //std::cerr << "growing pipe\n";
}

void Pipe::change_direction(int direct)
{
    currentDirect = (2 + (currentDirect / 2) * 2) % SIZE + (direct % 2);
    //std::cerr << "changing direction\n";
}

SDL_Color Pipe::get_color()
{
    return primary;
}

int Pipe::get_width()
{
    return width;
}

int Pipe::get_position()
{
    return currentPos;
}

int Pipe::get_increment()
{
    return increment;
}

std::vector<int> Pipe::get_directions()
{
    return std::vector<int>(directions);
}
