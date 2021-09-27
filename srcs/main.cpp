#include "parser/Parser.hpp"
#include "objects/Object.hpp"
#include "objects/Sphere.hpp"

#include <stdlib.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 600

int main(void) {

	Parser parser("../configs/sphere.json");

    Object obj("sphere");

    std::cout << obj << std::endl;

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int i;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer); // create window
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0); // set color before drawing
    SDL_RenderClear(renderer); // draw all the window
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100); // set color before drawing
    for (i = 0; i < WINDOW_WIDTH; ++i)
        SDL_RenderDrawPoint(renderer, i, i); // draw the pixel
    SDL_RenderPresent(renderer); // render the image
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
