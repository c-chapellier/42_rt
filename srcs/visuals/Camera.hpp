#pragma once

#include <math.h>

#include "./../header.hpp"

#include "./../objects/components/Point.hpp"
#include "./../objects/components/Vector.hpp"
#include "./../objects/Plane.hpp"

class Config;

class Camera
{
    private:
        Point *p;
        Vector *v;
        double angle;
    public:
        Camera(double px, double py, double pz, double vx, double vy, double vz, double a);
        Camera(Point p, Vector v, double a);
        ~Camera();

        Point *getP();
        Vector *getV();

        std::vector< std::vector<Point> > getScreen(Config &config);
};