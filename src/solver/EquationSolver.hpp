#pragma once

#include <list>
#include <math.h>
#include <iostream>

#include "Complex.hpp"

class EquationSolver
{
    public:
        static std::list<double> solveEquation(double a, double b);
        static std::list<double> solveQuadraticEquation(double a, double b, double c);
        static std::list<double> solveCubicEquation(double a, double b, double c, double d);
        static std::list<double> solveQuarticEquation(double a, double b, double c, double d, double e);
};