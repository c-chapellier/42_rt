#pragma once

#include <math.h>
#include <list>
#include "Object.hpp"
#include "Plane.hpp"
#include "components/Point.hpp"
#include "components/Line.hpp"
#include "../solver/EquationSolver.hpp"
class Intersection;


class Plane;

// Equation:
// Ax² + By² + Cz² + Dxy + Exz + Fyz + Gx + Hy + Iz + J = 0
// A(x - x₀)² + B(y - y₀)² + C(z - z₀)² + D(x - x₀)(y - y₀) + E(x - x₀)(z - z₀) + F(y - y₀)(z - z₀) + G(x - x₀) + H(y - y₀) + I(z - z₀) + J = 0

class QuadraticSurface : public Object
{
    private:
        double A, B, C, D, E, F, G, H, I, J;

    public:
        QuadraticSurface(double A, double B, double C, double D, double E, double F, double G, double H, double I, double J);
        ~QuadraticSurface();

        void intersect(std::vector<Intersection> *intersections, const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(Intersection &intersection, const Line &line) const;
        Plane tangentAt(const Point &p) const;
        Color getColorAt(const Point &intersection) const;
};