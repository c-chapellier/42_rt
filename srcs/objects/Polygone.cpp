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
Polygone::Polygone(std::vector<Triangle*> triangles)
{
    if(triangles.size() < 1)
        throw "Can not create a polygone without any triangle";
    for (unsigned long i = 0; i < triangles.size(); ++i)
    {
        this->triangles.push_back(new Triangle(*triangles[i]));
    }
}
Polygone::~Polygone()
{

}

Point *Polygone::intersect(Line *line)
{
    Point *res = NULL;

    for(unsigned long i = 0; i < this->triangles.size(); ++i)
    {
        // if intersect triangle
        Point *tmp = this->triangles[i]->intersect(line);
        if(tmp){
            if (res == NULL){
                res = tmp;
            } else {
                double dist1 = res->distWith(*line->getP());
                double dist2 = tmp->distWith(*line->getP());
                if(dist2 < dist1) {
                    delete(res);
                    res = tmp;
                }
            }
        }
        // compare dist with prec points
        // stock new point
    }
    return res;
}