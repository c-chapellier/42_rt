#pragma once

#include <math.h>

#include "../header.hpp"

#include "../objects/components/Point.hpp"
#include "../objects/components/Vector.hpp"
#include "../objects/Plane.hpp"

class Config;
/*

V
^
|
|
|
 - - - - -> U
*/
class Camera
{
    private:
        Point coordinates;
        Vector direction;
        Vector up;
        double angle;

        Vector U;
        Vector V;
        Point screenCenter;
        int height;
        int width;
        
    public:
        Camera(double cx, double cy, double cz, double dx, double dy, double dz, double ux, double uy, double uz, double a);
        ~Camera();

        Point getP() const;
        Vector getV() const;

        void setX(double x);
        void setY(double y);
        void setZ(double z);
        void setV(double x, double y, double z);

        void update(const Config &config);

        Point getPoint(int h, int w, bool x) const;
        Point getPoint(double h, double w) const;
        std::vector< std::vector<Point> > getScreen() const;
};