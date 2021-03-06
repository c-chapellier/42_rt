#pragma once

#include "components/Point.hpp"
#include "components/Vector.hpp"
#include "Object.hpp"

class Intersection;

// Equation:
// aX + bY +cZ = K

class Plane
{
    private:
        Point p;
        Vector v;
    public:
        Plane(const Point &p, const Vector &v);
        Plane(const Point &p1, const Point &p2);
        Plane(const Point &p, double vx, double vy, double vz);
        Plane(const double px, const double py, const double pz, const double vx, const double vy, const double vz);
        Plane(const Point &p1, const Point &p2, const Point &p3);
        ~Plane();

        Point getP() const;
        Vector getV() const;

        double angleWith(const Line &line) const;
        double angleWith(const Vector &v) const;
        double angleWith(const Plane &p) const;

        void intersect(std::vector<Intersection> *intersections, const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(const Intersection &intersection, const Line &line) const;

        friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
};