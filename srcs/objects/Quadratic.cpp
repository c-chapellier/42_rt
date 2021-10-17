#include "Quadratic.hpp"

Quadratic::Quadratic(double A, double B, double C, double D, double E, double F, double G, double H, double I, double J) : Object(), A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J)
{
    this->p = new Point(0, 0, 0);
}
Quadratic::Quadratic(Point &p, double A, double B, double C, double D, double E, double F, double G, double H, double I, double J, Color *color) : Object(color), A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J)
{
    this->p = new Point(p);
}
Quadratic::~Quadratic()
{
    delete(this->p);
}

Point *Quadratic::intersect(Line *line)
{
    double x0, y0, z0, x1, y1, z1, a, b, c, t0, t1, t2, delta;
    x0 = this->p->getX();
    y0 = this->p->getY();
    z0 = this->p->getZ();
    x1 = line->getP()->getX();
    y1 = line->getP()->getY();
    z1 = line->getP()->getZ();
    a = line->getV()->getX();
    b = line->getV()->getY();
    c = line->getV()->getZ();

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

    delta = pow(t1, 2) - (4 * t2 * t0);

    if (t2 == 0) {
        double s1 = -t0 / t1;
        double x, y, z;
        x = x1 + a * s1;
        y = y1 + b * s1;
        z = z1 + c * s1;
        return new Point(x, y, z);
    }
    
    if (delta < 0){
        return NULL;
    } else if (delta == 0) {
        double s1 = -t1 / (2 * t2);
        double x, y, z;
        x = x1 + a * s1;
        y = y1 + b * s1;
        z = z1 + c * s1;
        if(s1 <= 0)
            return NULL;
        return new Point(x, y, z);
    } else {
        double s1 = (-t1 + sqrt(delta)) / (2 * t2);
        double s2 = (-t1 - sqrt(delta)) / (2 * t2);
        double x_1, y_1, z_1, x_2, y_2, z_2;
        x_1 = x1 + a * s1;
        y_1 = y1 + b * s1;
        z_1 = z1 + c * s1;
        x_2 = x1 + a * s2;
        y_2 = y1 + b * s2;
        z_2 = z1 + c * s2;
        if(s1 <= 2 && s2 <= 0)
            return NULL;
        else if(s1 > 0 && s2 <=0)
            return new Point(x_1, y_1, z_1);
        else if(s2 > 0 && s1 <=0)
            return new Point(x_2, y_2, z_2);
        Point *p1, *p2;
        p1 = new Point(x_1, y_1, z_1);
        p2 = new Point(x_2, y_2, z_2);
        if(line->getP()->distWith(*p1) < line->getP()->distWith(*p2)){
            delete(p2);
            return p1;
        } else {
            delete(p1);
            return p2;
        }
    }
}

// Surface: F(x, y, z) = 0
// Point: (x₀, y₀, z₀)
// Tangent Plane: Fx(x₀, y₀, z₀)(x - x₀) + Fy(x₀, y₀, z₀)(y - y₀) + Fz(x₀, y₀, z₀)(z - z₀) = 0
// Resolution:
// Ax² + By² +Cz² + Dx + Ey + Fz + Gxy + Hxz + Iyz + K = 0
// Fx => 2Ax + D + Gy + Hz
// Fy => 2By + E + Gx + Iz
// Fz => 2Cz + F + Hx + Iy
// Fx(x - x₀) + Fy(y - y₀) + Fz(z -z₀) = 0 : Plane equation
Plane *Quadratic::tangentAt(Point *p)
{
    double a, b, c, d, e, f, g, h, i, x0, y0, z0;
    x0 = this->p->getX();
    y0 = this->p->getY();
    z0 = this->p->getZ();

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

    Fx = 2 * a * p->getX() +
        d +
        g * p->getY() +
        h * p->getZ();
    Fy = 2 * b * p->getY() +
        e +
        g * p->getX() +
        i * p->getZ();
    Fz = 2 * c * p->getZ() +
        f +
        h * p->getX() +
        i * p->getY();
    return new Plane(p, Fx, Fy, Fz);
}

double Quadratic::angleWith(Line *line)
{
    return this->tangentAt(this->intersect(line))->angleWith(line);
}
