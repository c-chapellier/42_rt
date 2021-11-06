#pragma once

#include "BlackObject.hpp"
#include "../objects/components/Point.hpp"
#include "../objects/components/Vector.hpp"
#include "../objects/components/Line.hpp"

class BlackCylinder : public BlackObject
{
    private:
        Line l;
        double r;
    public:
        BlackCylinder(double px, double py, double pz, double vx, double vy, double vz, double r);
        BlackCylinder(Point &p, Vector &v, double r);
        BlackCylinder(Line &line, double r);
        ~BlackCylinder();

        bool contains(const Point &p) const;
};