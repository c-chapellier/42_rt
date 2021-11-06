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

Point Polygone::intersect(const Line &line) const
{
    Point *res = NULL;

    for(unsigned long i = 0; i < this->triangles.size(); ++i)
    {
        // if intersect triangle
        try {
            Point tmp = this->triangles[i].intersect(line);

            if (res == NULL){
                res = new Point(tmp);
            } else {
                double dist1 = res->distWith(line.getP());
                double dist2 = tmp.distWith(line.getP());
                if(dist2 < dist1) {
                    delete(res);
                    res = new Point(tmp);
                }
            }
        } catch(...) {}
        // compare dist with prec points
        // stock new point
    }
    if (res == NULL) {
        throw NoInterException("Line do not intersect polygon");
    }
    Point ret(*res);
    delete(res);
    return ret;
}

double Polygone::angleWith(const Line &line) const
{
    double angle = -1.0;
    Point *actual_min = NULL;

    for (unsigned long i = 0; i < this->triangles.size(); ++i)
    {
        try {
            Point tmp = this->triangles[i].intersect(line);
            if (actual_min == NULL)
            {
                angle = this->triangles[i].getPlane().angleWith(line);
                actual_min = new Point(tmp);
            }
            else
            {
                double dist1 = actual_min->distWith(line.getP());
                double dist2 = tmp.distWith(line.getP());
                
                if (dist2 < dist1)
                {
                    angle = this->triangles[i].getPlane().angleWith(line);
                    delete(actual_min);
                    actual_min = new Point(tmp);
                }
            }
        } catch(...) {}
    }
    delete(actual_min);
    return angle;
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