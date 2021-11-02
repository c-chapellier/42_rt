#pragma once

#include "Object.hpp"
#include "./../header.hpp"

class Sphere : public Object
{
    private:
        Point p;
        double r;
    public:
        Sphere(Point &p, double r);
        Sphere(double x, double y, double z, double r);
        Sphere(double x, double y, double z, double r, Color &color);
        ~Sphere();

        Point getP();
        double getR();

        Point *intersect(const Line &line) const;
        double angleWith(const Line &line) const;
};