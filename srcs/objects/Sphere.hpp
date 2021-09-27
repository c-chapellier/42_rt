#pragma once

#include <iostream>
#include "components/Point.hpp"

class Sphere
{
    private:
        const Point *center;
        const double r;
    public:
        Sphere(double x, double y, double z, double r);
        ~Sphere();

        friend std::ostream& operator<<(std::ostream& out, const Sphere& sp);
};