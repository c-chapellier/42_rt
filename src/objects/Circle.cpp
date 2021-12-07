#include "Circle.hpp"

Circle::Circle(double R, double r) : R(R), r(r)
{
    if (r >= R || r < 0 || R < 0)
        throw "Impossible circle";
}
Circle::~Circle() {}

void Circle::intersect(std::vector<Intersection> *intersections, const Line &line) const
{
    Vector local_vector = this->tr.apply(line.getV(), TO_LOCAL);
    Vector normal(0, 0, 1);

    if (local_vector.getZ() == 0) {
        // line in the plane
    } else {
        double s = -local_vector.getP1()->getZ() / local_vector.getZ();
        if(s > 0.00001) {
            Point origin(0, 0, 0);
            Point local_point(
                local_vector.getP1()->getX() + s * local_vector.getX(),
                local_vector.getP1()->getY() + s * local_vector.getY(),
                local_vector.getP1()->getZ() + s * local_vector.getZ()
            );
            if (local_point.distWith(origin) <= R && local_point.distWith(origin) >= r) {
                Point real_point = this->tr.apply(local_point, TO_REAL);
                double dist = (real_point.getX() - line.getP().getX()) / line.getV().getX();
                intersections->push_back(Intersection(real_point, local_point, dist, (Object*)this));
            }
            
        }
    }
}

double Circle::angleWithAt(const Line &line, const Intersection &intersection) const
{
    Vector local_normal(0, 0, 1);
    Vector real_normal = this->tr.apply(local_normal, TO_REAL);
    return real_normal.angleWith(line.getV());
}

Line Circle::getReflectedRayAt(Intersection &intersection, const Line &line) const
{
    Vector local_vector = this->tr.apply(line.getV(), TO_LOCAL);
    Vector local_reflexion(local_vector.getX(), local_vector.getY(), -local_vector.getZ());
    Vector real_reflexion = this->tr.apply(local_vector, TO_REAL);
    real_reflexion.setP1(intersection.getRealPoint());
    return Line(intersection.getRealPoint(), real_reflexion);
}

Color Circle::getColorAt(const Point &intersection) const
{
    if (this->texture.getType() == "Uniform") {
        return this->getColor();
    } else if (this->texture.getType() == "Gradient") {
        double dist = intersection.distWith(Point(0, 0, 0));
        double ratio = dist - r / (R - r);
        return Color(
            this->getColor(0).getR() + (int)((double)((double)this->getColor(1).getR() - (double)this->getColor(0).getR()) * ratio),
            this->getColor(0).getG() + (int)((double)((double)this->getColor(1).getG() - (double)this->getColor(0).getG()) * ratio),
            this->getColor(0).getB() + (int)((double)((double)this->getColor(1).getB() - (double)this->getColor(0).getB()) * ratio),
            this->getColor(0).getO() + (int)((double)((double)this->getColor(1).getO() - (double)this->getColor(0).getO()) * ratio)
        );
    } else if (this->texture.getType() == "Grid") {
        throw "Texture unsupported";
    } else if (this->texture.getType() == "VerticalLined") {
        throw "Texture unsupported";
    } else if (this->texture.getType() == "HorizontalLined") {
        throw "Texture unsupported";
    } else if (this->texture.getType() == "Image") {
        throw "Texture unsupported";
    } else {
        throw "Should never happen";
    }
}