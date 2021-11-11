#pragma once

#include "../header.hpp"

class Intersection;

class Plane;

class Circle : public Object
{
    private:
        Plane *plane;
        double R;
        double r;
    public:
        Circle(double px, double py, double pz, double vx, double vy, double vz, double R, double r);
        Circle(const Plane &plane, double R, double r);
        ~Circle();

        std::vector<Intersection> intersect(const Line &line) const;
        double angleWithAt(const Line &line, const Intersection &intersection) const;
        Line getReflectedRayAt(Intersection &intersection, const Line &line) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};