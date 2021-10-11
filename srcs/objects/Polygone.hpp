#pragma once

#include <vector>

#include "Object.hpp"
#include "components/Triangle.hpp"

class Polygone : public Object
{
    private:
        std::vector<Triangle*> triangles;
    public:
        Polygone(std::vector<Point*> points);
        Polygone(std::vector<Triangle*> triangles);
        ~Polygone();

        Point *intersect(Line *line);
};