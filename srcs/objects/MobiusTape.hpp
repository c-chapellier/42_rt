#pragma once

#include "components/Point.hpp"

class MobiusTape
{
    private:
        Point *p;
        double t;
        double v;
    public:
        MobiusTape(double x, double y, double z);
        ~MobiusTape();

        friend std::ostream& operator<<(std::ostream& out, const MobiusTape& mobius);
};