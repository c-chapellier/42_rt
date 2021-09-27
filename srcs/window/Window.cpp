#include "Window.hpp"

Window::Window(int width, int height)
    : width(width), height(height)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(this->height, this->width, 0, &this->window, &this->renderer);
    this->clear();
}

Window::Window(int width, int height, std::map<std::string, Image> imgs)
    : width(width), height(height), imgs(imgs)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(this->height, this->width, 0, &this->window, &this->renderer);
    this->clear();
}

Window::~Window()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Window::clear()
{
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    SDL_RenderClear(this->renderer);
}

void Window::refresh()
{
    SDL_RenderPresent(this->renderer);
}

void Window::pause()
{
    while (1)
    {
        if (SDL_PollEvent(&this->event) && this->event.type == SDL_QUIT)
            break;
    }
}

void Window::load_image(std::string name, Image &img)
{
    if (!img.is_valid(this->width, this->height))
        throw "Image and window dimensions do not match.";
    this->imgs[name] = img;
}

void Window::set_image(std::string name)
{
    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            SDL_SetRenderDrawColor(
                this->renderer,
                this->imgs[name][i][j].get_red(),
                this->imgs[name][i][j].get_green(),
                this->imgs[name][i][j].get_blue(),
                this->imgs[name][i][j].get_opacity()
            );
            SDL_RenderDrawPoint(this->renderer, i, j);
        }
    }
    this->refresh();
}

void Window::destroy_image(std::string name)
{
    this->imgs.erase(name);
}
