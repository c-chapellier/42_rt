#include "Cone.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Cone::Cone(double alpha)
    : alpha(alpha)
{
    tr.updateMatrices();
}

Cone::~Cone() {}

/* * * * * * * * * * * * * * * * * * * * *

*               FUNCTIONS                *

* * * * * * * * * * * * * * * * * * * * */

void Cone::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Vector back = this->tr.apply(line.getV(), TO_LOCAL);
    back.normalize();

    double a, b, c;
    a = pow(back.getX(), 2) + pow(back.getY(), 2) - (pow(back.getZ(), 2) * pow(tan(RADIAN(alpha)), 2));
    b = 2 * back.getP1()->getX() * back.getX() + 2 * back.getP1()->getY() * back.getY() - 2 * back.getP1()->getZ() * back.getZ() * tan(RADIAN(alpha));
    c = pow(back.getP1()->getX(), 2) + pow(back.getP1()->getY(), 2) - pow(back.getP1()->getZ() * tan(RADIAN(alpha)), 2);

    std::list<double> solutions = EquationSolver::solveQuadraticEquation(a, b, c);
    for (double s : solutions) {
        if (s > 0.00001) {
            Point local_point(
                back.getP1()->getX() + s * back.getX(),
                back.getP1()->getY() + s * back.getY(),
                back.getP1()->getZ() + s * back.getZ()
            );
            Point real_point = this->tr.apply(local_point, TO_REAL);
            double dist = (real_point.getX() - line.getP().getX()) / line.getV().getX();
            intersections->push_back(Intersection(real_point, local_point, dist, (Object*)this));
        }
    }
}

double Cone::angleWithAt(const Line &line, const Intersection &intersection) const
{
    double angle = 90 - (180 - 90 - alpha);
    double offset = tan(RADIAN(angle)) * abs(intersection.getLocalPoint().getZ());
    Point local_height(0, 0, intersection.getLocalPoint().getZ() > 0 ? intersection.getLocalPoint().getZ() + offset : intersection.getLocalPoint().getZ() - offset);
    Point real_height = this->tr.apply(local_height, TO_REAL);
    Plane pl(real_height, intersection.getRealPoint());
    return pl.angleWithAt(line, intersection);
}

Line Cone::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    double angle = 90 - (180 - 90 - alpha);
    double offset = tan(RADIAN(angle)) * abs(intersection.getLocalPoint().getZ());
    Point local_height(0, 0, intersection.getLocalPoint().getZ() > 0 ? intersection.getLocalPoint().getZ() + offset : intersection.getLocalPoint().getZ() - offset);
    Point real_height = this->tr.apply(local_height, TO_REAL);
    Vector normal(real_height, intersection.getRealPoint());
    Vector reflexion =  normal.getReflectionOf(line.getV());
    reflexion.setP1(intersection.getRealPoint());
    return Line(intersection.getRealPoint(), reflexion);
}

Color Cone::getColorAt(const Point &intersection) const
{
    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
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
    } else if (this->texture.getType() == "Grid") {
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
        
    } else if (this->texture.getType() == "VerticalLined") {
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
    } else if (this->texture.getType() == "HorizontalLined") {
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
    } else if (this->texture.getType() == "Image") {
        return TextureAplicator::applyTextureOnConeAt(*this, intersection);
    } else {
        throw "Should never happen";
    }
}