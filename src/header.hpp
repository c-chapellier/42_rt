#pragma once

#include <exception>
#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include <cmath>

#include <vector>
#include <list>
#include <map>
#include <array>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>

#define PRINT(x) std::cout << x << std::endl

#define DEGREE_TO_RADIAN(n) ((n) * (M_PI / 180))
#define RADIAN_TO_DEGREE(n) ((n) * (180 / M_PI))

#define RANDOM(min, max) (double)(min) + ((double)(max) - (double)(min)) * ((double)rand() / (RAND_MAX + 1.0))

#define EPSILON .000001

#define FEQUALS(a, b) (fabs(fabs(a) - fabs(b)) < EPSILON)

int SolveQuartic(double c[ 5 ], double s[ 4 ]);

#include "components/Vec3.hpp"
#include "components/Ray.hpp"
#include "components/Matrix.hpp"
#include "components/Transform.hpp"

class Material;

struct hit_t
{
    double t;
    Vec3 intersection, normal;
    bool is_front_face;
    Material *material;
};

#include "materials/Material.hpp"
#include "materials/Diffuse.hpp"
#include "materials/Metal.hpp"

#include "objects/Object.hpp"
#include "objects/Sphere.hpp"
#include "objects/Torus.hpp"

#include "camera/Camera.hpp"
#include "window/Window.hpp"
