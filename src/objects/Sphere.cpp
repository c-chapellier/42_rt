#include "Sphere.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Sphere::Sphere(double r)
    : Object(), r(r)
{}

Sphere::~Sphere(){};

/* * * * * * * * * * * * * * * * * * * * *

*                GETTER                  *

* * * * * * * * * * * * * * * * * * * * */

double Sphere::getR() const
{
    return this->r;
}

/* * * * * * * * * * * * * * * * * * * * *

*                FUNCTIONS               *

* * * * * * * * * * * * * * * * * * * * */

void Sphere::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Line local_line = this->tr.apply(line, TO_LOCAL);
    local_line.normalize();

    double a = 1;

    double b = 2 * local_line.getPX() * local_line.getX()
        + 2 * local_line.getPY() * local_line.getY()
        + 2 * local_line.getPZ() * local_line.getZ();
        
    double c = local_line.getPX() * local_line.getPX()
        + local_line.getPY() * local_line.getPY()
        + local_line.getPZ() * local_line.getPZ()
        - this->r * this->r;

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);
    for (double s: solutions)
    {
        if (s > 0.00001)
        {
            Point local_intersection(
                local_line.getPX() + local_line.getX() * s,
                local_line.getPY() + local_line.getY() * s,
                local_line.getPZ() + local_line.getZ() * s
            );
            Point real_intersection = this->tr.apply(local_intersection, TO_REAL);
            double dist = (real_intersection.getX() - line.getPX()) / line.getX();
            intersections->push_back(Intersection(real_intersection, local_intersection, dist, (Object*)this));
        }
    }
}

double Sphere::angleWithAt(const Line &line, const Intersection &intersection) const
{
    Point real_origin = this->tr.apply(Point(0, 0, 0), TO_REAL);
    return Plane(real_origin, intersection.getRealPoint()).angleWith(line);
}

Line Sphere::getReflectedRayAt(const Intersection &intersection, const Line &line) const
{
    Point real_origin = this->tr.apply(Point(0, 0, 0), TO_REAL);
    Vector v(real_origin, intersection.getRealPoint());
    Vector tmp = v.getReflectionOf(line.getV());
    return Line(intersection.getRealPoint(), tmp);
}

Color Sphere::getColorAt(const Point &intersection) const
{
    char type = this->texture.getType();

    if (type == UNIFORM) {
        return this->getColor();
    } else if (type == GRADIENT) {
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
    } else if (type == GRID) {
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
    } else if (type == VERTICAL_LINED) {
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
    } else if (type == HORIZONTAL_LINED) {
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
    } else if (type == IMAGE) {
        return TextureAplicator::applyTextureOnSphereAt(*this, intersection);
    } else {
        throw "Should never happen";
    }
}