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

        void intersect(std::vector<Intersection> *intersections, const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(Intersection &intersection, const Line &line) const;
        Color getColorAt(const Point &intersection) const;
};