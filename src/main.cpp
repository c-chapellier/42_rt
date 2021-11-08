#include "engine/Engine.hpp"

//void texture();

int main(int argc, char *argv[])
{
    srand(time(NULL));

    EquationSolver::solveQuarticEquation(1, -4, -5, 2, -10);

    try
    {
        if (argc < 2)
            throw std::string("Usage: ") + argv[0] + " <config file>";

        int flags = IMG_INIT_JPG | IMG_INIT_PNG;
        int initted = IMG_Init(flags);

        if ((initted & flags) != flags)
            throw "IMG_Init: Failed to init required jpg and png support!";

        Engine(argv[1]).run();
        
        IMG_Quit();
        //texture();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const std::string& e)
    {
        std::cerr << e << '\n';
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    catch (...)
    {
        std::cerr << "catch something else" << '\n';
    }
    return 0;
}

// int byteMap(SDL_Surface *img) {
//     if (img->format->BytesPerPixel == 1) {
//         return 1;
//     }
//     if (img->format->BytesPerPixel == 2) {
//         return 2;
//     }
//     if (img->format->BytesPerPixel == 3) {
//         return 3;
//     }
//     if (img->format->BytesPerPixel == 4) {
//         return 4;
//     }
//     return 5;
// }

// void surfaceInfo(SDL_Surface *img) {
//     SDL_LockSurface(img);
//     std::cout << "* * * * * * * * * *" << std::endl;
//     std::cout << "*     SURFACE     *" << std::endl;
//     std::cout << "* * * * * * * * * *" << std::endl;
//     std::cout << "height: " << img->h << std::endl;
//     std::cout << "width: " << img->w << std::endl;
//     std::cout << "pixels: " << img->pixels << std::endl;
//     std::cout << "pixels[0][0]: " << (int)((uint8_t*)img->pixels)[30000] << std::endl;
//     std::cout << "pixels[0][1]: " << (int)((uint8_t*)img->pixels)[30001] << std::endl;
//     std::cout << "pixels[0][2]: " << (int)((uint8_t*)img->pixels)[30002] << std::endl;
//     std::cout << "* * * * * * * * * *" << std::endl;
//     std::cout << "*      format     *" << std::endl;
//     std::cout << "* * * * * * * * * *" << std::endl;
//     std::cout << "format: " << img->format->format << " " << SDL_PIXELTYPE(img->format->format) << std::endl;
//     std::cout << "byte per pixel: " << byteMap(img) << std::endl;
//     std::cout << "R mask: " << img->format->Rmask << std::endl;
//     std::cout << "B mask: " << img->format->Bmask << std::endl;
//     std::cout << "G mask: " << img->format->Gmask << std::endl;
//     std::cout << "A mask: " << img->format->Amask << std::endl;
//     std::cout << "R loss: " << (int)img->format->Rloss << std::endl;
//     std::cout << "B loss: " << (int)img->format->Bloss << std::endl;
//     std::cout << "G loss: " << (int)img->format->Gloss << std::endl;
//     std::cout << "A loss: " << (int)img->format->Aloss << std::endl;
//     std::cout << "R shift: " << (int)img->format->Rshift << std::endl;
//     std::cout << "B shift: " << (int)img->format->Bshift << std::endl;
//     std::cout << "G shift: " << (int)img->format->Gshift << std::endl;
//     std::cout << "A shift: " << (int)img->format->Ashift << std::endl;
//     // std::cout << "* * * * * * * * * *" << std::endl;
//     // std::cout << "*     palette     *" << std::endl;
//     // std::cout << "* * * * * * * * * *" << std::endl;
//     // std::cout << "n colors: " << img->format->palette << std::endl;
//     // std::cout << "* * * * * * * * * *" << std::endl;
//     // std::cout << "*      color      *" << std::endl;
//     // std::cout << "* * * * * * * * * *" << std::endl;
//     // std::cout << "r: " << img->format->palette->colors->r << std::endl;
//     // std::cout << "g: " << img->format->palette->colors->g << std::endl;
//     // std::cout << "b: " << img->format->palette->colors->b << std::endl;
//     // std::cout << "a: " << img->format->palette->colors->a << std::endl;
//     for (int i = 0; i < img->h; ++i) {
//         for (int j = 0; j < img->w; ++j) {
//             std::cout << "pixels[" << i * img->w + j << "] R: " << (int)((uint8_t*)img->pixels)[((i * img->w + j) * 3)] << std::endl;
//             std::cout << "pixels[" << i * img->w + j << "] G: " << (int)((uint8_t*)img->pixels)[((i * img->w + j) * 3) + 1] << std::endl;
//             std::cout << "pixels[" << i * img->w + j << "] B: " << (int)((uint8_t*)img->pixels)[((i * img->w + j) * 3) + 2] << std::endl;
//         }
//     }
//     SDL_UnlockSurface(img);
// }

// void texture()
// {
//     // load support for the JPG and PNG image formats
//     int flags = IMG_INIT_JPG|IMG_INIT_PNG;
//     int initted = IMG_Init(flags);
//     if((initted&flags) != flags) {
//         std::cout << "IMG_Init: Failed to init required jpg and png support!" << std::endl;
//         std::cout << "IMG_Init: " << IMG_GetError() << std::endl;
//     }
//     SDL_Surface *img = IMG_Load("textures/mars.jpg");

//     if (img == nullptr) {
//         std::cout << "IMG_Load: " << IMG_GetError() << "\n";
//     } else {
//         surfaceInfo(img);
//     }

//     IMG_Quit();
// }