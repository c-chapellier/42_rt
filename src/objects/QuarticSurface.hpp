#pragma once

#include <math.h>
#include "Object.hpp"
#include "./../exceptions/NoInterException.hpp"

class QuarticSurface : public Object
{
    private:
        Point p;
        double C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14, C15, C16, C17, C18, C19, C20, C21, C22, C23, C24, C25, C26, C27, C28, C29, C30, C31, C32, C33, C34, C35;

        Plane tangentAt(const Point &intersection) const;
    public:
        QuarticSurface(double px, double py, double pz);
        ~QuarticSurface();

        void setX4(double C1);
        void setY4(double C2);
        void setZ4(double C3);

        void setX3Y(double C4);
        void setX3Z(double C5);
        void setY3X(double C6);
        void setY3Z(double C7);
        void setZ3X(double C8);
        void setZ3Y(double C9);

        void setX2Y2(double C10);
        void setX2Z2(double C11);
        void setY2Z2(double C12);

        void setX2YZ(double C13);
        void setY2XZ(double C14);
        void setZ2XY(double C15);

        void setX3(double C16);
        void setY3(double C17);
        void setZ3(double C18);

        void setX2Y(double C19);
        void setX2Z(double C20);
        void setY2X(double C21);
        void setY2Z(double C22);
        void setZ2X(double C23);
        void setZ2Y(double C24);
        void setXYZ(double C25);

        void setX2(double C26);
        void setY2(double C27);
        void setZ2(double C28);
        void setXY(double C29);
        void setXZ(double C30);
        void setYZ(double C31);

        void setX(double C32);
        void setY(double C33);
        void setZ(double C34);

        void setK(double C35);

        Point intersect(const Line &line) const;
        double angleWith(const Line &line) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};