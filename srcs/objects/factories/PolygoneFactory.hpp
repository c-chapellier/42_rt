#pragma once

#include "./../Polygone.hpp"

class PolygoneFactory
{
    private:
        PolygoneFactory();

        static Polygone *createOctohedron(Point &p, double height, double width);
        static Polygone *createCube(Point &p, double size);
        static Polygone *createParallelepiped(Point &p, double height, double width, double length);
        static Polygone *createDiamond(Point &p, double h, double H, double r, double R);
    public:
        static Polygone *createPolygone(std::string type, Point &p, double size1, double size2, double size3, double size4);
};