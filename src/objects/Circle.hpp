#pragma once

#include "Object.hpp"
#include "Plane.hpp"

class Circle : public Object
{
    private:
        Plane plane;
        double R;
        double r;
    public:
        Circle(double px, double py, double pz, double vx, double vy, double vz, double R, double r);
        Circle(Plane &plane, double R, double r);
        ~Circle();

        Point intersect(const Line &line) const;
        double angleWith(const Line &line) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, Point &intersection);
};