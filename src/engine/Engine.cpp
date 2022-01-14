#include "Engine.hpp"

Engine::Engine()
    : camera(
        Vec3(-10, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0),
        90,
        this->height * this->precision,
        this->width * this->precision
    )
{
    this->pixels.resize(this->height, std::vector<Vec3>(this->width));

    this->win = std::make_unique<Window>(this->height, this->width);

    this->objects.push_back(new Torus(
        Transform(Vec3(0, 0, 0), Vec3(0, .8, 0), Vec3(2, 2, 2)),
        new Diffuse(Vec3(.8, .2, .2)),
        1,
        .3
    ));

    // this->objects.push_back(new Torus(
    //     Transform(Vec3(0, 0, 0), Vec3(0, 0, .9), Vec3(3, 3, 3)),
    //     new Diffuse(Vec3(.8, .2, .2)),
    //     1,
    //     .3
    // ));

    this->objects.push_back(new Sphere(
        Transform(Vec3(0, 2, -2), Vec3(0, 0, 0), Vec3(1, 1, 1)),
        new Diffuse(Vec3(.2, .2, .8))
    ));

    this->objects.push_back(new Sphere(
        Transform(Vec3(0, -2, -2), Vec3(0, 0, 0), Vec3(1, 1, 1)),
        new Diffuse(Vec3(.2, .8, .2))
    ));

    // this->objects.push_back(new Sphere(
    //     Transform(Vec3(0, 0, 2), Vec3(1, 1, 1)),
    //     new Diffuse(Vec3(.8, .2, .2))
    // ));
}

Engine::~Engine()
{
    for (auto object: this->objects) delete object;
}

bool Engine::hit(const Ray &ray, hit_t &hit)
{
    hit.t = INFINITY;

    int n = this->objects.size();

    for (int i = 0; i < n; ++i)
    {
        if (objects[i]->intersect(ray, .001, hit))
        {
            hit.material = objects[i]->material;
        }
    }

    return hit.t != INFINITY;
}

Vec3 Engine::get_color(const Ray &ray, int depth)
{
    hit_t hit;

    if (depth >= 10) return Vec3(1, 1, 1);

    if (this->hit(ray, hit))
    {
        Ray reflected;
        Vec3 attenuation;

        // return Vec3(.8, .2, .2);

        if (hit.material->reflect(ray, hit, attenuation, reflected))
            return attenuation * this->get_color(reflected, depth + 1);

        return attenuation;
    }
    
    // return Vec3(1, 1, 1);
    return depth == 0 ? Vec3(0, 0, 0) : Vec3(1, 1, 1);
}

void Engine::threads(int n_thread)
{
    for (int i = n_thread; i < this->height; i += this->n_threads)
    {
        !(i % 10) && std::cout << "i " << i << "\n\033[F";
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
    // std::cout << "press any key ..." << std::endl;
    // std::cin.get();

    std::cout << "run" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    for (int i = 0; i < this->n_threads; ++i)
        threads.push_back(std::thread(&Engine::threads, this, i));

    for (auto &th : threads)
        th.join();

    auto stop = std::chrono::high_resolution_clock::now();
    this->win->stream(this->pixels);

    std::cout << "Loaded: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " milliseconds" << std::endl;
    this->win->pause();
}
