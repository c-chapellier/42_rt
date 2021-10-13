#pragma once

#include "./../Polygone.hpp"

class PolygoneFactory
{
    private:
        PolygoneFactory();

        static Polygone *create2NEdron(Point &p, int precision, double height, double r);
        static Polygone *createParallelepiped(Point &p, double height, double width, double length);
        static Polygone *createDiamond(Point &p, double h, double H, double r, double R);
        static Polygone *createTape(Point &p, double R, double width, int precision);
        static Polygone *createMobiusTape(Point &p, double R, double width, int precision);
        static Polygone *createSpiral(Point &p, double R, double width, int precision, int nb_turns);
        static Polygone *createTower(Point &p, double R, double width, int precision, int layers);
    public:
        static Polygone *createPolygone(std::string type, Point &p, double size1, double size2, double size3, double size4);
};