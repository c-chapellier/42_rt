#pragma once

#include <vector>

#include "Object.hpp"
#include "components/Triangle.hpp"
class Intersection;

class Triangle;

class Polygone : public Object
{
    private:
        std::vector<Triangle*> triangles;

    public:
        Polygone(std::vector<Triangle*> triangles);
        ~Polygone();

        void intersect(std::vector<Intersection> *intersections, const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(const Intersection &intersection, const Line &line) const;
        Color getColorAt(const Point &intersection) const;
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