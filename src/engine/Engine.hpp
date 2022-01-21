#pragma once

#include "../global.hpp"

#include "../parser/XmlSceneParser.hpp"

#include "../saver/Saver.hpp"

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

class Engine
{
private:
    XmlSceneParser parser;

    int height, width, precision;
    Camera camera;
    std::vector<Object *> objects;

    std::vector< std::vector<Vec3> > pixels;
    Window window;

    const int n_threads = std::thread::hardware_concurrency();
    // const int n_threads = 1;

public:
    Engine(const std::string &file);
    ~Engine();

    void run();
    void threads(int n_thread);
    Vec3 get_color(const Ray &ray, int depth) const;
    bool hit(const Ray &ray, hit_t &hit) const;
    Vec3 get_debug_pixel(int x, int y) const;
};