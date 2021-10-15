#pragma once

#include "./../Polygone.hpp"

class PolygoneFactory
{
    private:
        PolygoneFactory();

        static Polygone *create2NEdron(Point &p, int precision, double height, double r, Color *color);
        static Polygone *createParallelepiped(Point &p, double height, double width, double length, Color *color);
        static Polygone *createDiamond(Point &p, double h, double H, double r, double R, Color *color);
        static Polygone *createTape(Point &p, double R, double width, int precision, Color *color);
        static Polygone *createMobiusTape(Point &p, double R, double width, int precision, Color *color);
        static Polygone *createSpiral(Point &p, double R, double width, int precision, int nb_turns, Color *color);
        static Polygone *createTower(Point &p, double R, double width, int precision, int layers, Color *color);
        static Polygone *createTorus(Point &p, double R, double r, int precision, int layers, Color *color);
    public:
        static Polygone *createPolygone(std::string type, Point &p, double size1, double size2, double size3, double size4, Color *color);
};