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

    std::cout << "refresh " << this->percentage << std::endl;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            // std::cout << "beg i[" << i << "] j[" << j << "] red[" << img[i][j].getRed() << "]" << std::endl;
            // std::cout << "beg i[" << 251 << "] j[" << 1 << "] red[" << img[251][1].getRed() << "]" << std::endl;
            if (i > (height / 2) - 50 && i < (height / 2) + 50 && (double)j < (double)width * ((double)this->percentage / 100))
            {
                img[i][j] = Pixel(127, 127, 127, 255);
                // std::cout << "  setting pixel color to " << img[i][j].getRed() << std::endl;
            }
            else {
                // std::cout << "  setting pixel color to " << img[i][j].getRed() << std::endl;
                img[i][j] = Pixel(0, 0, 0, 255);
            }

            // std::cout << "end i[" << i << "] j[" << j << "] red[" << img[i][j].getRed() << "]" << std::endl;
            // std::cout << "end i[" << 251 << "] j[" << 1 << "] red[" << img[251][1].getRed() << "]" << std::endl;
        }
        // std::cout << "end for i [" << i << "] red[" << img[i][0].getRed() << "]" << std::endl;
    }
    // for (int i = 0; i < height; ++i)
    //     for (int j = 0; j < width; ++j)
    //         img[i][j].getRed() != 0.0 && std::cout << "ok 1 -------------" << std::endl; 
    this->window->stream(img);
    std::cout << "end refresh" << std::endl;
}

void LoadingBar::add(int i)
{
    this->percentage += i;

    if (this->percentage > 100)
        throw "LoadingBar::add: percentage > 100.";
        
    this->refresh();
}
