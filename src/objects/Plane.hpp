#pragma once

#include "../exceptions/NoInterException.hpp"
#include "components/Point.hpp"
#include "components/Vector.hpp"
#include "Object.hpp"

class Intersection;

// Equation:
// aX + bY +cZ = K

class Plane : public Object
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

        std::vector<Intersection> intersect(const Line &line) const;
        double angleWith(const Line &line) const;
        double angleWith(const Vector &v) const;
        double angleWith(const Plane &p) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(Intersection &intersection, const Line &line) const;

        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;

        friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
};