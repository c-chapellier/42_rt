#pragma once

#include "Object.hpp"
#include "./../header.hpp"

class Intersection;

class Sphere : public Object
{
    private:
        double r;
    public:
        Sphere(double r);
        ~Sphere();

        double getR() const;

        std::vector<Intersection> intersect(const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(Intersection &intersection, const Line &line) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};