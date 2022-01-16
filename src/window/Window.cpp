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

void Window::pause(Engine *engine)
{
    SDL_Event event;
    bool debug_mode = true;
    int x, y;

    while (SDL_WaitEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        {
            printf( "Quit\n" );
            return;
        }
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                printf( "Quit\n" );
                return;
            case SDLK_d:
                debug_mode = !debug_mode;
                break;
            default:
                break;
            }
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            SDL_GetMouseState(&x, &y);
            debug = 1;
            PRINT("x = " << x << ", y = " << y);
            Ray ray = engine->camera.getRay((engine->height - 1 - y) * engine->precision, x * engine->precision);
            Vec3 pxl = engine->get_color(ray, 0);
            PRINT("pixel: " << pxl << std::endl);
            debug = 0;
            break;
        }
        default:
        {
            break;
        }
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
