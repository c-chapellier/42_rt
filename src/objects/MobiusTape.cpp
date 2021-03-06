#include "MobiusTape.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

MobiusTape::MobiusTape(double A, double B, double C, double D, double E, double F, double G)
    : A(A), B(B), C(C), D(D), E(E), F(F), G(G)
{}

MobiusTape::~MobiusTape() {}

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void MobiusTape::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Line local_line = this->tr.apply(line, TO_LOCAL);

    double alpha = local_line.getPX();
    double beta = local_line.getPY();
    double gama = local_line.getPZ();

    double a = local_line.getX();
    double b = local_line.getY();
    double c = local_line.getZ();

    double x3 = A * pow(a, 2) * b +
                B * pow(c, 2) * b +
                C * pow(b, 3) -
                F * 2 * pow(a, 2) * c -
                G * 2 * pow(b, 2) * c;

    double x2 = A * pow(a, 2) * beta +
                A * 2 * alpha * a * b +
                B * pow(c, 2) * beta +
                B * 2 * gama * c * b -
                C * 3 * beta * pow(b, 2) -
                E * a * c -
                F * 2 * pow(a, 2) * gama -
                F * 2 * alpha * a * c -
                G * 2 * pow(b, 2) * gama -
                G * 2 * beta * b * c;
    
    double x1 = A * 2 * alpha * a * beta +
                A * pow(alpha, 2) * b +
                B * 2 * gama * c * b +
                B * pow(gama, 2) * b +
                C * pow(beta, 2) * b +
                B * b -
                E * gama * A -
                E * alpha * c -
                F * 2 * alpha * a * gama -
                F * 2 * pow(alpha, 2) * c -
                G * 2 * beta * c * gama -
                G * 2 * pow(beta, 2) * c;
    
    double x0 = A * pow(alpha, 2) * b +
                B * pow(gama, 2) * b -
                C * pow(beta, 3) -
                D * beta -
                E * alpha * gama -
                F * 2 * pow(alpha, 2) * c -
                G * 2 * pow(beta, 2) * c;

    std::list<double> solutions = EquationSolver::solveCubicEquation(x3, x2, x1, x0);

    for (double s : solutions) {
        if (s > 0.00001) {
            Point local_point(
                local_line.getPX() + s * local_line.getX(),
                local_line.getPY() + s * local_line.getY(),
                local_line.getPZ() + s * local_line.getZ()
            );
            Point real_point = this->tr.apply(local_point, TO_REAL);
            double dist = (real_point.getX() - line.getP().getX()) / line.getV().getX();
            intersections->push_back(Intersection(real_point, local_point, dist, (Object*)this));
        }
    }
}

Plane MobiusTape::tangentAt(const Point &intersection) const
{
    Point local_point = this->tr.apply(intersection, TO_LOCAL);

    double x, y, z;
    x = intersection.getX();
    y = intersection.getY();
    z = intersection.getZ();

    double fx = 2 * A * (x) * (y) -
                2 * E * (z) -
                4 * F * (x) * (z);

    double fy = A * pow((x), 2) +
                B * pow((z), 2) +
                3 * C * (y) -
                D -
                4 * G * (y) * (z);

    double fz = 2 * B * (y) * (z) -
                2 * E * (x) -
                2 * F * pow((x), 2) -
                2 * G * pow((y), 2);

    Point tmp = this->tr.apply(Point(fx, fy, fz), TO_REAL);
    return Plane(intersection, tmp);
}

double MobiusTape::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return this->tangentAt(intersection.getRealPoint()).angleWith(line);
}

Line MobiusTape::getReflectedRayAt(const Intersection &intersection, const Line &line) const
{
    return this->tangentAt(intersection.getRealPoint()).getReflectedRayAt(intersection, line);
}

Color MobiusTape::getColorAt(const Point &intersection) const
{
    if (this->texture.getType() == UNIFORM) {
        return this->getColor();
    } else {
        throw "Texture unsupported";
    }
}