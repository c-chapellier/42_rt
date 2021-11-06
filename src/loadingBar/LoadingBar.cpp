#include "LoadingBar.hpp"

LoadingBar::LoadingBar(Window *window) : window(window), percentage(0)
{
    this->refresh();
}

LoadingBar::~LoadingBar()
{
}

void LoadingBar::refresh()
{
    int width = this->window->get_width();
    int height = this->window->get_height();
    Image img(width, height);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i > (height / 2) - 50 && i < (height / 2) + 50 && (double)j < (double)width * ((double)this->percentage / 100))
            {
                img[i][j] = Pixel(127, 127, 127, 255);
            }
            else {
                img[i][j] = Pixel(0, 0, 0, 255);
            }
        }
    }
    this->window->stream(img);
}

void LoadingBar::add(int i)
{
    this->percentage += i;

    if (this->percentage > 100)
        throw "LoadingBar::add: percentage > 100.";
        
    this->refresh();
}
