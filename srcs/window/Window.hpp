#pragma once

#include <map>
#include <string>
#include <SDL2/SDL.h>

#include "../image/Image.hpp"

class Window
{
private:
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    const int width;
    const int height;
    std::map<std::string, Image> imgs;

public:
    Window(int width, int height);
    ~Window();

    void clear();
    void refresh();
    void pause();

    void load_image(std::string name, Image &img);
    void set_image(std::string name);
    void destroy_image(std::string name);
};