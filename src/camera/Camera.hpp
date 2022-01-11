#pragma once

#include "../header.hpp"

class Camera
{
private:
    Vec3 coordinates;
    int h_2, w_2;

    Vec3 v, u;
    Vec3 screenCenter;
        
public:
    Camera(Vec3 coordinates, Vec3 direction, Vec3 up, double angle, int height, int width);

    Ray getRay(int i, int j) const;
};
