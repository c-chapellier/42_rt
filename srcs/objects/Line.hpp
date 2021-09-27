#pragma once

#include "components/Point.hpp"
#include "components/Vector.hpp"

class Line
{
    private:
        Point *p;
        Vector *v;
    public:
        Line(double px, double py, double pz, double vx, double vy, double vz);
        ~Line();

        friend std::ostream& operator<< (std::ostream& out, const Line& line);
};