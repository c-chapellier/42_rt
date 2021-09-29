#pragma once

#include "Object.hpp"
#include "components/Point.hpp"
#include "Line.hpp"
#include <math.h>

class Quadratic : public Object
{
    private:
        double A, B, C, D, E, F, G, H, I, J;
    public:
        Quadratic(double A, double B, double C, double D, double E, double F, double G, double H, double I, double J);
        ~Quadratic();

        Point *intersect(Line *line);
};