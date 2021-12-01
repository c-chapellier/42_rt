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

        std::vector<Intersection> intersect(const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(Intersection &intersection, const Line &line) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};