#include "Sphere.hpp"

Sphere::Sphere(double r) : Object(), r(r)
{

}

Sphere::~Sphere(){};

double Sphere::getR() const
{
    return this->r;
}

void Sphere::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Vector local = this->tr.apply(line.getV(), TO_LOCAL);
    local.normalize();
    double a, b, c;

    a = 1;

    b = 2 * local.getP1()->getX() * local.getX()
        + 2 * local.getP1()->getY() * local.getY()
        + 2 * local.getP1()->getZ() * local.getZ();
        
    c = local.getP1()->getX() * local.getP1()->getX()
        + local.getP1()->getY() * local.getP1()->getY()
        + local.getP1()->getZ() * local.getP1()->getZ()
        - this->r * this->r;

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);
    for (double s: solutions)
    {
        if (s > 0.00001)
        {
            Point local_intersection(
                local.getP1()->getX() + local.getX() * s,
                local.getP1()->getY() + local.getY() * s,
                local.getP1()->getZ() + local.getZ() * s
            );
            Point real_intersection = this->tr.apply(local_intersection, TO_REAL);
            double dist = (real_intersection.getX() - line.getP().getX()) / line.getV().getX();
            intersections->push_back(Intersection(real_intersection, local_intersection, dist, (Object*)this));
        }
    }
}

double Sphere::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return Plane(this->tr.getTranslation(), intersection.getRealPoint()).angleWith(line);
}

Line Sphere::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    Vector v(this->tr.getTranslation(), intersection.getRealPoint());
    Vector tmp = v.getReflectionOf(line.getV());
    tmp.setP1(intersection.getRealPoint());
    return Line(intersection.getRealPoint(), tmp);
}

Color Sphere::getColorAt(const Point &intersection) const
{
    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        /*
            To find the right color:
                - Get Z value as a ratio of height
        */
        double ratio = intersection.getZ() >= 0 ?
            (this->r - intersection.getZ()) / (2 * this->r):
            (this->r + abs(intersection.getZ())) / (2 * this->r);
            
        return Color(
            this->getColor(0).getR() + (int)((double)((double)this->getColor(1).getR() - (double)this->getColor(0).getR()) * ratio),
            this->getColor(0).getG() + (int)((double)((double)this->getColor(1).getG() - (double)this->getColor(0).getG()) * ratio),
            this->getColor(0).getB() + (int)((double)((double)this->getColor(1).getB() - (double)this->getColor(0).getB()) * ratio),
            this->getColor(0).getO() + (int)((double)((double)this->getColor(1).getO() - (double)this->getColor(0).getO()) * ratio)
        );
    } else if (this->texture.getType() == "Grid") {
        /*
            The first value of the texture is the number of vertical sections
            The second value is the number of horizontal lines
            To find the right color:
                - Combine vertical and horizontal
        */

        // Vertical
        double lineRadian = 360.0 / texture.getValue1();

        Vector v(0, 0, 0, intersection.getX(), intersection.getY(), 0);
        Vector x_axis(0, 1, 0);
        double alpha = v.angleWith(x_axis);
        alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);

        // Horizontal
        double ratio = intersection.getZ() >= 0 ?
            this->r - intersection.getZ() :
            this->r + abs(intersection.getZ());
        double lineWidth = this->r * 2 / texture.getValue1();

        return this->getColor(((int)(alpha / lineRadian) + (int)(ratio / lineWidth)) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        /*
            The first value of the texture is the number of vertical sections
            The second value is unused
            To find the right color:
                - Get section length as degree
                - Get the line width
        */

        double lineRadian = 360.0 / texture.getValue1();
        Vector v(0, 0, 0, intersection.getX(), intersection.getY(), 0);
        Vector x_axis(0, 1, 0);
        double alpha = v.angleWith(x_axis);
        alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);

        return this->getColor((int)(alpha / lineRadian) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        /*
            The first value of the texture is the number of horizontal lines
            The second value is unused
            To find the right color:
                - Get the height ratio
                - Get the line width
        */
        double ratio = intersection.getZ() > 0 ?
            this->r - intersection.getZ() :
            this->r + abs(intersection.getZ());
        double lineWidth = this->r * 2 / texture.getValue1();
        return this->getColor((int)(ratio / lineWidth) % 2);
    } else if (this->texture.getType() == "Image") {
        return TextureAplicator::applyTextureOnSphereAt(*this, intersection);
    } else {
        throw "Should never happen";
    }
}