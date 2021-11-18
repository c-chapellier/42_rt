#include "PolygoneFactory.hpp"

PolygoneFactory::PolygoneFactory()
{

}

void PolygoneFactory::deleteVector(std::vector<Point*> points)
{
    for (unsigned long i = 0; i < points.size(); ++i)
        delete(points[i]);
}

Polygone *PolygoneFactory::createPolygone(const std::string &type, const Point &p, double size1, double size2, double size3, double size4, double alpha, double beta, double gama)
{
    if (type == "Cube"){
        return createParallelepiped(p, size1, size1, size1, alpha, beta, gama);
    } else if (type == "1N-edron") {
        return create1NEdron(p, size1, size2, size3, alpha, beta, gama);
    } else if (type == "2N-edron") {
        return create2NEdron(p, size1, size2, size3, alpha, beta, gama);
    } else if (type == "Parallelepiped") {
        return createParallelepiped(p, size1, size2, size3, alpha, beta, gama);
    } else if (type == "Diamond") {
        return createDiamond(p, size1, size2, size3, size4, alpha, beta, gama);
    } else if (type == "Tape") {
        return createTape(p, size1, size2, size3, alpha, beta, gama);
    } else if (type == "ClosedTape") {
        return createClosedTape(p, size1, size2, size3, alpha, beta, gama);
    } else if (type == "MobiusTape") {
        return createMobiusTape(p, size1, size2, size3, alpha, beta, gama);
    } else if (type == "Spiral") {
        return createSpiral(p, size1, size2, size3, size4, alpha, beta, gama);
    } else if (type == "Tower") {
        return createTower(p, size1, size2, size3, size4, alpha, beta, gama);
    } else if (type == "Torus") {
        return createTorus(p, size1, size2, size3, size4, alpha, beta, gama);
    } else if (type == "Ring") {
        return createRing(p, size1, size2, size3, alpha, beta, gama);
    } else if (type == "Circle") {
        return createCircle(p, size1, size2, alpha, beta, gama);
    } else if (type == "Star") {
        return createStar(p, size1, size2, size3, size4, alpha, beta, gama);
    }
    throw
        "Unrecognized type of polygone";
}

Polygone *PolygoneFactory::create1NEdron(const Point &p, int precision, double height, double r, double alpha, double beta, double gama)
{
    Point *top = new Point(0, 0, height / 2);
    Point *bottom = new Point(0, 0, -height / 2);

    std::vector<Point*> points;
    for (int i = 0; i < precision; ++i){
        double angle = (double)i * (double)(360.0 / (double)precision);
        points.push_back(new Point(r * cos(RADIAN(angle)), r * sin(RADIAN(angle)), -height / 2));
    }

    Transformer::rotateAroundX(top, alpha);
    Transformer::rotateAroundX(bottom, alpha);
    Transformer::rotateAroundX(points, alpha);

    Transformer::rotateAroundY(top, beta);
    Transformer::rotateAroundY(bottom, beta);
    Transformer::rotateAroundY(points, beta);

    Transformer::rotateAroundZ(top, gama);
    Transformer::rotateAroundZ(bottom, gama);
    Transformer::rotateAroundZ(points, gama);

    Transformer::translate(top, p);
    Transformer::translate(bottom, p);
    Transformer::translate(points, p);

    std::vector<Triangle*> triangles;
    for (int i = 0; i < precision; ++i){
        triangles.push_back(new Triangle(top, points[i], points[(i + 1) % precision]));
        triangles.push_back(new Triangle(bottom, points[i], points[(i + 1) % precision]));
    }

    delete(top);
    delete(bottom);
    deleteVector(points);
    return new Polygone(triangles);
}

