#pragma once

#include "../global.hpp"

#include "../window/Window.hpp"
#include "../camera/Camera.hpp"

#include "../objects/Sphere.hpp"
#include "../objects/Torus.hpp"
#include "../objects/Plane.hpp"
#include "../objects/MobiusTape.hpp"

#include "../materials/Diffuse.hpp"
#include "../materials/Metal.hpp"
#include "../materials/Mirror.hpp"

#include "../textures/Uniform.hpp"
#include "../textures/ChessBoard.hpp"

class Window;

class Engine
{
public:
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