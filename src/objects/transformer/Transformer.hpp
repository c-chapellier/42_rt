#pragma once

#include <vector>
#include "./../components/Point.hpp"
#include "./../components/Vector.hpp"

class Transformer
{
    private:
        Transformer();

        static double getAngle(double x, double y);
    public:
        // translation
        static void translate(Point *p, const Point &off);
        static void translate(std::vector<Point*> points, const Point &off);
        static void translateX(Point *p, double off);
        static void translateX(std::vector<Point*> points, double off);
        static void translateY(Point *p, double off);
        static void translateY(std::vector<Point*> points, double off);
        static void translateZ(Point *p, double off);
        static void translateZ(std::vector<Point*> points, double off);
        // rotation
        static void rotateAroundX(Point *p, double alpha);
        static void rotateAroundX(std::vector<Point*> points, double alpha);
        static void rotateAroundY(Point *p, double alpha);
        static void rotateAroundY(std::vector<Point*> points, double alpha);
        static void rotateAroundZ(Point *p, double alpha);
        static void rotateAroundZ(std::vector<Point*> points, double alpha);

};