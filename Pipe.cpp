#include "Pipe.h"


bool contains(SDL_Rect rect, SDL_Point point)
{
    return (point.x >= rect.x && point.x <= rect.w) && (point.y >= rect.y && point.y <= rect.h);
}

Pipe::Pipe(int direct, SDL_Color color, SDL_Point position)
{
    int red = rand() % 0xFF;
    int green = rand() % 0xFF;
    primary = {red, green, 0};
    currentDirect = direct;
    currentPos = position;
}

void Pipe::wraparound()
{
    switch (currentDirect)
    {
        case UP:
            positions.push_back({currentPos.x, 0});
            positions.push_back({-1,-1});
            positions.push_back({currentPos.x, boundingBox.h});
            currentPos.y = boundingBox.h + currentPos.y % boundingBox.h;
            break;
        case DOWN:
            positions.push_back({currentPos.x, boundingBox.h});
            positions.push_back({-1,-1});
            positions.push_back({currentPos.x, 0});
            currentPos.y = currentPos.y % boundingBox.h;
            break;
        case LEFT:
            positions.push_back({0, currentPos.y});
            positions.push_back({-1,-1});
            positions.push_back({boundingBox.w, currentPos.y});
            currentPos.x = boundingBox.w + currentPos.x % boundingBox.w;
            break;
        case RIGHT:
            positions.push_back({boundingBox.w, currentPos.y});
            positions.push_back({-1,-1});
            positions.push_back({0, currentPos.y});
            currentPos.x = currentPos.x % boundingBox.w;
            break;
    }
}

void Pipe::grow()
{
    if (stop)
        return;

    if (!contains(boundingBox, currentPos))
        wraparound();
    positions.push_back(currentPos);

    if (rand() % 10 == 0)
        change_direction(rand());

    int increment = rand();
    switch (currentDirect)
    {
        case UP:
            currentPos.y -= increment % (boundingBox.h / 25);
            break;
        case DOWN:
            currentPos.y += increment % (boundingBox.h / 25);
            break;
        case LEFT:
            currentPos.x -= increment % (boundingBox.w / 25);
            break;
        case RIGHT:
            currentPos.x += increment % (boundingBox.w / 25);
            break;
    }


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

std::vector<SDL_Point> Pipe::get_positions()
{
    return std::vector<SDL_Point>(positions);
}

int Pipe::get_position_count()
{
    return positions.size();
}

Pipe::Line Pipe::peek_line()
{
    return lineStack.back();
}
