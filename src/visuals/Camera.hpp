#pragma once

#include <math.h>

#include "../header.hpp"

#include "../objects/components/Point.hpp"
#include "../objects/components/Vector.hpp"
#include "../objects/Plane.hpp"

class Config;

class Camera
{
    private:
        Point p;
        Vector v;
        double angle;
        
    public:
        Camera(double px, double py, double pz, double vx, double vy, double vz, double a);
        Camera(const Point &p, const Vector &v, double a);
        ~Camera();

        Point getP() const;
        Vector getV() const;

        std::vector< std::vector<Point> > getScreen(const Config &config) const;
};