#include "Cylinder.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Cylinder::Cylinder(double r)
    : r(r)
{
}

Cylinder::~Cylinder() {}

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void Cylinder::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Line local_line = this->tr.apply(line, TO_LOCAL);
    local_line.normalize();

    double a, b, c;
    a = local_line.getX() * local_line.getX()+
        local_line.getY() * local_line.getY();

    b = 2 * local_line.getPX() * local_line.getX() + 
        2 * local_line.getPY() * local_line.getY();

    c = local_line.getPX() * local_line.getPX() +
        local_line.getPY() * local_line.getPY() -
        this->r * this->r;

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);
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

double Cylinder::angleWithAt(const Line &line, const Intersection &intersection) const
{
    Point local_height(0, 0, intersection.getLocalPoint().getZ());
    Point real_height = this->tr.apply(local_height, TO_REAL);
    Plane pl(real_height, intersection.getRealPoint());
    return pl.angleWithAt(line, intersection);
}

Line Cylinder::getReflectedRayAt(const Intersection &intersection, const Line &line) const
{
    Point local_height(0, 0, intersection.getLocalPoint().getZ());
    Point real_height = this->tr.apply(local_height, TO_REAL);
    Vector normal(real_height, intersection.getRealPoint());
    Vector reflexion =  normal.getReflectionOf(line.getV());
    return Line(intersection.getRealPoint(), reflexion);
}

Color Cylinder::getColorAt(const Point &intersection) const
{
    char type = this->texture.getType();

    if (type == UNIFORM) {
        return this->getColor();
    } else if (type == GRADIENT) {
        // get the value of Z as absolute
        int z_value = intersection.getZ() >= 0 ?
            (int)(intersection.getZ() / (double)this->texture.getValue1()) :
            (int)((abs(intersection.getZ())) / this->texture.getValue1());
        // get the ratio of gradient
        double gr =  (intersection.getZ() >= 0 ?
            mod(intersection.getZ(), this->texture.getValue1()) :
            mod(abs(intersection.getZ()), this->texture.getValue1()))
            / (double)this->texture.getValue1();
        return  (z_value % 2 == 0 ? 
                Color(
                    this->getColor(0).getR() + (int)((double)((double)this->getColor(1).getR() - (double)this->getColor(0).getR()) * gr),
                    this->getColor(0).getG() + (int)((double)((double)this->getColor(1).getG() - (double)this->getColor(0).getG()) * gr),
                    this->getColor(0).getB() + (int)((double)((double)this->getColor(1).getB() - (double)this->getColor(0).getB()) * gr),
                    this->getColor(0).getO() + (int)((double)((double)this->getColor(1).getO() - (double)this->getColor(0).getO()) * gr)
                ) :
                Color(
                    this->getColor(1).getR() + (int)((double)((double)this->getColor(0).getR() - (double)this->getColor(1).getR()) * gr),
                    this->getColor(1).getG() + (int)((double)((double)this->getColor(0).getG() - (double)this->getColor(1).getG()) * gr),
                    this->getColor(1).getB() + (int)((double)((double)this->getColor(0).getB() - (double)this->getColor(1).getB()) * gr),
                    this->getColor(1).getO() + (int)((double)((double)this->getColor(0).getO() - (double)this->getColor(1).getO()) * gr)
                )
            );
    } else if (type == GRID) {
        /*
            The first value of the texture is the number of vertical sections
            The second value is the width of horizontal lines
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
                        (int)(intersection.getZ()) :
                        (int)((abs(intersection.getZ()) + this->texture.getValue2()));
        
        return this->getColor(((int)(alpha / lineRadian) + (int)(ratio / this->texture.getValue2())) % 2);
    } else if (type == VERTICAL_LINED) {
        /*
            The first value of the texture is the number of vertical sections
            The second value is unused
            To find the right color:
                - Get section length as degree
        */
        double lineRadian = 360.0 / texture.getValue1();
        Vector v(0, 0, 0, intersection.getX(), intersection.getY(), 0);
        Vector x_axis(0, 1, 0);
        double alpha = v.angleWith(x_axis);
        alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);

        return this->getColor((int)(alpha / lineRadian) % 2);
    } else if (type == HORIZONTAL_LINED) {
        /*
            The first value of the texture is the width of horizontal lines
            The second value is unused
            To find the right color:
                - Get the height ratio
        */
        double ratio = intersection.getZ() >= 0 ?
                        (int)(intersection.getZ()) :
                        (int)((abs(intersection.getZ()) + this->texture.getValue1()));
        return this->getColor((int)(ratio / this->texture.getValue1()) % 2);
    } else if (type == IMAGE) {
        return TextureAplicator::applyTextureOnCylinderAt(*this, intersection);
    } else {
        throw "Should never happen";
    }
}