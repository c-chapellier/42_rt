#include "Circle.hpp"

Circle::Circle(double px, double py, double pz, double vx, double vy, double vz, double R, double r) : plane(px, py, pz, vx, vy, vz), R(R), r(r)
{

}
Circle::Circle(Plane &plane, double R, double r) : plane(plane), R(R), r(r)
{

}
Circle::~Circle() {}

Point Circle::intersect(const Line &line) const
{
    Point p = this->plane.intersect(line);
    double dist = p.distWith(this->plane.getP());

    if (dist <= this->R && dist >= this->r)
        return p;
    throw "Line do not intersect the circle";
}

double Circle::angleWith(const Line &line) const
{
    return this->plane.angleWith(line);
}

Color Circle::getColorAt(int height, int width, int screen_height, int screenWidth, Point &intersection)
{
    screenWidth = intersection.getX();

    if (this->texture.getType() == "Uniform") {
        return getColor();
    } else if (this->texture.getType() == "Gradient") {
        double p = (double)((double)height / (double)screen_height);
        return Color(
            getColor(0).getR() + (int)((double)((double)getColor(1).getR() - (double)getColor(0).getR()) * p),
            getColor(0).getG() + (int)((double)((double)getColor(1).getG() - (double)getColor(0).getG()) * p),
            getColor(0).getB() + (int)((double)((double)getColor(1).getB() - (double)getColor(0).getB()) * p),
            getColor(0).getO() + (int)((double)((double)getColor(1).getO() - (double)getColor(0).getO()) * p)
        );
    } else if (this->texture.getType() == "Grid") {
        return getColor(((height / this->texture.getValue1()) + (width / this->texture.getValue2())) % 2);
    } else if (this->texture.getType() == "VerticalLined") {
        return getColor((width / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "HorizontalLined") {
        return getColor((height / this->texture.getValue1()) % 2);
    } else if (this->texture.getType() == "Image") {
        throw "Texture type Image ca't be apply here";
    } else {
        throw "Should never happen";
    }
}