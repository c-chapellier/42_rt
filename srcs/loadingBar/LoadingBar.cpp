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
    Pixel black(0, 0, 0, 0);
    Pixel grey(127, 127, 127, 0);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i > (height / 2) - 50 && i < (height / 2) + 50 && (double)j < (double)width * ((double)this->percentage / 100))
                img.set_pixel(j, i, grey);
            else
                img.set_pixel(j, i, black);
        }
    }
    this->window->stream(img);
}

LoadingBar &LoadingBar::operator+=(const int rhs)
{
    this->percentage += rhs;
    if (this->percentage > 100)
        throw "LoadingBar: percentage > 100.";
    this->refresh();
    return *this;
}
