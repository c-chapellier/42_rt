#pragma once

#include "../global.hpp"

// #include "../engine/Engine.hpp"

class Engine;

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
    void pause(Engine *engine);
    void stream(std::vector< std::vector<Vec3> > &pixels);
};
