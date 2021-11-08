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
    int height = this->window->get_height();
    int width = this->window->get_width();
    Image img(height, width);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (
                j >= (height / 2) - 50
                && j <= (height / 2) + 50
                && i <= (width * this->percentage) / 100
            )
            {
                img[i][j] = Pixel(127, 127, 127, 255);
            }
            else {
                img[i][j] = Pixel(0, 0, 0, 255);
            }
        }
    }

    std::cout << "refresh 1" << std::endl;
    this->window->stream(img);
    std::cout << "refresh 2" << std::endl;
}

void LoadingBar::add(int i)
{
    this->percentage += i;

    if (this->percentage < 0 || this->percentage > 100)
        throw "LoadingBar::add: percentage < 0 || percentage > 100.";
        
    this->refresh();
}

void LoadingBar::set(int i)
{
    this->percentage = i;

    if (this->percentage < 0 || this->percentage > 100)
        throw "LoadingBar::set: percentage < 0 || percentage > 100.";
        
    this->refresh();
}
