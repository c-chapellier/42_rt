#pragma once

#include "Object.hpp"
#include "./../header.hpp"

class Sphere : public Object
{
    private:
        Point p;
        double r;
    public:
        Sphere(const Point &p, double r);
        Sphere(double x, double y, double z, double r);
        Sphere(double x, double y, double z, double r, const Color &color);
        ~Sphere();

        Point getP() const;
        double getR() const;

        Point intersect(const Line &line) const;
        double angleWith(const Line &line) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};