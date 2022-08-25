#include "Engine.hpp"

Engine::Engine(const std::string &scene, const std::string &saveFile) :
    saveFile(saveFile),
    parser(scene),
    height(this->parser.height),
    width(this->parser.width),
    precision(this->parser.precision),
    camera(this->parser.camera),
    objects(this->parser.objects),
    pixels(std::vector< std::vector<Vec3> >(this->height, std::vector<Vec3>(this->width))),
    window(Window(this->height, this->width))
{

}

Engine::~Engine()
{

}

bool Engine::hit(const Ray &ray, hit_t &hit) const
{
    hit.t = INFINITY;

    int n = this->objects.size();

    for (int i = 0; i < n; ++i)
    {
        if (objects[i]->intersect(ray, EPSILON, hit))
        {
            hit.object = objects[i];
        }
    }

    return hit.t != INFINITY;
}

Vec3 Engine::get_color(const Ray &ray, int depth) const
{
    hit_t hit;

    if (depth >= 10) return Vec3(1, 1, 1);

    if (this->hit(ray, hit))
    {
        Vec3 color = hit.object->texture->get_color(hit);

        PRINT("[" << depth << "]: color: " << color);

        Ray reflected;
        if (hit.object->material->reflect(ray, hit, color, reflected))
            return color * this->get_color(reflected, depth + 1);

        return color;
    }
    
    // return Vec3(1, 1, 1);
    return depth == 0 ? Vec3(0, 0, 0) : Vec3(1, 1, 1);
}

void Engine::threads(int n_thread)
{
    for (int i = n_thread; i < this->height; i += this->n_threads)
    {
        // !(i % 10) && std::cerr << "i " << i << "\n\033[F";
        for (int j = 0; j < this->width; ++j)
        {
            this->pixels[i][j] = Vec3(0, 0, 0);
            for (int pi = 0; pi < this->precision; ++pi)
            {
                for (int pj = 0; pj < this->precision; ++pj)
                {
                    Ray ray = this->camera.getRay(i * this->precision + pi, j * this->precision + pj);
                    this->pixels[i][j] += this->get_color(ray, 0);
                }
            }
            this->pixels[i][j] /= this->precision * this->precision;
        }
    }
}

void Engine::run()
{
    std::cout << "press any key ..." << std::endl;
    std::cin.get();

    std::cerr << "run" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    for (int i = 0; i < this->n_threads; ++i)
        threads.push_back(std::thread(&Engine::threads, this, i));

    for (auto &th : threads)
        th.join();

    auto stop = std::chrono::high_resolution_clock::now();
    std::cerr << "Loaded: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " milliseconds" << std::endl;

    BMP::write(this->pixels, this->saveFile);
    std::cerr << "Image saved: " << this->saveFile << std::endl;

    this->window.stream(this->pixels);
    this->window.pause(this);
}

Vec3 Engine::get_debug_pixel(int x, int y) const
{
    Ray ray = this->camera.getRay((this->height - 1 - y) * this->precision, x * this->precision);
    return this->get_color(ray, 0);
}

// define once engine is defined
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
            Vec3 pxl = engine->get_debug_pixel(x, y);
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
