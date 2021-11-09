#pragma once

#include "Object.hpp"
#include "./../exceptions/NoInterException.hpp"

// https://mathcurve.com/surfaces.gb/cubic/cubic.shtml
class CubicSurface : public Object
{
    private:
        Point p;
        double A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T;

        Plane tangentAt(const Point &intersection) const;
    public:
        CubicSurface(double px, double py, double pz);
        ~CubicSurface();

        void setX3(double A);
        void setY3(double B);
        void setZ3(double C);
        void setX2Y(double D);
        void setX2Z(double E);
        void setY2X(double F);
        void setY2Z(double G);
        void setZ2X(double H);
        void setZ2Y(double I);
        void setXYZ(double J);
        void setX2(double K);
        void setY2(double L);
        void setZ2(double M);
        void setXY(double N);
        void setXZ(double O);
        void setYZ(double P);
        void setX(double Q);
        void setY(double R);
        void setZ(double S);
        void setK(double T);

        Point intersect(const Line &line) const;
        double angleWith(const Line &line) const;
        Color getColorAt(int height, int width, int screen_height, int screenWidth, const Point &intersection) const;
};