#include "PolygoneFactory.hpp"

PolygoneFactory::PolygoneFactory()
{

}

Polygone *PolygoneFactory::createPolygone(std::string type, Point &p, double size1, double size2, double size3, double size4)
{
    if (type == "Cube"){
        return createCube(p, size1);
    } else if (type == "Octohedron") {
        return createOctohedron(p, size1, size2);
    } else if (type == "Parallelepiped") {
        return createParallelepiped(p, size1, size2, size3);
    } else if (type == "Diamond") {
        return createDiamond(p, size1, size2, size3, size4);
    } else {
        return NULL;
    }
}

Polygone *PolygoneFactory::createOctohedron(Point &p, double height, double width)
{
    Point *p1 = new Point(p);
    Point *p2 = new Point(p.getX() - width, p.getY(), p.getZ() - height);
    Point *p3 = new Point(p.getX(), p.getY() - width, p.getZ() - height);
    Point *p4 = new Point(p.getX() + width, p.getY(), p.getZ() - height);
    Point *p5 = new Point(p.getX(), p.getY() + width, p.getZ() - height);
    Point *p6 = new Point(p.getX(), p.getY() , p.getZ() - (2 * height));

    std::vector<Triangle *> triangles;
    triangles.push_back(new Triangle(*p1, *p2, *p3));
    triangles.push_back(new Triangle(*p1, *p3, *p4));
    triangles.push_back(new Triangle(*p1, *p4, *p5));
    triangles.push_back(new Triangle(*p1, *p5, *p2));
    triangles.push_back(new Triangle(*p6, *p2, *p3));
    triangles.push_back(new Triangle(*p6, *p3, *p4));
    triangles.push_back(new Triangle(*p6, *p4, *p5));
    triangles.push_back(new Triangle(*p6, *p5, *p2));

    delete(p1);
    delete(p2);
    delete(p3);
    delete(p4);
    delete(p5);
    delete(p6);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createCube(Point &p, double size)
{
    Point *p1 = new Point(p);
    Point *p2 = new Point(p.getX() + size, p.getY(), p.getZ());
    Point *p3 = new Point(p.getX() + size, p.getY() + size, p.getZ());
    Point *p4 = new Point(p.getX(), p.getY() + size, p.getZ());
    Point *p5 = new Point(p.getX(), p.getY(), p.getZ() - size);
    Point *p6 = new Point(p.getX() + size, p.getY(), p.getZ() - size);
    Point *p7 = new Point(p.getX() + size, p.getY() + size, p.getZ() - size);
    Point *p8 = new Point(p.getX(), p.getY() + size, p.getZ() - size);

    std::vector<Triangle *> triangles;
    // top face
    triangles.push_back(new Triangle(*p1, *p2, *p3));
    triangles.push_back(new Triangle(*p1, *p4, *p3));
    // front face
    triangles.push_back(new Triangle(*p1, *p4, *p8));
    triangles.push_back(new Triangle(*p1, *p5, *p8));
    // left face
    triangles.push_back(new Triangle(*p1, *p5, *p6));
    triangles.push_back(new Triangle(*p1, *p2, *p6));
    // back face
    triangles.push_back(new Triangle(*p2, *p6, *p7));
    triangles.push_back(new Triangle(*p2, *p3, *p7));
    // right face
    triangles.push_back(new Triangle(*p4, *p3, *p7));
    triangles.push_back(new Triangle(*p4, *p8, *p7));
    // bottom face
    triangles.push_back(new Triangle(*p5, *p8, *p7));
    triangles.push_back(new Triangle(*p5, *p6, *p7));

    delete(p1);
    delete(p2);
    delete(p3);
    delete(p4);
    delete(p5);
    delete(p6);
    delete(p7);
    delete(p8);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createParallelepiped(Point &p, double height, double width, double length)
{
    Point *p1 = new Point(p);
    Point *p2 = new Point(p.getX() + width, p.getY(), p.getZ());
    Point *p3 = new Point(p.getX() + width, p.getY() + length, p.getZ());
    Point *p4 = new Point(p.getX(), p.getY() + length, p.getZ());
    Point *p5 = new Point(p.getX(), p.getY(), p.getZ() - height);
    Point *p6 = new Point(p.getX() + width, p.getY(), p.getZ() - height);
    Point *p7 = new Point(p.getX() + width, p.getY() + length, p.getZ() - height);
    Point *p8 = new Point(p.getX(), p.getY() + length, p.getZ() - height);

    std::vector<Triangle *> triangles;
    // top face
    triangles.push_back(new Triangle(*p1, *p2, *p3));
    triangles.push_back(new Triangle(*p1, *p4, *p3));
    // front face
    triangles.push_back(new Triangle(*p1, *p4, *p8));
    triangles.push_back(new Triangle(*p1, *p5, *p8));
    // left face
    triangles.push_back(new Triangle(*p1, *p5, *p6));
    triangles.push_back(new Triangle(*p1, *p2, *p6));
    // back face
    triangles.push_back(new Triangle(*p2, *p6, *p7));
    triangles.push_back(new Triangle(*p2, *p3, *p7));
    // right face
    triangles.push_back(new Triangle(*p4, *p3, *p7));
    triangles.push_back(new Triangle(*p4, *p8, *p7));
    // bottom face
    triangles.push_back(new Triangle(*p5, *p8, *p7));
    triangles.push_back(new Triangle(*p5, *p6, *p7));

    delete(p1);
    delete(p2);
    delete(p3);
    delete(p4);
    delete(p5);
    delete(p6);
    delete(p7);
    delete(p8);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createDiamond(Point &p, double h, double H, double r, double R)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;
    Point *top = new Point(p);
    Point *bottom = new Point(p.getX(), p.getY(), p.getZ() - h -H);
    for(int i = 0; i < 6; ++i) {
        sup_points.push_back(new Point(p.getX() + r * cos(RADIAN(i * 60)), p.getY() + r * sin(RADIAN(i * 60)), p.getZ()));
        inf_points.push_back(new Point(p.getX() + R * cos(RADIAN(i * 60)), p.getY() + R * sin(RADIAN(i * 60)), p.getZ() - h));
    }

    std::vector<Triangle*> triangles;

    for(int i = 0; i < 6; ++i) {
        triangles.push_back(new Triangle(*top, *sup_points[i], *sup_points[(i + 1) % 6]));
        triangles.push_back(new Triangle(*bottom, *inf_points[i], *inf_points[(i + 1) % 6]));
        triangles.push_back(new Triangle(*sup_points[i], *sup_points[(i + 1) % 6], *inf_points[i]));
        triangles.push_back(new Triangle(*inf_points[i], *inf_points[(i + 1) % 6], *sup_points[(i + 1) % 6]));
    }

    return new Polygone(triangles);
}