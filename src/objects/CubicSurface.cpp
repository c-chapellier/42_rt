#include "CubicSurface.hpp"

CubicSurface::CubicSurface(double px, double py, double pz) : p(px, py, pz)
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

std::vector<Intersection> CubicSurface::intersect(const Line &line) const
{
    double a = line.getV().getX();
    double b = line.getV().getY();
    double c = line.getV().getZ();
    double alpha = line.getP().getX() - this->p.getX();
    double beta = line.getP().getY() - this->p.getY();
    double gama = line.getP().getZ() - this->p.getZ();

    double t3 = A * pow(a, 3) +
                B * pow(b, 3) +
                C * pow(c, 3) +
                D * pow(a, 2) * b +
                E * pow(a, 2) * c +
                F * pow(b, 2) * a +
                G * pow(b, 2) * c +
                H * pow(c, 2) * a +
                I * pow(c, 2) * b +
                J * a * b * c;
    
    double t2 = A * 3 * pow(a, 2) * alpha +
                B * 3 * pow(b, 2) * beta +
                C * 3 * pow(c, 2) * gama +
                D * ((2 * a * b * alpha) + (pow(a, 2) * beta)) +
                E * ((2 * a * c * alpha) + (pow(a, 2) * gama)) +
                F * ((2 * b * a * beta) + (pow(b, 2) * alpha)) +
                G * ((2 * b * c * beta) + (pow(b, 2) * gama)) +
                H * ((2 * c * a * gama) + (pow(c, 2) * alpha)) +
                I * ((2 * c * b * beta) + (pow(c, 2) * beta)) +
                J * ((a * c * beta) + (b * c * alpha) + (a * b * gama)) +
                K * pow(a, 2) +
                L * pow(b, 2) +
                M * pow(c, 2) +
                N * a * b +
                O * a * c +
                P * b * c;

    double t1 = A * 3 * pow(alpha, 2) * a +
                B * 3 * pow(beta, 2) * b +
                C * 3 * pow(gama, 2) * c +
                D * ((pow(a, 2) * b) + (2 * a * alpha * beta)) +
                E * ((pow(a, 2) * c) + (2 * a * alpha * gama)) +
                F * ((pow(b, 2) * a) + (2 * b * beta * alpha)) +
                G * ((pow(b, 2) * c) + (2 * b * beta * gama)) +
                H * ((pow(c, 2) * a) + (2 * c * gama * alpha)) +
                I * ((pow(c, 2) * b) + (2 * c * gama * beta)) +
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

    double t0 = A * pow(alpha, 3) +
                B * pow(beta, 3) +
                C * pow(gama, 3) +
                D * pow(a, 2) * beta +
                E * pow(a, 2) * gama +
                F * pow(b, 2) * alpha +
                G * pow(b, 2) * gama +
                H * pow(c, 2) * alpha +
                I * pow(c, 2) * beta +
                J * alpha * beta * gama +
                K * pow(alpha, 2) +
                L * pow(beta, 2) +
                M * pow(gama, 2) +
                N * alpha * beta +
                O * alpha * gama +
                P * beta + gama +
                Q * alpha +
                R * beta +
                S * gama +
                T;

    std::list<double> solutions = EquationSolver::solveCubicEquation(t3, t2, t1, t0);

    std::vector<Intersection> intersections;
    for (double s : solutions) {
        if (s > 0) {
            Point p(
                line.getP().getX() + s * line.getV().getX(),
                line.getP().getY() + s * line.getV().getY(),
                line.getP().getZ() + s * line.getV().getZ()
            );
            intersections.push_back(Intersection(p, s, (Object*)this));
        }
    }
    return intersections;
}

Plane CubicSurface::tangentAt(const Point &intersection) const
{
    double x = intersection.getX();
    double y = intersection.getY();
    double z = intersection.getZ();
    double x0 = this->p.getX();
    double y0 = this->p.getY();
    double z0 = this->p.getZ();

    double fx = A * 3 * pow(x - x0, 2) +
                D * 2 * (x - x0) * (y - y0) +
                E * 2 * (x - x0) * (z - z0) +
                F * pow(y - y0, 2) +
                H * pow(z - z0, 2) +
                J * (y - y0) * (z - z0) +
                K * 2 * (x - x0) +
                N * (y - y0) +
                O * (z - z0) +
                Q;

    double fy = B * 3 * pow(y - y0, 2) +
                D * pow(x - x0, 2) +
                F * 2 * (y - y0) * (x - x0) +
                G * 2 * (y - y0) * (z - z0) +
                I * pow(z - z0, 2) +
                J * (x - x0) * (z - z0) +
                L * 2 * (y - y0) +
                N * (x - x0) +
                P * (z - z0) +
                R;

    double fz = C * 3 * pow(z - z0, 2) +
                E * pow(x - x0, 2) +
                G * pow(y - y0, 2) +
                H * 2 * (z - z0) * (x - x0) +
                I * 2 * (z - z0) * (y - y0) +
                J * (x - x0) * (y - y0) +
                M * 2 * (z - z0) +
                O * (x - x0) +
                P * (y - y0) +
                S;
    return Plane(intersection, fx, fy, fz); 
}

double CubicSurface::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return this->tangentAt(intersection.getP()).angleWith(line);
}

Line CubicSurface::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    return this->tangentAt(intersection.getP()).getReflectedRayAt(intersection, line);
}

Color CubicSurface::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
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