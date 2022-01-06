#include "Window.hpp"

Window::Window(int height, int width)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &this->window, &this->renderer);
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
    SDL_Event event;

    while (SDL_WaitEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            printf( "Quit\n" );
            return;
        default:
            break;
        }
    }
}

void Window::stream(std::vector< std::vector<Vec3> > &pixels)
{
    int height = pixels.size();
    int width = pixels[0].size();

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            SDL_SetRenderDrawColor(
                this->renderer,
                int(255.99 * pixels[i][j].r()),
                int(255.99 * pixels[i][j].g()),
                int(255.99 * pixels[i][j].b()),
                255
            );
            SDL_RenderDrawPoint(this->renderer, j, height - 1 - i);
        }
    }
    this->refresh();

    // poll for an event for the window to pop
    SDL_Event event;
    SDL_PollEvent(&event);
}
