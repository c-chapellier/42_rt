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
        Polygone(std::vector<Triangle*> triangles, Color *color);
        ~Polygone();

        Point *intersect(const Line &line) const;
        double angleWith(Line *line);
};

// Cube Coordinates size 0 0 0
// 2N-edron Coordinates precision height radius 0
// Parallelepiped Coordinates height width length 0
// Diamond Coordinates height Height radius Radius
// MobiusTape radius width precision 0
// Tape radius width precision 0
// Spiral radius width precision turns
// Tower radius width precision layers
// Torus Radius radius precision layer