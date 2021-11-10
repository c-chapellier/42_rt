#include "Polygone.hpp"

Polygone::Polygone(std::vector<Triangle> triangles) : Object(), triangles(triangles)
{
    if (triangles.size() == 0)
        throw "Can not create a polygone without any triangle";
}

Polygone::Polygone(std::vector<Triangle> triangles, const Color &color) : Object(color), triangles(triangles)
{
    if (triangles.size() == 0)
        throw "Can not create a polygone without any triangle";
}

Polygone::~Polygone()
{

}

std::vector<Intersection> Polygone::intersect(const Line &line) const
{
    std::vector<Intersection> intersections;

    for (unsigned long i = 0; i < this->triangles.size(); ++i) {
        std::vector<Intersection> tmp = triangles[i].intersect(line);
        for(Intersection inter : tmp) {
            intersections.push_back(Intersection(inter.getP(), inter.getDist(), (Object*)this, (Triangle*)&triangles[i]));
        }
    }
    return intersections;
}

double Polygone::angleWithAt(const Line &line, const Intersection &intersection) const
{
    return intersection.getTr()->getPlane().angleWith(line);
}

Color Polygone::getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const
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