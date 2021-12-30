#include "QuarticSurface.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

QuarticSurface::QuarticSurface()
{
    this->C1 = 0;
    this->C2 = 0;
    this->C3 = 0;
    this->C4 = 0;
    this->C5 = 0;
    this->C6 = 0;
    this->C7 = 0;
    this->C8 = 0;
    this->C9 = 0;
    this->C10 = 0;
    this->C11 = 0;
    this->C12 = 0;
    this->C13 = 0;
    this->C14 = 0;
    this->C15 = 0;
    this->C16 = 0;
    this->C17 = 0;
    this->C18 = 0;
    this->C19 = 0;
    this->C20 = 0;
    this->C21 = 0;
    this->C22 = 0;
    this->C23 = 0;
    this->C24 = 0;
    this->C25 = 0;
    this->C26 = 0;
    this->C27 = 0;
    this->C28 = 0;
    this->C29 = 0;
    this->C30 = 0;
    this->C31 = 0;
    this->C32 = 0;
    this->C33 = 0;
    this->C34 = 0;
    this->C35 = 0;
}
QuarticSurface::~QuarticSurface() {}

/* * * * * * * * * * * * * * * * * * * * *

*                SETTER                  *

* * * * * * * * * * * * * * * * * * * * */

void QuarticSurface::setX4(double C1) { this->C1 = C1; }
void QuarticSurface::setY4(double C2) { this->C2 = C2; }
void QuarticSurface::setZ4(double C3) { this->C3 = C3; }
void QuarticSurface::setX3Y(double C4) { this->C4 = C4; }
void QuarticSurface::setX3Z(double C5) { this->C5 = C5; }
void QuarticSurface::setY3X(double C6) { this->C6 = C6; }
void QuarticSurface::setY3Z(double C7) { this->C7 = C7; }
void QuarticSurface::setZ3X(double C8) { this->C8 = C8; }
void QuarticSurface::setZ3Y(double C9) { this->C9 = C9; }
void QuarticSurface::setX2Y2(double C10) { this->C10 = C10; }
void QuarticSurface::setX2Z2(double C11) { this->C11 = C11; }
void QuarticSurface::setY2Z2(double C12) { this->C12 = C12; }
void QuarticSurface::setX2YZ(double C13) { this->C13 = C13; }
void QuarticSurface::setY2XZ(double C14) { this->C14 = C14; }
void QuarticSurface::setZ2XY(double C15) { this->C15 = C15; }
void QuarticSurface::setX3(double C16) { this->C16 = C16; }
void QuarticSurface::setY3(double C17) { this->C17 = C17; }
void QuarticSurface::setZ3(double C18) { this->C18 = C18; }
void QuarticSurface::setX2Y(double C19) { this->C19 = C19; }
void QuarticSurface::setX2Z(double C20) { this->C20 = C20; }
void QuarticSurface::setY2X(double C21) { this->C21 = C21; }
void QuarticSurface::setY2Z(double C22) { this->C22 = C22; }
void QuarticSurface::setZ2X(double C23) { this->C23 = C23; }
void QuarticSurface::setZ2Y(double C24) { this->C24 = C24; }
void QuarticSurface::setXYZ(double C25) { this->C25 = C25; }
void QuarticSurface::setX2(double C26) { this->C26 = C26; }
void QuarticSurface::setY2(double C27) { this->C27 = C27; }
void QuarticSurface::setZ2(double C28) { this->C28 = C28; }
void QuarticSurface::setXY(double C29) { this->C29 = C29; }
void QuarticSurface::setXZ(double C30) { this->C30 = C30; }
void QuarticSurface::setYZ(double C31) { this->C31 = C31; }
void QuarticSurface::setX(double C32) { this->C32 = C32; }
void QuarticSurface::setY(double C33) { this->C33 = C33; }
void QuarticSurface::setZ(double C34) { this->C34 = C34; }   
void QuarticSurface::setK(double C35) { this->C35 = C35; }

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void QuarticSurface::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Line local_line = this->tr.apply(line, TO_LOCAL);
    double a = local_line.getX();
    double b = local_line.getY();
    double c = local_line.getZ();
    double alpha = local_line.getPX();
    double beta = local_line.getPY();
    double gama = local_line.getPZ();

    double t4 = C1 * pow(a, 4) +
                C2 * pow(b, 4) +
                C3 * pow(c, 4) +
                C4 * pow(a, 3) * b +
                C5 * pow(a, 3) * c +
                C6 * pow(b, 3) * a +
                C7 * pow(b, 3) * c +
                C8 * pow(c, 3) * a +
                C9 * pow(c, 3) * b +
                C10 * pow(a, 2) * pow(b, 2) +
                C11 * pow(a, 2) * pow(c, 2) +
                C12 * pow(b, 2) * pow(c, 2) +
                C13 * pow(a, 2) * b * c +
                C14 * pow(b, 2) * a * c +
                C15 * pow(c, 2) * a * b;

    double t3 = C1 * 4 * pow(a, 3) * alpha +
                C2 * 4 * pow(b, 3) * beta +
                C3 * 4 * pow(c, 3) * gama +
                C4 * ((pow(a, 3) * beta) + (3 * pow(a, 2) * b * alpha)) +
                C5 * ((pow(a, 3) * gama) + (3 * pow(a, 2) * c * alpha)) +
                C6 * ((pow(b, 3) * alpha) + (3 * pow(b, 2) * a * beta)) +
                C7 * ((pow(b, 3) * gama) + (3 * pow(b, 2) * c * beta)) +
                C8 * ((pow(c, 3) * alpha) + (3 * pow(c, 2) * a * gama)) +
                C9 * ((pow(c, 3) * beta) + (3 * pow(c, 2) * b * gama)) +
                C10 * ((2 * pow(a, 2) * b * beta) + (2 * a * alpha * pow(b, 2))) +
                C11 * ((2 * pow(a, 2) * c * gama) + (2 * a * alpha * pow(c, 2))) +
                C12 * ((2 * pow(b, 2) * c * gama) + (2 * b * beta * pow(c, 2))) +
                C13 * ((pow(a, 2) * b * gama) + (pow(a, 2) * c * beta) + (2 * a * alpha * b * c)) +
                C14 * ((pow(b, 2) * a * gama) + (pow(b, 2) * c * alpha) + (2 * b * beta * a * c)) +
                C15 * ((pow(c, 2) * a * beta) + (pow(c, 2) * b * alpha) + (2 * c * gama * a * b)) +
                C16 * pow(a, 3) +
                C17 * pow(b, 3) +
                C18 * pow(c, 3) +
                C19 * pow(a, 2) * b +
                C20 * pow(a, 2) * c +
                C21 * pow(b, 2) * a +
                C22 * pow(b, 2) * c +
                C23 * pow(c, 2) * a +
                C24 * pow(c, 2) * b +
                C25 * a * b * c;

    double t2 = C1 * 6 * pow(a, 2) * pow(alpha, 2) +
                C2 * 6 * pow(b, 2) * pow(beta, 2) +
                C3 * 6 * pow(c, 2) * pow(gama, 2) +
                C4 * ((3 * pow(a, 2) * alpha * beta) + (3 * a * b *pow(alpha, 2))) +
                C5 * ((3 * pow(a, 2) * alpha * gama) + (3 * a * c *pow(alpha, 2))) +
                C6 * ((3 * pow(b, 2) * beta * alpha) + (3 * b * a *pow(beta, 2))) +
                C7 * ((3 * pow(b, 2) * beta * gama) + (3 * b * c *pow(beta, 2))) +
                C8 * ((3 * pow(c, 2) * gama * alpha) + (3 * c * a *pow(gama, 2))) +
                C9 * ((3 * pow(c, 2) * gama * beta) + (3 * c * b *pow(gama, 2))) +
                C10 * ((pow(a, 2) * pow(beta, 2)) + (4 * a * b * alpha * beta) + (pow(alpha, 2) * pow(b, 2))) +
                C11 * ((pow(a, 2) * pow(gama, 2)) + (4 * a * c * alpha * gama) + (pow(alpha, 2) * pow(c, 2))) +
                C12 * ((pow(b, 2) * pow(gama, 2)) + (4 * b * c * beta * gama) + (pow(beta, 2) * pow(c, 2))) +
                C13 * ((pow(a, 2) * beta * gama) + (2 * a * alpha * b * gama) + (2 * a * alpha * c * beta) + (pow(alpha, 2) * b * c)) +
                C14 * ((pow(b, 2) * alpha * gama) + (2 * b * beta * a * gama) + (2 * b * beta * c * alpha) + (pow(beta, 2) * a * c)) +
                C15 * ((pow(c, 2) * alpha * beta) + (2 * c * gama * a * beta) + (2 * c * gama * b * alpha) + (pow(gama, 2) * a * b)) +
                C16 * 3 * pow(a, 2) * alpha +
                C17 * 3 * pow(b, 2) * beta +
                C18 * 3 * pow(c, 2) * gama +
                C19 * ((2 * a * b * alpha) + (pow(a, 2) * beta)) +
                C20 * ((2 * a * c * alpha) + (pow(a, 2) * gama)) +
                C21 * ((2 * b * a * beta) + (pow(b, 2) * alpha)) +
                C22 * ((2 * b * c * beta) + (pow(b, 2) * gama)) +
                C23 * ((2 * c * a * gama) + (pow(c, 2) * alpha)) +
                C24 * ((2 * c * b * beta) + (pow(c, 2) * beta)) +
                C25 * ((a * c * beta) + (b * c * alpha) + (a * b * gama)) +
                C26 * pow(a, 2) +
                C27 * pow(b, 2) +
                C28 * pow(c, 2) +
                C29 * a * b +
                C30 * a * c +
                C31 * b * c;

    double t1 = C1 * 4 * a * pow(alpha, 3) +
                C2 * 4 * b * pow(beta, 3) +
                C3 * 4 * c * pow(gama, 3) +
                C4 * ((3 * a * pow(alpha, 2) * beta) + (pow(alpha, 3) * beta)) +
                C5 * ((3 * a * pow(alpha, 2) * gama) + (pow(alpha, 3) * gama)) +
                C6 * ((3 * b * pow(beta, 2) * alpha) + (pow(beta, 3) * alpha)) +
                C7 * ((3 * b * pow(beta, 2) * gama) + (pow(beta, 3) * gama)) +
                C8 * ((3 * c * pow(gama, 2) * alpha) + (pow(gama, 3) * alpha)) +
                C9 * ((3 * c * pow(gama, 2) * beta) + (pow(gama, 3) * beta)) +
                C10 * ((2 * alpha * pow(beta, 2)) + (2 * pow(alpha, 2) * b * beta)) +
                C11 * ((2 * alpha * pow(gama, 2)) + (2 * pow(alpha, 2) * c * gama)) +
                C12 * ((2 * beta * pow(gama, 2)) + (2 * pow(beta, 2) * c * gama)) +
                C13 * ((2 * a * alpha * beta * gama) + (pow(alpha, 2) * b * gama) + (pow(alpha, 2) * c * beta)) +
                C14 * ((2 * b * alpha * beta * gama) + (pow(beta, 2) * a * gama) + (pow(beta, 2) * c * alpha)) +
                C15 * ((2 * c * alpha * beta * gama) + (pow(gama, 2) * a * beta) + (pow(gama, 2) * b * alpha)) +
                C16 * 3 * pow(alpha, 2) * a +
                C17 * 3 * pow(beta, 2) * b +
                C18 * 3 * pow(gama, 2) * c +
                C19 * ((pow(a, 2) * b) + (2 * a * alpha * beta)) +
                C20 * ((pow(a, 2) * c) + (2 * a * alpha * gama)) +
                C21 * ((pow(b, 2) * a) + (2 * b * beta * alpha)) +
                C22 * ((pow(b, 2) * c) + (2 * b * beta * gama)) +
                C23 * ((pow(c, 2) * a) + (2 * c * gama * alpha)) +
                C24 * ((pow(c, 2) * b) + (2 * c * gama * beta)) +
                C25 * ((c * alpha * beta) + (b * alpha * gama) + (a * beta * gama)) +
                C26 * 2 * a * alpha +
                C27 * 2 * b * beta +
                C28 * 2 * c * gama +
                C29 * ((a * beta) + (b * alpha)) +
                C30 * ((a * gama) + (c * alpha)) +
                C31 * ((b * gama) + (c * beta)) +
                C32 * a +
                C33 * b +
                C34 * c;

    double t0 = C1 * pow(alpha, 4) +
                C2 * pow(beta, 4) +
                C3 * pow(gama, 4) +
                C4 * pow(alpha, 3) * beta +
                C5 * pow(alpha, 3) * gama +
                C6 * pow(beta, 3) * alpha +
                C7 * pow(beta, 3) * gama +
                C8 * pow(gama, 3) * alpha +
                C9 * pow(gama, 3) * beta +
                C10 * pow(alpha, 2) * pow(beta, 2) +
                C11 * pow(alpha, 2) * pow(gama, 2) +
                C12 * pow(beta, 2) * pow(gama, 2) +
                C13 * pow(alpha, 2) * beta * gama +
                C14 * pow(beta, 2) * alpha * gama +
                C15 * pow(gama, 2) * alpha * beta +
                C16 * pow(alpha, 3) +
                C17 * pow(beta, 3) +
                C18 * pow(gama, 3) +
                C19 * pow(a, 2) * beta +
                C20 * pow(a, 2) * gama +
                C21 * pow(b, 2) * alpha +
                C22 * pow(b, 2) * gama +
                C23 * pow(c, 2) * alpha +
                C24 * pow(c, 2) * beta +
                C25 * alpha * beta * gama +
                C26 * pow(alpha, 2) +
                C27 * pow(beta, 2) +
                C28 * pow(gama, 2) +
                C29 * alpha * beta +
                C30 * alpha * gama +
                C31 * beta + gama +
                C32 * alpha +
                C33 * beta +
                C34 * gama +
                C35;

    std::list<double> solutions = EquationSolver::solveQuarticEquation(t4, t3, t2, t1, t0);
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

