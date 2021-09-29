#pragma once

#include <iostream>
#include "components/Point.hpp"
#include "Object.hpp"

// Equation:
// (x - x₀)² + (Y - Y₀)² + (Z - Z₀)² = R²

class Sphere : public Object
{
    private:
        Point *center;
        const double r;
    public:
        Sphere(double x, double y, double z, double r);
        Sphere(Point p, double r);
        ~Sphere();

        Point *intersect(Line *line);

        friend std::ostream& operator<<(std::ostream& out, const Sphere& sp);
};