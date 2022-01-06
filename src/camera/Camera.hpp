#pragma once

#include "../header.hpp"

class Camera
{
private:
    Vec3 coordinates, direction, up;
    double angle;
    int height, width;

    Vec3 v, u;
    Vec3 screenCenter;
        
public:
    Camera(Vec3 coordinates, Vec3 direction, Vec3 up, double angle, int height, int width);

    void getRays(std::vector< std::vector<Ray> > &rays) const;
};
