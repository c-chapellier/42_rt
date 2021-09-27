#pragma once

#include <iostream>

class Vector
{
    private:
        const double x;
        const double y;
        const double z;
    public:
        Vector(const double x, const double y, const double z);
        ~Vector();

        friend std::ostream& operator<<(std::ostream& out, const Vector& vector);
};