#pragma once

#include "components/Point.hpp"
#include "components/Vector.hpp"

class Cylinder
{
    private:
        Point *p;
        Vector *v;
        double r;
    public:
        Cylinder(double px, double py, double pz, double vx, double vy, double vz, double r);
        ~Cylinder();

        friend std::ostream& operator<<(std::ostream& out, const Cylinder& cylinder);
};