Plane QuarticSurface::tangentAt(const Point &intersection) const
{
    Point local_point = this->tr.apply(intersection, TO_LOCAL);
    double x = local_point.getX();
    double y = local_point.getY();
    double z = local_point.getZ();

    double fx = C1 * 4 * pow(x, 3) +
                C4 * 3 * pow(x, 2) * (y) +
                C5 * 3 * pow(x, 2) * (y) +
                C6 * pow(y, 3) +
                C8 * pow(z, 3) +
                C10 * 2 * (x) * pow(y, 2) +
                C11 * 2 * (x) * pow(z, 2) +
                C13 * 2 * (x) * (y) * (z) +
                C14 * pow(y, 2) * (z) +
                C15 * pow(z, 2) * (y) +
                C16 * 3 * pow(x, 2) +
                C19 * 2 * (x) * (y) +
                C20 * 2 * (x) * (z) +
                C21 * pow(y, 2) +
                C23 * pow(z, 2) +
                C25 * (y) * (z) +
                C26 * 2 * (x) +
                C29 * (y) +
                C30 * (z) +
                C32;

    double fy = C2 * 4 * pow(y, 3) +
                C4 * pow(x, 3) +
                C6 * 3 * pow(y, 2) * (x) +
                C7 * 3 * pow(y, 2) * (z) +
                C9 * pow(z, 3) +
                C10 * 2 * pow(x, 2) * (y) +
                C12 * 2 * pow(z, 2) * (y) +
                C13 * pow(x, 2) * (z) +
                C14 * 2 * (x) * (y) * (z) +
                C15 * pow(z, 2) * (x) +
                C17 * 3 * pow(y, 2) +
                C19 * pow(x, 2) +
                C21 * 2 * (y) * (x) +
                C22 * 2 * (y) * (z) +
                C24 * pow(z, 2) +
                C25 * (x) * (z) +
                C27 * 2 * (y) +
                C29 * (x) +
                C31 * (z) +
                C33;

    double fz = C3 * 4 * pow(z, 3) +
                C5 * pow(x, 3) +
                C7 * pow(y, 3) +
                C8 * 3 * pow(z, 2) * (x) +
                C9 * 3 * pow(z, 2) * (y) +
                C11 * 2 * pow(x, 2) * (z) +
                C12 * 2 * pow(y, 2) * (z) +
                C13 * pow(x, 2) * (y) +
                C14 * pow(y, 2) * (x) +
                C15 * 2 * (x) * (y) * (z) +
                C18 * 3 * pow(z, 2) +
                C20 * pow(x, 2) +
                C22 * pow(y, 2) +
                C23 * 2 * (z) * (x) +
                C24 * 2 * (z) * (y) +
                C25 * (x) * (y) +
                C28 * 2 * (z) +
                C30 * (x) +
                C31 * (y) +
                C34;

    Point tmp = this->tr.apply(Point(fx, fy, fz), TO_REAL);
    return Plane(intersection, tmp);
}

double QuarticSurface::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return this->tangentAt(intersection.getRealPoint()).angleWith(line);
}

Line QuarticSurface::getReflectedRayAt(const Intersection &intersection, const Line &line) const
{
    return this->tangentAt(intersection.getRealPoint()).getReflectedRayAt(intersection, line);
}

Color QuarticSurface::getColorAt(const Point &intersection) const
{
    if (this->texture.getType() == UNIFORM) {
        return this->getColor();
    } else {
        throw "Texture unsupported";
    }
}