#pragma once

#include "../header.hpp"

class Intersection;

class Plane;

class Circle : public Object
{
    private:
        double R;
        double r;
    public:
        Circle(double R, double r);
        ~Circle();

        void intersect(std::vector<Intersection> *intersections, const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(const Intersection &intersection, const Line &line) const;
        Color getColorAt(const Point &intersection) const;
};