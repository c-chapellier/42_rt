#pragma once

#include "../header.hpp"

class Window
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;

public:
    Window(int height, int width);
    ~Window();

    void clear();
    void refresh();
    void pause();
    void stream(std::vector< std::vector<Vec3> > &pixels);
};