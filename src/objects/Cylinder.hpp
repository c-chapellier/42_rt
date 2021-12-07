#pragma once

#include "Object.hpp"
#include "./../solver/Matrix.hpp"
#include "./../header.hpp"
#include "./../headers/define.hpp"

class Intersection;

class Cylinder : public Object
{
    private:
        double r;

    public:
        Cylinder(double r);
        ~Cylinder();

        void intersect(std::vector<Intersection> *intersections, const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(Intersection &intersection, const Line &line) const;
        Color getColorAt(const Point &intersection) const;
};