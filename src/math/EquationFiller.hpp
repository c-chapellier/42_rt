#pragma once

#include <math.h>
#include "../global.hpp"

class EquationFiller
{
private:

public:
    static void x4(double coefs[5], double x, double a);
    static void nx2y2(double coefs[5], double x, double y, double a, double b, double n);
    static void nx2(double coefs[5], double x, double a, double n);
    static void nx(double coefs[5], double x, double a, double n);
};
