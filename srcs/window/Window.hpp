#pragma once

#include <string>

#include "../../include/SDL2/SDL.h"
#include "../image/Image.hpp"

class Image;

class Window
{
private:
    SDL_Renderer *renderer;
    SDL_Window *window;

    const int height;
    const int width;
    
    std::vector<Image> imgs;
    int img_index;

    void event_info(SDL_Event event) const;

public:
    Window(int height, int width);
    ~Window();

    int get_width() const;
    int get_height() const;

    void clear();
    void refresh();
    void pause();

    void stream(Image &img);

    void load_image(Image &img);
    void set_image();
    void set_next_image();
    void set_prev_image();
};