Polygone *PolygoneFactory::create2NEdron(const Point &p, int precision, double height, double r, double alpha, double beta, double gama)
{
    Point *top = new Point(0, 0, height);
    Point *bottom = new Point(0, 0, -height);

    std::vector<Point*> points;
    for (int i = 0; i < precision; ++i){
        double angle = (double)i * (double)(360.0 / (double)precision);
        points.push_back(new Point(r * cos(RADIAN(angle)), r * sin(RADIAN(angle)), 0));
    }

    Transformer::rotateAroundX(top, alpha);
    Transformer::rotateAroundX(bottom, alpha);
    Transformer::rotateAroundX(points, alpha);

    Transformer::rotateAroundY(top, beta);
    Transformer::rotateAroundY(bottom, beta);
    Transformer::rotateAroundY(points, beta);

    Transformer::rotateAroundZ(top, gama);
    Transformer::rotateAroundZ(bottom, gama);
    Transformer::rotateAroundZ(points, gama);

    Transformer::translate(top, p);
    Transformer::translate(bottom, p);
    Transformer::translate(points, p);

    std::vector<Triangle*> triangles;
    for (int i = 0; i < precision; ++i){
        triangles.push_back(new Triangle(top, points[i], points[(i + 1) % precision]));
        triangles.push_back(new Triangle(bottom, points[i], points[(i + 1) % precision]));
    }

    delete(top);
    delete(bottom);
    deleteVector(points);
    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createParallelepiped(const Point &p, double height, double width, double length, double alpha, double beta, double gama)
{
    Point *p1 = new Point(-(width / 2), -(length / 2), height / 2);
    Point *p2 = new Point(width / 2, -(length / 2), height / 2);
    Point *p3 = new Point(width / 2, length / 2, height / 2);
    Point *p4 = new Point(-(width / 2), length / 2, height / 2);
    Point *p5 = new Point(-(width / 2), -(length / 2), -(height / 2));
    Point *p6 = new Point(width / 2, -(length / 2), -(height / 2));
    Point *p7 = new Point(width / 2, length / 2, -(height / 2));
    Point *p8 = new Point(-(width / 2), length / 2, -(height / 2));

    std::vector<Point*> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
    points.push_back(p7);
    points.push_back(p8);

    Transformer::rotateAroundX(points, alpha);
    Transformer::rotateAroundY(points, beta);
    Transformer::rotateAroundZ(points, gama);

    Transformer::translate(points, p);

    std::vector<Triangle*> triangles;
    // top face
    triangles.push_back(new Triangle(p1, p2, p3));
    triangles.push_back(new Triangle(p1, p4, p3));
    // front face
    triangles.push_back(new Triangle(p1, p4, p8));
    triangles.push_back(new Triangle(p1, p5, p8));
    // left face
    triangles.push_back(new Triangle(p1, p5, p6));
    triangles.push_back(new Triangle(p1, p2, p6));
    // back face
    triangles.push_back(new Triangle(p2, p6, p7));
    triangles.push_back(new Triangle(p2, p3, p7));
    // right face
    triangles.push_back(new Triangle(p4, p3, p7));
    triangles.push_back(new Triangle(p4, p8, p7));
    // bottom face
    triangles.push_back(new Triangle(p5, p8, p7));
    triangles.push_back(new Triangle(p5, p6, p7));

    deleteVector(points);
    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createDiamond(const Point &p, double h, double H, double r, double R, double alpha, double beta, double gama)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;
    Point *top = new Point(0, 0, 0);
    Point *bottom = new Point(0, 0, -h -H);

    for(int i = 0; i < 6; ++i) {
        sup_points.push_back(new Point(r * cos(RADIAN(i * 60)), r * sin(RADIAN(i * 60)), 0));
        inf_points.push_back(new Point(R * cos(RADIAN(i * 60)), R * sin(RADIAN(i * 60)), -h));
    }

    Transformer::rotateAroundX(top, alpha);
    Transformer::rotateAroundX(bottom, alpha);
    Transformer::rotateAroundX(sup_points, alpha);
    Transformer::rotateAroundX(inf_points, alpha);

    Transformer::rotateAroundY(top, beta);
    Transformer::rotateAroundY(bottom, beta);
    Transformer::rotateAroundY(sup_points, beta);
    Transformer::rotateAroundY(inf_points, beta);

    Transformer::rotateAroundZ(top, gama);
    Transformer::rotateAroundZ(bottom, gama);
    Transformer::rotateAroundZ(sup_points, gama);
    Transformer::rotateAroundZ(inf_points, gama);

    Transformer::translate(top, p);
    Transformer::translate(bottom, p);
    Transformer::translate(sup_points, p);
    Transformer::translate(inf_points, p);

    std::vector<Triangle*> triangles;

    for (int i = 0; i < 6; ++i) {
        triangles.push_back(new Triangle(top, sup_points[i], sup_points[(i + 1) % 6]));
        triangles.push_back(new Triangle(bottom, inf_points[i], inf_points[(i + 1) % 6]));
        triangles.push_back(new Triangle(sup_points[i], sup_points[(i + 1) % 6], inf_points[i]));
        triangles.push_back(new Triangle(inf_points[i], inf_points[(i + 1) % 6], sup_points[(i + 1) % 6]));
    }

    delete(top);
    delete(bottom);
    deleteVector(inf_points);
    deleteVector(sup_points);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createTape(const Point &p, double R, double width, int precision, double alpha, double beta, double gama)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;

    for(int i = 0; i < precision; ++i) {
        double angle = i * (360 / precision);
        sup_points.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), 0));
        inf_points.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), -width));
    }

    Transformer::rotateAroundX(sup_points, alpha);
    Transformer::rotateAroundX(inf_points, alpha);

    Transformer::rotateAroundY(sup_points, beta);
    Transformer::rotateAroundY(inf_points, beta);

    Transformer::rotateAroundZ(sup_points, gama);
    Transformer::rotateAroundZ(inf_points, gama);

    Transformer::translate(sup_points, p);
    Transformer::translate(inf_points, p);

    std::vector<Triangle*> triangles;

    for(int i = 0; i < precision; ++i) {
        triangles.push_back(new Triangle(sup_points[i], sup_points[(i + 1) % precision], inf_points[i]));
        triangles.push_back(new Triangle(inf_points[i], inf_points[(i + 1) % precision], sup_points[(i + 1) % precision]));
    }

    deleteVector(inf_points);
    deleteVector(sup_points);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createClosedTape(const Point &p, double R, double width, int precision, double alpha, double beta, double gama)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;
    Point *top = new Point(0, 0, width / 2);
    Point *bottom = new Point(0, 0, -width / 2);

    for(int i = 0; i < precision; ++i) {
        double angle = i * (360 / precision);
        sup_points.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), width / 2));
        inf_points.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), -width / 2));
    }

    Transformer::rotateAroundX(sup_points, alpha);
    Transformer::rotateAroundX(inf_points, alpha);
    Transformer::rotateAroundX(top, alpha);
    Transformer::rotateAroundX(bottom, alpha);

    Transformer::rotateAroundY(sup_points, beta);
    Transformer::rotateAroundY(inf_points, beta);
    Transformer::rotateAroundY(top, beta);
    Transformer::rotateAroundY(bottom, beta);

    Transformer::rotateAroundZ(sup_points, gama);
    Transformer::rotateAroundZ(inf_points, gama);
    Transformer::rotateAroundZ(top, gama);
    Transformer::rotateAroundZ(bottom, gama);

    Transformer::translate(sup_points, p);
    Transformer::translate(inf_points, p);
    Transformer::translate(top, p);
    Transformer::translate(bottom, p);

    std::vector<Triangle*> triangles;

    for(int i = 0; i < precision; ++i) {
        triangles.push_back(new Triangle(sup_points[i], sup_points[(i + 1) % precision], inf_points[i]));
        triangles.push_back(new Triangle(inf_points[i], inf_points[(i + 1) % precision], sup_points[(i + 1) % precision]));
        triangles.push_back(new Triangle(sup_points[i], sup_points[(i + 1) % precision], top));
        triangles.push_back(new Triangle(inf_points[i], inf_points[(i + 1) % precision], bottom));
    }

    delete(top);
    delete(bottom);
    deleteVector(inf_points);
    deleteVector(sup_points);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createMobiusTape(const Point &p, double R, double width, int precision, double alpha, double beta, double gama)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;

    for(int i = 0; i < precision; ++i) {
        double angle1 = (double)i * (double)(360.0 / (double)precision);
        double angle2 = angle1 / 2.0;
        double h = angle2 < 90 ? sin(RADIAN(angle2)) * (width / 2) : (width / 2) + (-cos(RADIAN(angle2)) * (width / 2));
        double r1 = R + (angle2 < 90 ? (sin(RADIAN(angle2)) * (width / 2)) : (width / 2) + (cos(RADIAN(angle2)) * (width / 2)));
        double r2 = R + (angle2 < 90 ? -(sin(RADIAN(angle2)) * (width / 2)) : -(width / 2) - (cos(RADIAN(angle2)) * (width / 2)));

        sup_points.push_back(new Point(r1 * cos(RADIAN(angle1)), r1 * sin(RADIAN(angle1)), -h));
        inf_points.push_back(new Point(r2 * cos(RADIAN(angle1)), r2 * sin(RADIAN(angle1)), -width + h));
    }

    Transformer::rotateAroundX(sup_points, alpha);
    Transformer::rotateAroundX(inf_points, alpha);

    Transformer::rotateAroundY(sup_points, beta);
    Transformer::rotateAroundY(inf_points, beta);

    Transformer::rotateAroundZ(sup_points, gama);
    Transformer::rotateAroundZ(inf_points, gama);

    Transformer::translate(sup_points, p);
    Transformer::translate(inf_points, p);

    std::vector<Triangle*> triangles;

    for(int i = 0; i < precision - 1; ++i) {
        triangles.push_back(new Triangle(sup_points[i], sup_points[(i + 1) % precision], inf_points[i]));
        triangles.push_back(new Triangle(inf_points[i], inf_points[(i + 1) % precision], sup_points[(i + 1) % precision]));
    }
    triangles.push_back(new Triangle(sup_points[0], inf_points[0], inf_points[precision - 1]));
    triangles.push_back(new Triangle(inf_points[precision - 1], sup_points[precision - 1], inf_points[0]));

    deleteVector(inf_points);
    deleteVector(sup_points);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createSpiral(const Point &p, double R, double width, int precision, int nb_turns, double alpha, double beta, double gama)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;

    for(int i = 0; i < precision * nb_turns; ++i) {
        double angle = i * (360 / precision);
        double h = (i / precision) * (width * 2) + (i % precision) * ((width * 2) / precision);
        sup_points.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), h));
        inf_points.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), -width + h));
    }

    Transformer::rotateAroundX(sup_points, alpha);
    Transformer::rotateAroundX(inf_points, alpha);

    Transformer::rotateAroundY(sup_points, beta);
    Transformer::rotateAroundY(inf_points, beta);

    Transformer::rotateAroundZ(sup_points, gama);
    Transformer::rotateAroundZ(inf_points, gama);

    Transformer::translate(sup_points, p);
    Transformer::translate(inf_points, p);

    std::vector<Triangle*> triangles;

    for(int i = 0; i < (precision * nb_turns) - 1; ++i) {
        triangles.push_back(new Triangle(sup_points[i], sup_points[(i + 1) % (precision * nb_turns)], inf_points[i]));
        triangles.push_back(new Triangle(inf_points[i], inf_points[(i + 1) % (precision * nb_turns)], sup_points[(i + 1) % (precision * nb_turns)]));
    }

    deleteVector(inf_points);
    deleteVector(sup_points);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createTower(const Point &p, double R, double width, int precision, int layers, double alpha, double beta, double gama)
{
    std::vector< std::vector<Point*> > points;

    for(int k = 0; k < layers; ++k) {
        std::vector<Point*> tmp;
        double offset = k % 2 == 0 ? 0 : (360 / precision) / 2;
        for(int i = 0; i < precision; ++i) {
            double angle = (i * (360 / precision)) + offset;
            tmp.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), (k * width)));
        }
        points.push_back(tmp);
    }

    for (int k = 0; k < layers; ++k) {
        Transformer::rotateAroundX(points[k], alpha);
        Transformer::rotateAroundY(points[k], beta);
        Transformer::rotateAroundZ(points[k], gama);
    }

    for (int k = 0; k < layers; ++k)
        Transformer::translate(points[k], p);

    std::vector<Triangle*> triangles;

    for (int k = 0; k < layers - 1; ++k) {
        for (int i = 0; i < precision; ++i) {
            if ( k % 2 == 0){
                triangles.push_back(new Triangle(points[k][i], points[k][(i + 1) % precision], points[k + 1][i]));
                triangles.push_back(new Triangle(points[k + 1][i], points[k + 1][(i + 1) % precision], points[k][(i + 1) % precision]));
            } else {
                triangles.push_back(new Triangle(points[k][i], points[k + 1][i], points[k + 1][(i + 1) % precision]));
                triangles.push_back(new Triangle(points[k][i], points[k][(i + 1) % precision], points[k + 1][(i + 1) % precision]));
            }
        }
    }

    for(int k = 0; k < layers; ++k) {
        deleteVector(points[k]);
    }
    
    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createTorus(const Point &p, double R, double r, int precision, int layers, double alpha, double beta, double gama)
{
    std::vector< std::vector<Point*> > points;

    for(int k = 0; k < layers; ++k) {
        std::vector<Point*> tmp;
        double angle1 = (double)k * (360.0 / (double)layers);
        double h = r * sin(RADIAN(angle1));
        double r1 = r * cos(RADIAN(angle1));
        for (int i = 0; i < precision; ++i) {
            double angle2 = (double)i * (360.0 / (double)precision);
            tmp.push_back(new Point(((R - r1) * (cos(RADIAN(angle2)))), ((R - r1) * (sin(RADIAN(angle2)))), h));
        }
        points.push_back(tmp);
    }

    for(int k = 0; k < layers; ++k){
        Transformer::rotateAroundX(points[k], alpha);
        Transformer::rotateAroundY(points[k], beta);
        Transformer::rotateAroundZ(points[k], gama);
    }

    for(int k = 0; k < layers; ++k)
        Transformer::translate(points[k], p);

    std::vector<Triangle*> triangles;

    for(int k = 0; k < layers; ++k){
        for(int i = 0; i < precision; ++i) {
            triangles.push_back(new Triangle(points[k][i], points[k][(i + 1) % precision], points[(k + 1) % layers][i]));
            triangles.push_back(new Triangle(points[(k + 1) % layers][i], points[(k + 1) % layers][(i + 1) % precision], points[k][(i + 1) % precision]));
        }
    }

    for(int k = 0; k < layers; ++k) {
        deleteVector(points[k]);
    }

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createRing(const Point &p, double R, double r, int precision, double alpha, double beta, double gama)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;

    for(int i = 0; i < precision; ++i) {
        double angle = i * (360 / precision);
        sup_points.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), 0));
        inf_points.push_back(new Point(r * cos(RADIAN(angle)), r * sin(RADIAN(angle)), 0));
    }

    Transformer::rotateAroundX(sup_points, alpha);
    Transformer::rotateAroundX(inf_points, alpha);

    Transformer::rotateAroundY(sup_points, beta);
    Transformer::rotateAroundY(inf_points, beta);

    Transformer::rotateAroundZ(sup_points, gama);
    Transformer::rotateAroundZ(inf_points, gama);

    Transformer::translate(sup_points, p);
    Transformer::translate(inf_points, p);

    std::vector<Triangle*> triangles;

    for(int i = 0; i < precision; ++i) {
        triangles.push_back(new Triangle(sup_points[i], sup_points[(i + 1) % precision], inf_points[i]));
        triangles.push_back(new Triangle(inf_points[i], inf_points[(i + 1) % precision], sup_points[(i + 1) % precision]));
    }

    deleteVector(inf_points);
    deleteVector(sup_points);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createCircle(const Point &p, double R, int precision, double alpha, double beta, double gama)
{
    std::vector<Point*> points;
    Point *center = new Point(0, 0, 0);

    for(int i = 0; i < precision; ++i) {
        double angle = i * (360 / precision);
        points.push_back(new Point(R * cos(RADIAN(angle)), R * sin(RADIAN(angle)), 0));
    }

    Transformer::rotateAroundX(points, alpha);
    Transformer::rotateAroundY(points, beta);
    Transformer::rotateAroundZ(points, gama);

    Transformer::translate(points, p);
    Transformer::translate(center, p);

    std::vector<Triangle*> triangles;

    for(int i = 0; i < precision; ++i) {
        triangles.push_back(new Triangle(points[i], points[(i + 1) % precision], center));
    }

    delete(center);
    deleteVector(points);

    return new Polygone(triangles);
}

