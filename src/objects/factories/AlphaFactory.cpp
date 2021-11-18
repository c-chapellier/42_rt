#include "AlphaFactory.hpp"

AlphaFactory::AlphaFactory(){}

std::vector<Polygone *> AlphaFactory::createAlpha(const std::string &str, const Point &p, double height, double width, double thick)
{
    std::vector<Polygone *> alpha;
    double offset = 0;

    for (int i = 0; i < (int)str.size(); ++i) {
        if (str[i] == 'B' || str[i] == 'b') {
            alpha.push_back(createB(p, height, width, thick, offset));
            offset += 2 * thick;
        } else if (str[i] == 'I' || str[i] == 'i') {
            alpha.push_back(createI(p, height, width, thick, offset));
            offset += 2 * thick;
        } else if (str[i] == 'O' || str[i] == 'o') {
            alpha.push_back(createO(p, height, width, thick, offset));
            offset += width + thick;
        } else if (str[i] == 'U' || str[i] == 'u') {
            alpha.push_back(createU(p, height, width, thick, offset));
            offset += width + thick;
        } else {
            throw "Unrecognized type of alpha";
        }
    }
    return alpha;
}

Polygone *AlphaFactory::createB(const Point &p, double height, double width, double thick, int offset)
{
    throw "Not yet implemented";
    p.getZ();
    width = 0;
    std::vector<Point> bar;
    std::vector<Point> point;
    // bar
    bar.push_back(Point(0, offset - (thick / 2), -(height / 2)));
    bar.push_back(Point(0, offset - (thick / 2), (height / 4)));
    bar.push_back(Point(0, offset + (thick / 2), (height / 4)));
    bar.push_back(Point(0, offset + (thick / 2), -(height / 2)));

    // point
    for (int i = 0; i < 4; ++i) {
        double alpha = i * (360 / 4);
        point.push_back(Point(0, offset + (thick / 2) * cos(RADIAN(alpha)), (height / 4) + (thick / 2) + (thick / 2) * sin(RADIAN(alpha))));
    }

    std::vector<Triangle*> triangles;
    triangles.push_back(new Triangle(bar[0], bar[1], bar[2]));
    triangles.push_back(new Triangle(bar[2], bar[3], bar[0]));
    triangles.push_back(new Triangle(point[0], point[1], point[2]));
    triangles.push_back(new Triangle(point[2], point[3], point[0]));

    return new Polygone(triangles);
}

Polygone *AlphaFactory::createI(const Point &p, double height, double width, double thick, int offset)
{
    throw "Not yet implemented";
    p.getZ();
    width = 0;
    std::vector<Point> bar;
    std::vector<Point> point;
    // bar
    bar.push_back(Point(0, offset - (thick / 2), -(height / 2)));
    bar.push_back(Point(0, offset - (thick / 2), (height / 4)));
    bar.push_back(Point(0, offset + (thick / 2), (height / 4)));
    bar.push_back(Point(0, offset + (thick / 2), -(height / 2)));

    // point
    for (int i = 0; i < 4; ++i) {
        double alpha = i * (360 / 4);
        point.push_back(Point(0, offset + (thick / 2) * cos(RADIAN(alpha)), (height / 4) + (thick / 2) + (thick / 2) * sin(RADIAN(alpha))));
    }

    std::vector<Triangle*> triangles;
    triangles.push_back(new Triangle(bar[0], bar[1], bar[2]));
    triangles.push_back(new Triangle(bar[2], bar[3], bar[0]));
    triangles.push_back(new Triangle(point[0], point[1], point[2]));
    triangles.push_back(new Triangle(point[2], point[3], point[0]));

    return new Polygone(triangles);
}

Polygone *AlphaFactory::createO(const Point &p, double height, double width, double thick, int offset)
{
    throw "Not yet implemented";
    p.getZ();
    std::vector<Point> points_out;
    std::vector<Point> points_in;
    points_out.push_back(Point(0, offset, - (height / 2)));
    points_out.push_back(Point(0, offset - (width / 2), 0));
    points_out.push_back(Point(0, offset, height / 2));
    points_out.push_back(Point(0, offset + (width / 2), 0));
    points_in.push_back(Point(0, offset,  -(height / 2) + thick));
    points_in.push_back(Point(0, offset -(width / 2) + thick, 0));
    points_in.push_back(Point(0, offset, (height / 2) - thick));
    points_in.push_back(Point(0, offset + (width / 2) - thick, 0));

    std::vector<Triangle*> triangles;
    for(int i = 0; i < 4; ++i) {
        triangles.push_back(new Triangle(points_out[i], points_out[(i + 1) % 4], points_in[i]));
        triangles.push_back(new Triangle(points_out[(i + 1) % 4], points_in[i], points_in[(i + 1) % 4]));
    }

    return new Polygone(triangles);
}

Polygone *AlphaFactory::createU(const Point &p, double height, double width, double thick, int offset)
{
    throw "Not yet implemented";
    p.getZ();
    std::vector<Point> points_out;
    std::vector<Point> points_in;
    points_out.push_back(Point(0, offset - (width / 2), height / 2));
    points_out.push_back(Point(0, offset - (width / 2), 0));
    points_out.push_back(Point(0, offset, -height / 2));
    points_out.push_back(Point(0, offset + (width / 2), 0));
    points_out.push_back(Point(0, offset + (width / 2), height / 2));
    points_in.push_back(Point(0, offset - (width / 2) + thick, height / 2));
    points_in.push_back(Point(0, offset - (width / 2) + thick, 0));
    points_in.push_back(Point(0, offset, -(height / 2) + thick));
    points_in.push_back(Point(0, offset + (width / 2) - thick, 0));
    points_in.push_back(Point(0, offset + (width / 2) - thick, height / 2));

    std::vector<Triangle*> triangles;
    for(int i = 0; i < 4; ++i) {
        triangles.push_back(new Triangle(points_out[i], points_out[(i + 1)], points_in[i]));
        triangles.push_back(new Triangle(points_out[(i + 1)], points_in[i], points_in[(i + 1)]));
    }

    return new Polygone(triangles);
}