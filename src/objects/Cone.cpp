#include "Cone.hpp"

Cone::Cone(double alpha)
    : alpha(alpha)
{
    tr.updateMatrices();
}

Cone::~Cone() {}

std::vector<Intersection> Cone::intersect(const Line &line) const
{
    Vector back = this->tr.apply(line.getV(), TO_LOCAL);
    back.normalize();

    double a, b, c;
    a = pow(back.getX(), 2) + pow(back.getY(), 2) - (pow(back.getZ(), 2) * pow(tan(RADIAN(alpha)), 2));
    b = 2 * back.getP1()->getX() * back.getX() + 2 * back.getP1()->getY() * back.getY() - 2 * back.getP1()->getZ() * back.getZ() * tan(RADIAN(alpha));
    c = pow(back.getP1()->getX(), 2) + pow(back.getP1()->getY(), 2) - pow(back.getP1()->getZ() * tan(RADIAN(alpha)), 2);

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);

    std::vector<Intersection> intersections;
    for (double s : solutions) {
        if (s > 0.00001) {
            Point local_point(
                back.getP1()->getX() + s * back.getX(),
                back.getP1()->getY() + s * back.getY(),
                back.getP1()->getZ() + s * back.getZ()
            );
            Point real_point = this->tr.apply(local_point, TO_REAL);
            double dist = (real_point.getX() - line.getP().getX()) / line.getV().getX();
            intersections.push_back(Intersection(real_point, dist, (Object*)this));
        }
    }
    return intersections;
}

double Cone::angleWithAt(const Line &line, const Intersection &intersection) const
{
    // go to imaginary world
    Point local_point = this->tr.apply(intersection.getP(), TO_LOCAL);
    // get angle
    double angle = 90 - (180 - 90 - alpha);
    double offset = tan(RADIAN(angle)) * abs(local_point.getZ());
    Point h(0, 0, local_point.getZ() > 0 ? local_point.getZ() + offset : local_point.getZ() - offset);
    // return to real world
    Point real_point = this->tr.apply(h, TO_REAL);
    // get the plane
    Plane pl(real_point, intersection.getP());
    return pl.angleWithAt(line, intersection);
}

Line Cone::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    return Line(1, 1, 1, 1, 1, 1);
}

Color Cone::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
{
    Point local_point = this->tr.apply(intersection, TO_LOCAL);
    screenWidth = intersection.getX();

    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        // get the value of Z as absolute
        int z_value = local_point.getZ() >= 0 ?   (int)(local_point.getZ() / (double)this->texture.getValue1()) :
                                    (int)((abs(local_point.getZ())) / this->texture.getValue1());
        // get the ratio of gradient
        double gr =  (local_point.getZ() >= 0 ?    mod(local_point.getZ(), this->texture.getValue1()) :
                                        mod(abs(local_point.getZ()), this->texture.getValue1()))
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
    } else if (this->texture.getType() == "Grid") {
        /*
            The first value of the texture is the number of vertical sections
            The second value is the width of horizontal lines
            To find the right color:
                - Combine vertical and horizontal
        */

        // Vertical
        double lineRadian = 360.0 / texture.getValue1();
        Vector v(0, 0, 0, local_point.getX(), local_point.getY(), 0);
        Vector x_axis(0, 1, 0);
        double alpha = v.angleWith(x_axis);
        alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);

        // Horizontal
        double ratio = local_point.getZ() >= 0 ?
                        (int)(local_point.getZ()) :
                        (int)((abs(local_point.getZ()) + this->texture.getValue2()));
        
        return this->getColor(((int)(alpha / lineRadian) + (int)(ratio / this->texture.getValue2())) % 2);
        
    } else if (this->texture.getType() == "VerticalLined") {
        /*
            The first value of the texture is the number of vertical sections
            The second value is unused
            To find the right color:
                - Get section length as degree
        */
        double lineRadian = 360.0 / texture.getValue1();
        Vector v(0, 0, 0, local_point.getX(), local_point.getY(), 0);
        Vector x_axis(0, 1, 0);
        double alpha = v.angleWith(x_axis);
        alpha = v.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);

        return this->getColor((int)(alpha / lineRadian) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        /*
            The first value of the texture is the width of horizontal lines
            The second value is unused
            To find the right color:
                - Get the height ratio
        */
        double ratio = local_point.getZ() >= 0 ?
                        (int)(local_point.getZ()) :
                        (int)((abs(local_point.getZ()) + this->texture.getValue1()));
        return this->getColor((int)(ratio / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "Image") {
        throw "Texture type has no power here";
    } else {
        throw "Should never happen";
    }
}