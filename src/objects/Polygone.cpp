#include "Polygone.hpp"

Polygone::Polygone(std::vector<Point*> points) : Object()
{
    if (points.size() < 3)
        throw "Can not create a polygone with less than three points";
    for (unsigned long i = 2; i < points.size(); ++i)
    {
        this->triangles.push_back(new Triangle(*points[i - 2], *points[i - 1], *points[i]));
    }
}
Polygone::Polygone(std::vector<Triangle*> triangles) : Object()
{
    if (triangles.size() < 1)
        throw "Can not create a polygone without any triangle";
    for (unsigned long i = 0; i < triangles.size(); ++i)
    {
        this->triangles.push_back(new Triangle(*triangles[i]));
    }
}
Polygone::Polygone(std::vector<Triangle*> triangles, const Color &color) : Object(color)
{
    if (triangles.size() < 1)
        throw "Can not create a polygone without any triangle";
    for (unsigned long i = 0; i < triangles.size(); ++i)
    {
        this->triangles.push_back(new Triangle(*triangles[i]));
    }
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
            Point tmp = this->triangles[i]->intersect(line);

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
            Point tmp = this->triangles[i]->intersect(line);
            if (actual_min == NULL)
            {
                angle = this->triangles[i]->getPlane()->angleWith(line);
                actual_min = new Point(tmp);
            }
            else
            {
                double dist1 = actual_min->distWith(line.getP());
                double dist2 = tmp.distWith(line.getP());
                
                if (dist2 < dist1)
                {
                    angle = this->triangles[i]->getPlane()->angleWith(line);
                    delete(actual_min);
                    actual_min = new Point(tmp);
                }
            }
        } catch(...) {}
    }
    delete(actual_min);
    return angle;
}

Color Polygone::getColorAt(int height, int width, int screen_height, int screenWidth, Point &intersection)
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