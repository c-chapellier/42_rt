#pragma once

#include "../header.hpp"

class Engine
{
private:
    std::unique_ptr<Window> win;

    std::vector<Object *> objects;

    const int height = 900, width = 900, precision = 9;

    const int n_threads = std::thread::hardware_concurrency();

    std::vector< std::vector<Vec3> > pixels;
    std::vector< std::vector<Ray> > rays;

public:
    Engine();
    ~Engine();

    void run();
    void threads(int n_thread);
    Vec3 get_color(const Ray &ray, int depth);
    bool hit(const Ray &ray, hit_t &hit);
    Vec3 random_in_unit_sphere();
};