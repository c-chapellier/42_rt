#include "Circle.hpp"

Circle::Circle(double px, double py, double pz, double vx, double vy, double vz, double R, double r)
{
    this->plane = new Plane(px, py, pz, vx, vy, vz);
    this->R = R;
    this->r = r;
}
Circle::~Circle() {
    delete(this->plane);
}

Point Circle::intersect(const Line &line) const
{
    Point p = this->plane->intersect(line);
    double dist = p.distWith(this->plane->getP());

    if (dist <= this->R && dist >= this->r)
        return p;
    throw NoInterException("Line do not intersect the circle");
}

double Circle::angleWith(const Line &line) const
{
    return this->plane->angleWith(line);
}

Color Circle::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
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