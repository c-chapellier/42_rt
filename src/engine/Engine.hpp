#pragma once

#include "../header.hpp"

class Engine
{
private:
    std::unique_ptr<Window> win;

    std::vector<Object *> objects;

    const int height = 600, width = 600, precision = 4;

    const int n_threads = std::thread::hardware_concurrency();
    // const int n_threads = 1;

    std::vector< std::vector<Vec3> > pixels;

    Camera camera;

public:
    Engine();
    ~Engine();

    void run();
    void threads(int n_thread);
    Vec3 get_color(const Ray &ray, int depth);
    bool hit(const Ray &ray, hit_t &hit);
};