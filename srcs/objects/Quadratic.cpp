#include "Quadratic.hpp"

Quadratic::Quadratic(double A, double B, double C, double D, double E, double F, double G, double H, double I, double J) : A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J)
{
    this->color = new Color();
}
Quadratic::~Quadratic()
{
    delete(this->color);
}

Point *Quadratic::intersect(Line *line)
{
    double a, b, c, x0, y0, z0, a0, b0, c0;
    x0 = line->getP()->getX();
    y0 = line->getP()->getY();
    z0 = line->getP()->getZ();
    a0 = line->getV()->getX();
    b0 = line->getV()->getY();
    c0 = line->getV()->getZ();

    a = (A * pow(a0, 2)) + (B * pow(b0, 2)) + (C * pow(c0, 2)) + (D * a0 * b0) + (E * a0 * c0) + (F * b0 * c0);
    b = (2 * ((A * x0 * a0) + (B * y0 * b0) + (C * z0 * c0))) + (x0 * b0) + (y0 * a0) + (x0 * c0) + (z0 * a0) + (y0 * c0) + (z0 * b0) + (G * a0) + (H * b0) + (I * c0);
    c = (A * pow(x0, 2)) + (B * pow(y0, 2)) + (C * pow(z0, 2)) + (x0 * y0) + (x0 * z0) + (y0 * z0) + (G * x0) + (H * y0) + (I * z0) + J;
    if (a == 0) {
        double s1 = -b / a;
        double x1, y1, z1;
        x1 = x0 + a0 * s1;
        y1 = y0 + b0 * s1;
        z1 = z0 + c0 * s1;
        return new Point(x1, y1, z1);
    }
    double delta = pow(b, 2) - (4 * a * c);
    if (delta < 0){
        return NULL;
    } else if (delta == 0) {
        double s1 = -b / (2 * a);
        double x1, y1, z1;
        x1 = x0 + a0 * s1;
        y1 = y0 + b0 * s1;
        z1 = z0 + c0 * s1;
        return new Point(x1, y1, z1);
    } else {
        double s1 = (-b + sqrt(delta)) / (2 * a);
        double s2 = (-b - sqrt(delta)) / (2 * a);
        double x1, y1, z1, x2, y2, z2;
        x1 = x0 + a0 * s1;
        y1 = y0 + b0 * s1;
        z1 = z0 + c0 * s1;
        x2 = x0 + a0 * s2;
        y2 = y0 + b0 * s2;
        z2 = z0 + c0 * s2;
        Point *p1, *p2;
        p1 = new Point(x1, y1, z1);
        p2 = new Point(x2, y2, z2);
        if(line->getP()->distWith(*p1) < line->getP()->distWith(*p2)){
            delete(p2);
            return p1;
        } else {
            delete(p1);
            return p2;
        }
    }
}