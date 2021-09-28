#pragma once

#include "components/Point.hpp"

// Equation:
// x = (1 + t/2 cos ν/2) cos ν
// y = (1 + t/2 cos ν/2) sin ν
// z = t/2 sin ν/2
// or
// x²y + yz² + y³ -y -2xz -2x²z -2y²z = 0

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