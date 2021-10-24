#pragma once

#include "./../Polygone.hpp"
#include "./../transformer/Transformer.hpp"

class PolygoneFactory
{
    private:
        PolygoneFactory();

        static Polygone *create2NEdron(Point &p, int precision, double height, double r, double alpha, double beta, double gama, Color *color);
        static Polygone *createParallelepiped(Point &p, double height, double width, double length, double alpha, double beta, double gama, Color *color);
        static Polygone *createDiamond(Point &p, double h, double H, double r, double R, double alpha, double beta, double gama, Color *color);
        static Polygone *createTape(Point &p, double R, double width, int precision, double alpha, double beta, double gama, Color *color);
        static Polygone *createClosedTape(Point &p, double R, double width, int precision, double alpha, double beta, double gama, Color *color);
        static Polygone *createMobiusTape(Point &p, double R, double width, int precision, double alpha, double beta, double gama, Color *color);
        static Polygone *createSpiral(Point &p, double R, double width, int precision, int nb_turns, double alpha, double beta, double gama, Color *color);
        static Polygone *createTower(Point &p, double R, double width, int precision, int layers, double alpha, double beta, double gama, Color *color);
        static Polygone *createTorus(Point &p, double R, double r, int precision, int layers, double alpha, double beta, double gama, Color *color);
        static Polygone *createRing(Point &p, double R, double r, int precision, double alpha, double beta, double gama, Color *color);
        static Polygone *createCircle(Point &p, double R, int precision, double alpha, double beta, double gama, Color *color);
        static Polygone *createStar(Point &p, double R, double r, double thick, int branch, double alpha, double beta, double gama, Color *color);
    public:
        static Polygone *createPolygone(std::string type, Point &p, double size1, double size2, double size3, double size4, double alpha, double beta, double gama);
        static Polygone *createPolygone(std::string type, Point &p, double size1, double size2, double size3, double size4, double alpha, double beta, double gama, Color *color);
};