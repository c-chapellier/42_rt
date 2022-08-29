
#include "./EquationFiller.hpp"

void EquationFiller::x4(double coefs[5], double x, double a)
{
    coefs[4] += QUARTIC(a);
    coefs[3] += 4*CUBE(a)*x;
    coefs[2] += 6*SQUARE(a*x);
    coefs[1] += 4*a*CUBE(x);
    coefs[0] += QUARTIC(x);
}

void EquationFiller::nx2y2(double coefs[5], double x, double y, double a, double b, double n)
{
    coefs[4] += n * (SQUARE(a*b));
    coefs[3] += n * (2*a*x*SQUARE(b) + 2*b*y*SQUARE(a));
    coefs[2] += n * (SQUARE(a*y) + SQUARE(b*x) + 4*a*b*x*y);
    coefs[1] += n * (2*SQUARE(x)*y*b + 2*SQUARE(y)*x*a);
    coefs[0] += n * (SQUARE(x) * SQUARE(y));
}

void EquationFiller::nx2(double coefs[5], double x, double a, double n)
{
    coefs[2] += n*SQUARE(a);
    coefs[1] += n*2*a*x;
    coefs[0] += n*SQUARE(x);
}

void EquationFiller::nx(double coefs[5], double x, double a, double n)
{
    coefs[1] += n*a;
    coefs[0] += n*x;
}
