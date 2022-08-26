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

#define PRINT(x) if (debug) std::cout << x << std::endl

#define DEGREE_TO_RADIAN(n) ((n) * (M_PI / 180))
#define RADIAN_TO_DEGREE(n) ((n) * (180 / M_PI))

#define RANDOM(min, max) (double)(min) + ((double)(max) - (double)(min)) * ((double)rand() / (RAND_MAX + 1.0))

#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))
#define QUARTIC(x) ((x) * (x) * (x) * (x))

#define EPSILON 1e-6

extern int debug;

#include "math/EquationSolver.hpp"

#include "components/Vec3.hpp"
#include "components/Ray.hpp"
#include "components/Matrix.hpp"
#include "components/Transform.hpp"

class Object;

struct hit_t
{
    double t, u, v;
    int t_index;
    Vec3 local_inter, global_inter, normal;
    bool is_front_face;
    Object *object;
};

struct t_t
{
    double t;
    int index;
};