Polygone *PolygoneFactory::createStar(const Point &p, double R, double r, double thick, int branch, double alpha, double beta, double gama)
{
    std::vector<Point*> sup_points;
    std::vector<Point*> inf_points;
    Point *top = new Point(0, 0, thick / 2);
    Point *bottom = new Point(0, 0, -thick / 2);

    double angle = 360.0 / branch;

    for(int i = 0; i < branch; ++i) {
        double angle1 = i * angle;
        double angle2 = angle1 + (angle / 2);
        sup_points.push_back(new Point(R * cos(RADIAN(angle1)), R * sin(RADIAN(angle1)), 0));
        inf_points.push_back(new Point(r * cos(RADIAN(angle2)), r * sin(RADIAN(angle2)), 0));
    }

    Transformer::rotateAroundX(sup_points, alpha);
    Transformer::rotateAroundX(inf_points, alpha);
    Transformer::rotateAroundX(top, alpha);
    Transformer::rotateAroundX(bottom, alpha);

    Transformer::rotateAroundY(sup_points, beta);
    Transformer::rotateAroundY(inf_points, beta);
    Transformer::rotateAroundY(top, beta);
    Transformer::rotateAroundY(bottom, beta);

    Transformer::rotateAroundZ(sup_points, gama);
    Transformer::rotateAroundZ(inf_points, gama);
    Transformer::rotateAroundZ(top, gama);
    Transformer::rotateAroundZ(bottom, gama);

    Transformer::translate(sup_points, p);
    Transformer::translate(inf_points, p);
    Transformer::translate(top, p);
    Transformer::translate(bottom, p);

    std::vector<Triangle*> triangles;

    for(int i = 0; i < branch; ++i) {
        triangles.push_back(new Triangle(sup_points[i], inf_points[i], top));
        triangles.push_back(new Triangle(sup_points[i], inf_points[i], bottom));
        triangles.push_back(new Triangle(inf_points[i], sup_points[(i + 1) % branch], top));
        triangles.push_back(new Triangle(inf_points[i], sup_points[(i + 1) % branch], bottom));
    }

    delete(top);
    delete(bottom);
    deleteVector(inf_points);
    deleteVector(sup_points);

    return new Polygone(triangles);
}