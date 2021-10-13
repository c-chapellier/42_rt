#include "PolygoneFactory.hpp"

PolygoneFactory::PolygoneFactory()
{

}

Polygone *PolygoneFactory::createPolygone(std::string type, Point &p, double size1, double size2, double size3, double size4)
{
    if (type == "Cube"){
        return createParallelepiped(p, size1, size1, size1);
    } else if (type == "2N-edron") {
        return create2NEdron(p, size1, size2, size3);
    } else if (type == "Parallelepiped") {
        return createParallelepiped(p, size1, size2, size3);
    } else if (type == "Diamond") {
        return createDiamond(p, size1, size2, size3, size4);
    } else if (type == "Tape") {
        return createTape(p, size1, size2, size3);
    } else if (type == "MobiusTape") {
        return createMobiusTape(p, size1, size2, size3);
    } else if (type == "Spiral") {
        return createSpiral(p, size1, size2, size3, size4);
    } else if (type == "Tower") {
        return createTower(p, size1, size2, size3, size4);
    }
    throw
        "Unrecognized type of polygone";
}

Polygone *PolygoneFactory::create2NEdron(Point &p, int precision, double height, double r)
{
    Point *top = new Point(p.getX(), p.getY(), p.getZ() + height);
    Point *bottom = new Point(p.getX(), p.getY(), p.getZ() - height);

    std::vector<Point*> points;
    for (int i = 0; i < precision; ++i){
        double alpha = (double)i * (double)(360.0 / (double)precision);
        points.push_back(new Point(p.getX() + (r * cos(RADIAN(alpha))), p.getY() + (r * sin(RADIAN(alpha))), p.getZ()));
    }

    std::vector<Triangle*> triangles;
    for (int i = 0; i < precision; ++i){
        triangles.push_back(new Triangle(*top, *points[i], *points[(i + 1) % precision]));
        triangles.push_back(new Triangle(*bottom, *points[i], *points[(i + 1) % precision]));
    }

    delete(top);
    delete(bottom);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createParallelepiped(Point &p, double height, double width, double length)
{
    Point *p1 = new Point(p.getX() - (width / 2), p.getY() - (length / 2), p.getZ() + (height / 2));
    Point *p2 = new Point(p.getX() + (width / 2), p.getY() - (length / 2), p.getZ() + (height / 2));
    Point *p3 = new Point(p.getX() + (width / 2), p.getY() + (length / 2), p.getZ() + (height / 2));
    Point *p4 = new Point(p.getX() - (width / 2), p.getY() + (length / 2), p.getZ() + (height / 2));
    Point *p5 = new Point(p.getX() - (width / 2), p.getY() - (length / 2), p.getZ() - (height / 2));
    Point *p6 = new Point(p.getX() + (width / 2), p.getY() - (length / 2), p.getZ() - (height / 2));
    Point *p7 = new Point(p.getX() + (width / 2), p.getY() + (length / 2), p.getZ() - (height / 2));
    Point *p8 = new Point(p.getX() - (width / 2), p.getY() + (length / 2), p.getZ() - (height / 2));

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

Polygone *PolygoneFactory::createTape(Point &p, double R, double width, int precision)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;

    for(int i = 0; i < precision; ++i) {
        double alpha = i * (360 / precision);
        sup_points.push_back(new Point(p.getX() + R * cos(RADIAN(alpha)), p.getY() + R * sin(RADIAN(alpha)), p.getZ()));
        inf_points.push_back(new Point(p.getX() + R * cos(RADIAN(alpha)), p.getY() + R * sin(RADIAN(alpha)), p.getZ() - width));
    }

    std::vector<Triangle*> triangles;

    for(int i = 0; i < precision; ++i) {
        triangles.push_back(new Triangle(*sup_points[i], *sup_points[(i + 1) % precision], *inf_points[i]));
        triangles.push_back(new Triangle(*inf_points[i], *inf_points[(i + 1) % precision], *sup_points[(i + 1) % precision]));
    }

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createMobiusTape(Point &p, double R, double width, int precision)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;

    for(int i = 0; i < precision; ++i) {
        double alpha = (double)i * (double)(360.0 / (double)precision);
        double beta = alpha / 2.0;
        double h = beta < 90 ? sin(RADIAN(beta)) * (width / 2) : (width / 2) + (-cos(RADIAN(beta)) * (width / 2));
        double r1 = R + (beta < 90 ? (sin(RADIAN(beta)) * (width / 2)) : (width / 2) + (cos(RADIAN(beta)) * (width / 2)));
        double r2 = R + (beta < 90 ? -(sin(RADIAN(beta)) * (width / 2)) : -(width / 2) - (cos(RADIAN(beta)) * (width / 2)));

        sup_points.push_back(new Point(p.getX() + r1 * cos(RADIAN(alpha)), p.getY() + r1 * sin(RADIAN(alpha)), p.getZ() - h));
        inf_points.push_back(new Point(p.getX() + r2 * cos(RADIAN(alpha)), p.getY() + r2 * sin(RADIAN(alpha)), p.getZ() - width + h));
    }

    std::vector<Triangle*> triangles;

    for(int i = 0; i < precision - 1; ++i) {
        triangles.push_back(new Triangle(*sup_points[i], *sup_points[(i + 1) % precision], *inf_points[i]));
        triangles.push_back(new Triangle(*inf_points[i], *inf_points[(i + 1) % precision], *sup_points[(i + 1) % precision]));
    }
    triangles.push_back(new Triangle(*sup_points[0], *inf_points[0], *inf_points[precision - 1]));
    triangles.push_back(new Triangle(*inf_points[precision - 1], *sup_points[precision - 1], *inf_points[0]));

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createSpiral(Point &p, double R, double width, int precision, int nb_turns)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;

    for(int i = 0; i < precision * nb_turns; ++i) {
        double alpha = i * (360 / precision);
        double h = (i / precision) * (width * 2) + (i % precision) * ((width * 2) / precision);
        sup_points.push_back(new Point(p.getX() + R * cos(RADIAN(alpha)), p.getY() + R * sin(RADIAN(alpha)), p.getZ() + h));
        inf_points.push_back(new Point(p.getX() + R * cos(RADIAN(alpha)), p.getY() + R * sin(RADIAN(alpha)), p.getZ() - width + h));
    }

    std::vector<Triangle*> triangles;

    for(int i = 0; i < (precision * nb_turns) - 1; ++i) {
        triangles.push_back(new Triangle(*sup_points[i], *sup_points[(i + 1) % (precision * nb_turns)], *inf_points[i]));
        triangles.push_back(new Triangle(*inf_points[i], *inf_points[(i + 1) % (precision * nb_turns)], *sup_points[(i + 1) % (precision * nb_turns)]));
    }

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createTower(Point &p, double R, double width, int precision, int layers)
{
    std::vector<std::vector<Point*>> points;

    for(int k = 0; k < layers; ++k){
        std::vector<Point*> tmp;
        double offset = k % 2 == 0 ? 0 : (360 / precision) / 2;
        for(int i = 0; i < precision; ++i) {
            double alpha = (i * (360 / precision)) + offset;
            tmp.push_back(new Point(p.getX() + R * cos(RADIAN(alpha)), p.getY() + R * sin(RADIAN(alpha)), p.getZ() + (k * width)));
        }
        points.push_back(tmp);
    }

    std::vector<Triangle*> triangles;

    for(int k = 0; k < layers - 1; ++k){
        for(int i = 0; i < precision; ++i) {
            // K even
            if ( k % 2 == 0){
                triangles.push_back(new Triangle(*points[k][i], *points[k][(i + 1) % precision], *points[k + 1][i]));
                triangles.push_back(new Triangle(*points[k + 1][i], *points[k + 1][(i + 1) % precision], *points[k][(i + 1) % precision]));
            } else {
                triangles.push_back(new Triangle(*points[k][i], *points[k + 1][i], *points[k + 1][(i + 1) % precision]));
                triangles.push_back(new Triangle(*points[k][i], *points[k][(i + 1) % precision], *points[k + 1][(i + 1) % precision]));
            }
        }
    }

    // unsigned long size = triangles.size();
    // for (unsigned long i = 0; i < size; ++i) {
    //     int ra = rand();
    //     if (ra % 3 == 0){
    //         if(i < triangles.size())
    //             triangles.erase(triangles.begin() + i);
    //     }
    // }
    
    return new Polygone(triangles);
}