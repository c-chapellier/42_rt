#include "Engine.hpp"

Engine::Engine()
{
    this->pixels.resize(this->height, std::vector<Vec3>(this->width));
    this->rays.resize(this->height * this->precision, std::vector<Ray>(this->width * this->precision));

    this->win = std::make_unique<Window>(this->height, this->width);

    this->objects.push_back(new Sphere(Vec3(0, 0, 0), 30, new Metal(Vec3(.8, .2, .2))));

    // this->objects.push_back(new Sphere(Vec3(100, -22, 0), 20, new Metal(Vec3(.8, .2, .2))));
    // this->objects.push_back(new Sphere(Vec3(100, 22, 0), 20, new Metal(Vec3(.2, .2, .8))));

    // auto ground_material = new Lambertian(Vec3(0.5, 0.5, 0.5));
    // this->objects.push_back(new Sphere(Vec3(0, -1000, 0), 1000, ground_material));

    // for (int a = -11; a < 11; a++) {
    //     for (int b = -11; b < 11; b++) {
    //         auto choose_mat = RANDOM(0, 1);
    //         Vec3 center(a + 0.9 * RANDOM(0, 1), 0.2, b + 0.9 * RANDOM(0, 1));

    //         if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
    //             if (choose_mat < 0.8) {
    //                 // diffuse
    //                 auto albedo = Vec3(RANDOM(0, 1), RANDOM(0, 1), RANDOM(0, 1)) * Vec3(RANDOM(0, 1), RANDOM(0, 1), RANDOM(0, 1));
    //                 auto sphere_material = new Lambertian(albedo);
    //                 this->objects.push_back(new Sphere(center, 0.2, sphere_material));
    //             } else if (choose_mat < 0.95) {
    //                 // metal
    //                 auto albedo = Vec3(RANDOM(.5, 1), RANDOM(.5, 1), RANDOM(.5, 1));
    //                 // auto fuzz = RANDOM(0, .5);
    //                 auto sphere_material = new Metal(albedo /* , fuzz */ );
    //                 this->objects.push_back(new Sphere(center, 0.2, sphere_material));
    //             } else {
    //                 // glass
    //                 // auto sphere_material = new dielectric(1.5);
    //                 // this->objects.push_back(new Sphere(center, 0.2, sphere_material));
    //             }
    //         }
    //     }
    // }

    // // auto material1 = new dielectric(1.5);
    // // this->objects.push_back(new Sphere(Vec3(0, 1, 0), 1.0, material1));

    // auto material2 = new Lambertian(Vec3(0.4, 0.2, 0.1));
    // this->objects.push_back(new Sphere(Vec3(-4, 1, 0), 1.0, material2));

    // auto material3 = new Metal(Vec3(0.7, 0.6, 0.5) /* , 0.0 */ );
    // this->objects.push_back(new Sphere(Vec3(4, 1, 0), 1.0, material3));
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

    if (depth >= 2) return Vec3(1, 1, 1);

    if (this->hit(ray, hit))
    {
        Ray scattered;
        Vec3 attenuation;

        if (hit.material->scatter(ray, hit, attenuation, scattered))
            return attenuation * this->get_color(scattered, depth + 1);

        return Vec3(1, 1, 1);
    }
    
    // return Vec3(1, 1, 1);
    return depth == 0 ? Vec3(0, 0, 0) : Vec3(1, 1, 1);
}

void Engine::threads(int n_thread)
{
    for (int i = n_thread; i < this->height; i += this->n_threads)
    {
        // std::cout << "i " << i << std::endl;
        for (int j = 0; j < this->width; ++j)
        {
            this->pixels[i][j] = Vec3(0, 0, 0);
            for (int pi = 0; pi < this->precision; ++pi)
            {
                for (int pj = 0; pj < this->precision; ++pj)
                {
                    this->pixels[i][j] += this->get_color(this->rays[i * this->precision + pi][j * this->precision + pj], 0);
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

    std::cout << "run" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;

    Camera camera(
        Vec3(-100, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0),
        // Vec3(13, 2, 3), -Vec3(13, 2, 3), Vec3(0, 1, 0),
        90,
        this->height * this->precision,
        this->width * this->precision
    );

    camera.getRays(this->rays);

    for (unsigned int i = 0; i < this->n_threads; ++i)
        threads.push_back(std::thread(&Engine::threads, this, i));

    for (auto &th : threads)
        th.join();

    auto stop = std::chrono::high_resolution_clock::now();
    this->win->stream(this->pixels);

    std::cout << "Loaded: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " milliseconds" << std::endl;
    this->win->pause();
}
