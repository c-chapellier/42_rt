#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#include <exception>
#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>

#include <vector>
#include <list>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>

#define DEGREE_TO_RADIAN(n) ((n) * (M_PI / 180))
#define RADIAN_TO_DEGREE(n) ((n) * (180 / M_PI))

#define RANDOM(min, max) (double)(min) + ((double)(max) - (double)(min)) * ((double)rand() / (RAND_MAX + 1.0))

#include "components/Vec3.hpp"
#include "components/Ray.hpp"

class Material;

struct hit_t
{
    double t;
    Vec3 intersection, normal;
    bool is_front_face;
    Material *material;
};

#include "materials/Material.hpp"
#include "materials/Lambertian.hpp"
#include "materials/Metal.hpp"

#include "objects/Object.hpp"
#include "objects/Sphere.hpp"

#include "camera/Camera.hpp"
#include "window/Window.hpp"
