#pragma once

#include "components/Point.hpp"

// Equation:
// x = (1 + t/2 cos ν/2) cos ν
// y = (1 + t/2 cos ν/2) sin ν
// z = t/2 sin ν/2
// or
// x²y + yz² + y³ -y -2xz -2x²z -2y²z = 0

// x = at + x₀
// y = bt + y₀
// z = ct + z₀

// => (at + x₀)² * (bt + y₀) +
//    (bt + y₀) * (ct + z₀)² +
//    (bt + y₀)³ +
//    - (bt + y₀) +
//    -2 (at + x₀) * (ct + z₀) +
//    -2 (at + x₀)² * (ct + z₀) +
//    -2 (bt + y₀)² * (ct + z₀)

// => (a²t² + 2ax₀t + x₀²) * (bt + y₀) = a²bt³ + 2ax₀bt² + x₀²bt + a²y₀t² + 2ax₀y₀t + x₀²y₀ = (a²b)t³ + (2ax₀b + a²y₀)t² + (x₀²b + 2ax₀y₀)t + x₀²y₀
// => (c²t² + 2cz₀t + z₀²) * (bt + y₀) = c²bt³ + 2cz₀bt² + z₀²bt + c²y₀t² + 2cz₀y₀t + z₀²y₀ = (c²b)t³ + (2cz₀b + c²y₀)t² + (z₀²b + 2cz₀y₀)t + z₀²y₀
// => (bt + y₀)³ = (b³)t³ + (3b²y₀)t² + (3by₀²)t + y₀³
// => - (bt + y₀) = (0)t³ + (0)t² - bt + y₀
// => -2 (at + x₀) * (ct + z₀) = -2 (act² +  az₀t + cx₀t + x₀z₀) = (0)t³ - (2ac)t² - (2az₀ + 2cx₀)t - 2x₀z₀
// => 

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