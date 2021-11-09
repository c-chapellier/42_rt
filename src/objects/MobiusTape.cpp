#include "MobiusTape.hpp"

MobiusTape::MobiusTape(double px, double py, double pz) : p(px, py, pz), A(1), B(1), C(1), D(1), E(1), F(1), G(1)
{

}
MobiusTape::MobiusTape(double px, double py, double pz, double A, double B, double C, double D, double E, double F, double G)
: p(px, py, pz), A(A), B(B), C(C), D(D), E(E), F(F), G(G)
{

}
MobiusTape::~MobiusTape(){}

Point MobiusTape::intersect(const Line &line) const
{
    double alpha = line.getP().getX() - this->p.getX();
    double beta = line.getP().getY() - this->p.getY();
    double gama = line.getP().getZ() - this->p.getZ();

    double a = line.getV().getX();
    double b = line.getV().getY();
    double c = line.getV().getZ();

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

    double s = -1;
    for (double ss: solutions) {
        if ((ss < s && ss > 0) || (s < 0 && ss > 0))
            s = ss;
    }

    if (s < 0)
        throw NoInterException("Line do not intersect the mobius tape");

    Point p(
        line.getP().getX() + s * line.getV().getX(),
        line.getP().getY() + s * line.getV().getY(),
        line.getP().getZ() + s * line.getV().getZ()
    );
    return p;
}

Plane MobiusTape::tangentAt(const Point &intersection) const
{
    double x, x1, y, y1, z, z1;
    x = intersection.getX();
    x1 = this->p.getX();
    y = intersection.getY();
    y1 = this->p.getY();
    z = intersection.getZ();
    z1 = this->p.getZ();

    double fx = 2 * A * (x - x1) * (y - y1) -
                2 * E * (z - z1) -
                4 * F * (x - x1) * (z - z1);

    double fy = A * pow((x - x1), 2) +
                B * pow((z - z1), 2) +
                3 * C * (y - y1) -
                D -
                4 * G * (y - y1) * (z - z1);

    double fz = 2 * B * (y - y1) * (z - z1) -
                2 * E * (x - x1) -
                2 * F * pow((x - x1), 2) -
                2 * G * pow((y - y1), 2);

    return Plane(intersection, fx, fy, fz);
}

double MobiusTape::angleWith(const Line &line) const
{
    return this->tangentAt(this->intersect(line)).angleWith(line);
}

Color MobiusTape::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
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