#pragma once

#include "Object.hpp"
#include "components/Point.hpp"
#include "components/Line.hpp"
#include "Plane.hpp"
#include <math.h>

class Plane;

// Equation:
// Ax² + By² + Cz² + Dxy + Exz + Fyz + Gx + Hy + Iz + J = 0
// A(x - x₀)² + B(y - y₀)² + C(z - z₀)² + D(x - x₀)(y - y₀) + E(x - x₀)(z - z₀) + F(y - y₀)(z - z₀) + G(x - x₀) + H(y - y₀) + I(z - z₀) + J = 0

class Quadratic : public Object
{
    private:
        double A, B, C, D, E, F, G, H, I, J;
        Point p;
        
    public:
        Quadratic(double A, double B, double C, double D, double E, double F, double G, double H, double I, double J);
        Quadratic(const Point &p, double A, double B, double C, double D, double E, double F, double G, double H, double I, double J);
        Quadratic(const Point &p, double A, double B, double C, double D, double E, double F, double G, double H, double I, double J, const Color &color);
        ~Quadratic();

        Point intersect(const Line &line) const;
        double angleWith(const Line &line) const;
        Plane *tangentAt(const Point &p) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};