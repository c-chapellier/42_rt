#pragma once

#include "Object.hpp"
#include "components/Point.hpp"
#include "Line.hpp"
#include "Plane.hpp"
#include <math.h>

// Equation:
// Ax² + By² + Cz² + Dxy + Exz + Fyz + Gx + Hy + Iz + J = 0
// A(x - x₀)² + B(y - y₀)² + C(z - z₀)² + D(x - x₀)(y - y₀) + E(x - x₀)(z - z₀) + F(y - y₀)(z - z₀) + G(x - x₀) + H(y - y₀) + I(z - z₀) + J = 0

class Quadratic : public Object
{
    private:
        double A, B, C, D, E, F, G, H, I, J;
        Point *p;
    public:
        Quadratic(double A, double B, double C, double D, double E, double F, double G, double H, double I, double J);
        Quadratic(Point &p, double A, double B, double C, double D, double E, double F, double G, double H, double I, double J);
        ~Quadratic();

        Point *intersect(Line *line);
        double angleWith(Line *line);
        Plane *tangentAt(Point *p);
};