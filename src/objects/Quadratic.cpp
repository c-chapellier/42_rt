#include "Quadratic.hpp"

Quadratic::Quadratic(double A, double B, double C, double D, double E, double F, double G, double H, double I, double J)
    : Object(), A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J), p(0, 0, 0)
{
}

Quadratic::Quadratic(const Point &p, double A, double B, double C, double D, double E, double F, double G, double H, double I, double J)
    : A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J), p(p)
{
}

Quadratic::Quadratic(const Point &p, double A, double B, double C, double D, double E, double F, double G, double H, double I, double J, const Color &color)
    : Object(color), A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J), p(p)
{
}
Quadratic::~Quadratic()
{
}

std::vector<Intersection> Quadratic::intersect(const Line &line) const
{
    double x0, y0, z0, x1, y1, z1, a, b, c, t0, t1, t2;
    x0 = this->p.getX();
    y0 = this->p.getY();
    z0 = this->p.getZ();
    x1 = line.getP().getX();
    y1 = line.getP().getY();
    z1 = line.getP().getZ();
    a = line.getV().getX();
    b = line.getV().getY();
    c = line.getV().getZ();

    t0 = A * pow(x1 - x0, 2) + 
        B * pow(y1 - y0, 2) + 
        C * pow(z1 - z0, 2) + 
        D * (x1 - x0) * (y1 - y0) + 
        E * (x1 - x0) * (z1 - z0) + 
        F * (y1 - y0) * (z1 - z0) + 
        G * (x1 - x0) + 
        H * (y1 - y0) + 
        I * (z1 - z0) + 
        J;

    t1 = A * 2 * (x1 - x0) * a +
        B * 2 * (y1 - y0) * b +
        C * 2 * (z1 - z0) * c +
        D * (x1 - x0) * b +
        D * (y1 - y0) * a +
        E * (x1 - x0) * c +
        E * (z1 - z0) * a +
        F * (y1 - y0) * c +
        F * (z1 - z0) * b +
        G * a +
        H * b +
        I * c;
    
    t2 = A * pow(a, 2) +
        B * pow(b, 2) +
        C * pow(c, 2) +
        D * a * b +
        E * a * c +
        F * b * c;

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(t2, t1, t0);

    std::vector<Intersection> intersections;
    for (double s : solutions) {
        if (s > 0.00001) {
            double x = x1 + a * s;
            double y = y1 + b * s;
            double z = z1 + c * s;
            intersections.push_back(Intersection(x, y, z, s, (Object*)this));
        }
    }

    return intersections;
}

// Surface: F(x, y, z) = 0
// Point: (x₀, y₀, z₀)
// Tangent Plane: Fx(x₀, y₀, z₀)(x - x₀) + Fy(x₀, y₀, z₀)(y - y₀) + Fz(x₀, y₀, z₀)(z - z₀) = 0
// Resolution:
// Ax² + By² + Cz² + Dx + Ey + Fz + Gxy + Hxz + Iyz + K = 0
// Fx => 2Ax + D + Gy + Hz
// Fy => 2By + E + Gx + Iz
// Fz => 2Cz + F + Hx + Iy
// Fx(x - x₀) + Fy(y - y₀) + Fz(z -z₀) = 0 : Plane equation
Plane Quadratic::tangentAt(const Point &p) const
{
    double a, b, c, d, e, f, g, h, i, x0, y0, z0;
    x0 = this->p.getX();
    y0 = this->p.getY();
    z0 = this->p.getZ();

    a = A;
    b = B;
    c = C;
    d = -(2 * A * x0) -
        (D * y0) -
        (E * z0) +
        G;
    e = -(2 * B * y0) -
        (D * x0) -
        (F * z0) +
        H;
    f = -(2 * C * z0) -
        (E * x0) -
        (F * y0) +
        I;
    g = D;
    h = E;
    i = F;

    double Fx, Fy, Fz;

    Fx = 2 * a * p.getX() +
        d +
        g * p.getY() +
        h * p.getZ();
    Fy = 2 * b * p.getY() +
        e +
        g * p.getX() +
        i * p.getZ();
    Fz = 2 * c * p.getZ() +
        f +
        h * p.getX() +
        i * p.getY();

    return Plane(p, Fx, Fy, Fz);
}

double Quadratic::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return this->tangentAt(intersection.getP()).angleWith(line);
}

Line Quadratic::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    return this->tangentAt(intersection.getP()).getReflectedRayAt(intersection, line);
}

Color Quadratic::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
{
    screenWidth = intersection.getX();

    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        double p = (double)((double)height / (double)screen_height);
        return Color(
            this->getColor(0).getR() + (int)((double)((double)this->getColor(1).getR() - (double)this->getColor(0).getR()) * p),
            this->getColor(0).getG() + (int)((double)((double)this->getColor(1).getG() - (double)this->getColor(0).getG()) * p),
            this->getColor(0).getB() + (int)((double)((double)this->getColor(1).getB() - (double)this->getColor(0).getB()) * p),
            this->getColor(0).getO() + (int)((double)((double)this->getColor(1).getO() - (double)this->getColor(0).getO()) * p)
        );
    } else if (this->texture.getType() == "Grid") {
        return this->getColor(((height / this->texture.getValue1()) + (width / this->texture.getValue2())) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        return this->getColor((width / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        return this->getColor((height / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "Image") {
        throw "Texture type Image ca't be apply here";
    } else {
        throw "Should never happen";
    }
}