#include "CubicSurface.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

CubicSurface::CubicSurface()
{
    this->A = 0;
    this->B = 0;
    this->C = 0;
    this->D = 0;
    this->E = 0;
    this->F = 0;
    this->G = 0;
    this->H = 0;
    this->I = 0;
    this->J = 0;
    this->K = 0;
    this->L = 0;
    this->M = 0;
    this->N = 0;
    this->O = 0;
    this->P = 0;
    this->Q = 0;
    this->R = 0;
    this->S = 0;
    this->T = 0;
}
CubicSurface::~CubicSurface() {}

/* * * * * * * * * * * * * * * * * * * * *

*                SETTER                  *

* * * * * * * * * * * * * * * * * * * * */

void CubicSurface::setX3(double A) { this->A = A; }
void CubicSurface::setY3(double B) { this->B = B; }
void CubicSurface::setZ3(double C) { this->C = C; }
void CubicSurface::setX2Y(double D) { this->D = D; }
void CubicSurface::setX2Z(double E) { this->E = E; }
void CubicSurface::setY2X(double F) { this->F = F; }
void CubicSurface::setY2Z(double G) { this->G = G; }
void CubicSurface::setZ2X(double H) { this->H = H; }
void CubicSurface::setZ2Y(double I) { this->I = I; }
void CubicSurface::setXYZ(double J) { this->J = J; }
void CubicSurface::setX2(double K) { this->K = K; }
void CubicSurface::setY2(double L) { this->L = L; }
void CubicSurface::setZ2(double M) { this->M = M; }
void CubicSurface::setXY(double N) { this->N = N; }
void CubicSurface::setXZ(double O) { this->O = O; }
void CubicSurface::setYZ(double P) { this->P = P; }
void CubicSurface::setX(double Q) { this->Q = Q; }
void CubicSurface::setY(double R) { this->R = R; }
void CubicSurface::setZ(double S) { this->S = S; }
void CubicSurface::setK(double T) { this->T = T; }

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void CubicSurface::intersect(std::vector<Intersection> *intersections, const Line &line) const
{

    Line local_line = this->tr.apply(line, TO_LOCAL);

    double a = local_line.getX();
    double b = local_line.getY();
    double c = local_line.getZ();
    double alpha = local_line.getPX();
    double beta = local_line.getPY();
    double gama = local_line.getPZ();

    double t3 = A * a * a * a +
                B * b * b * b +
                C * c * c * c +
                D * a * a * b +
                E * a * a * c +
                F * b * b * a +
                G * b * b * c +
                H * c * c * a +
                I * c * c * b +
                J * a * b * c;
    
    double t2 = A * 3 * a * a * alpha +
                B * 3 * b * b * beta +
                C * 3 * c * c * gama +
                D * ((2 * a * b * alpha) + (a * a * beta)) +
                E * ((2 * a * c * alpha) + (a * a * gama)) +
                F * ((2 * b * a * beta) + (b * b * alpha)) +
                G * ((2 * b * c * beta) + (b * b * gama)) +
                H * ((2 * c * a * gama) + (c * c * alpha)) +
                I * ((2 * c * b * beta) + (c * c * beta)) +
                J * ((a * c * beta) + (b * c * alpha) + (a * b * gama)) +
                K * a * a +
                L * b * b +
                M * c * c +
                N * a * b +
                O * a * c +
                P * b * c;

    double t1 = A * 3 * alpha * alpha * a +
                B * 3 * beta * beta * b +
                C * 3 * gama * gama * c +
                D * ((a * a * b) + (2 * a * alpha * beta)) +
                E * ((a * a * c) + (2 * a * alpha * gama)) +
                F * ((b * b * a) + (2 * b * beta * alpha)) +
                G * ((b * b * c) + (2 * b * beta * gama)) +
                H * ((c * c * a) + (2 * c * gama * alpha)) +
                I * ((c * c * b) + (2 * c * gama * beta)) +
                J * ((c * alpha * beta) + (b * alpha * gama) + (a * beta * gama)) +
                K * 2 * a * alpha +
                L * 2 * b * beta +
                M * 2 * c * gama +
                N * ((a * beta) + (b * alpha)) +
                O * ((a * gama) + (c * alpha)) +
                P * ((b * gama) + (c * beta)) +
                Q * a +
                R * b +
                S * c;

    double t0 = A * alpha * alpha * alpha +
                B * beta * beta * beta +
                C * gama * gama * gama +
                D * a * a * beta +
                E * a * a * gama +
                F * b * b * alpha +
                G * b * b * gama +
                H * c * c * alpha +
                I * c * c * beta +
                J * alpha * beta * gama +
                K * alpha * alpha +
                L * beta * beta +
                M * gama * gama +
                N * alpha * beta +
                O * alpha * gama +
                P * beta + gama +
                Q * alpha +
                R * beta +
                S * gama +
                T;

    std::list<double> solutions = EquationSolver::solveCubicEquation(t3, t2, t1, t0);
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

Plane CubicSurface::tangentAt(const Point &intersection) const
{
    Point local_point = this->tr.apply(intersection, TO_LOCAL);
    double x = local_point.getX();
    double y = local_point.getY();
    double z = local_point.getZ();

    double fx = A * 3 * x * x +
                D * 2 * x * y +
                E * 2 * x * z +
                F * y * y +
                H * z * z +
                J * y * z +
                K * 2 * x +
                N * y +
                O * z +
                Q;

    double fy = B * 3 * y * y +
                D * x * x +
                F * 2 * y * x +
                G * 2 * y * z +
                I * z * z +
                J * x * z +
                L * 2 * y +
                N * x +
                P * z +
                R;

    double fz = C * 3 * z * z +
                E * x * x +
                G * y * y +
                H * 2 * z * x +
                I * 2 * z * y +
                J * x * y +
                M * 2 * z +
                O * x +
                P * y +
                S;
    
    Point tmp = this->tr.apply(Point(fx, fy, fz), TO_REAL);
    return Plane(intersection, tmp);
}

double CubicSurface::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return this->tangentAt(intersection.getRealPoint()).angleWith(line);
}

Line CubicSurface::getReflectedRayAt(const Intersection &intersection, const Line &line) const
{
    return this->tangentAt(intersection.getRealPoint()).getReflectedRayAt(intersection, line);
}

Color CubicSurface::getColorAt(const Point &intersection) const
{
    char type = this->texture.getType();

    if (type == UNIFORM) {
        return this->getColor();
    } else {
        throw "Texture unsupported";
    }
}