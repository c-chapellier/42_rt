#include "QuadraticSurface.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

QuadraticSurface::QuadraticSurface(double A, double B, double C, double D, double E, double F, double G, double H, double I, double J)
    : Object(), A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J)
{}

QuadraticSurface::~QuadraticSurface() {}

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void QuadraticSurface::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Vector local_vector = this->tr.apply(line.getV(), TO_LOCAL);
    double x1, y1, z1, a, b, c, t0, t1, t2;
    x1 = local_vector.getP1()->getX();
    y1 = local_vector.getP1()->getY();
    z1 = local_vector.getP1()->getZ();
    a = local_vector.getX();
    b = local_vector.getY();
    c = local_vector.getZ();

    t0 = A * x1 * x1 + 
        B * y1 * y1 + 
        C * z1 * z1 + 
        D * x1 * y1 + 
        E * x1 * z1 + 
        F * y1 * z1 + 
        G * x1 + 
        H * y1 + 
        I * z1 + 
        J;

    t1 = A * 2 * x1 * a +
        B * 2 * y1 * b +
        C * 2 * z1 * c +
        D * x1 * b +
        D * y1 * a +
        E * x1 * c +
        E * z1 * a +
        F * y1 * c +
        F * z1 * b +
        G * a +
        H * b +
        I * c;
    
    t2 = A * a * a +
        B * b * b +
        C * c * c +
        D * a * b +
        E * a * c +
        F * b * c;

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(t2, t1, t0);
    for (double s : solutions) {
        if (s > 0.00001) {
            Point local_point(
                x1 + a * s,
                y1 + b * s,
                z1 + c * s
            );
            Point real_point = this->tr.apply(local_point, TO_REAL);
            double dist = (real_point.getX() - line.getP().getX()) / line.getV().getX();
            intersections->push_back(Intersection(real_point, local_point, dist, (Object*)this));
        }
    }
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
Plane QuadraticSurface::tangentAt(const Point &p) const
{
    Point local_point = this->tr.apply(p, TO_LOCAL);

    double a, b, c, d, e, f, g, h, i;

    a = A;
    b = B;
    c = C;
    d = G;
    e = H;
    f = I;
    g = D;
    h = E;
    i = F;

    double Fx, Fy, Fz;

    Fx = 2 * a * local_point.getX() +
        d +
        g * local_point.getY() +
        h * local_point.getZ();
    Fy = 2 * b * local_point.getY() +
        e +
        g * local_point.getX() +
        i * local_point.getZ();
    Fz = 2 * c * local_point.getZ() +
        f +
        h * local_point.getX() +
        i * local_point.getY();

    Point tmp = this->tr.apply(Point(Fx, Fy, Fz), TO_REAL);

    return Plane(p, tmp);
}

double QuadraticSurface::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return this->tangentAt(intersection.getRealPoint()).angleWith(line);
}

Line QuadraticSurface::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    return this->tangentAt(intersection.getRealPoint()).getReflectedRayAt(intersection, line);
}

Color QuadraticSurface::getColorAt(const Point &intersection) const
{
    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        throw "Texture unsupported";
    } else if (this->texture.getType() == "Grid") {
        throw "Texture unsupported";
    } else if (this->texture.getType() == "VerticalLined") {
        throw "Texture unsupported";
    } else if (this->texture.getType() == "HorizontalLined") {
        throw "Texture unsupported";
    } else if (this->texture.getType() == "Image") {
        throw "Texture unsupported";
    } else {
        throw "Should never happen";
    }
}