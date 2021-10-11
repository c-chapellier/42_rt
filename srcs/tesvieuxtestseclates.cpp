#include "header.hpp"


void test_radian_degree()
{
    // printf("%f\n", RADIAN(180));
    // printf("%f\n", RADIAN(360));

    // printf("%f\n", sin(RADIAN(0)));
    // printf("%f\n", sin(RADIAN(30)));
    // printf("%f\n", sin(RADIAN(45)));
    // printf("%f\n", sin(RADIAN(60)));
    // printf("%f\n", sin(RADIAN(90)));
    // printf("%f\n", sin(RADIAN(180)));
    // printf("%f\n", sin(RADIAN(270)));

    // printf("%f\n", DEGREE(asin(sin(RADIAN(0)))));
    // printf("%f\n", DEGREE(asin(sin(RADIAN(30)))));
    // printf("%f\n", DEGREE(asin(sin(RADIAN(45)))));
    // printf("%f\n", DEGREE(asin(sin(RADIAN(60)))));
    // printf("%f\n", DEGREE(asin(sin(RADIAN(90)))));
    // printf("%f\n", DEGREE(asin(sin(RADIAN(180)))));
    // printf("%f\n", DEGREE(asin(sin(RADIAN(270)))));
}

void test_angle_between_vectors()
{
    // Vector v1(1, 0, 0); // + 0
    // Vector v2(1, 1, 0); // + +
    // Vector v3(0, 1, 0); // 0 +
    // Vector v4(-1, 1, 0); // - +
    // Vector v5(-1, 0, 0); // - 0
    // Vector v6(-1, -1, 0); // - -
    // Vector v7(0, -1, 0); // 0 -
    // Vector v8(1, -1, 0); // + -

    // std::cout << "angle between v1 and v1 (0): " << v1.angleWith(&v1) << " sin: " << sin(RADIAN(v1.angleWith(&v1))) << " cos: " << cos(RADIAN(v1.angleWith(&v1))) <<  " dir: " << v1.directionXY(&v1) << std::endl;
    // std::cout << "angle between v1 and v2 (45): " << v1.angleWith(&v2) << " sin: " << sin(RADIAN(v1.angleWith(&v2))) << " cos: " << cos(RADIAN(v1.angleWith(&v2))) << " dir: " << v1.directionXY(&v2) << std::endl;
    // std::cout << "angle between v1 and v3 (90): " << v1.angleWith(&v3) << " sin: " << sin(RADIAN(v1.angleWith(&v3))) << " cos: " << cos(RADIAN(v1.angleWith(&v3))) << " dir: " << v1.directionXY(&v3) << std::endl;
    // std::cout << "angle between v1 and v4 (135): " << v1.angleWith(&v4) << " sin: " << sin(RADIAN(v1.angleWith(&v4))) << " cos: " << cos(RADIAN(v1.angleWith(&v4))) << " dir: " << v1.directionXY(&v4) << std::endl;
    // std::cout << "angle between v1 and v5 (180): " << v1.angleWith(&v5) << " sin: " << sin(RADIAN(v1.angleWith(&v5))) << " cos: " << cos(RADIAN(v1.angleWith(&v5))) << " dir: " << v1.directionXY(&v5) << std::endl;
    // std::cout << "angle between v1 and v6 (225): " << v1.angleWith(&v6) << " sin: " << sin(RADIAN(v1.angleWith(&v6))) << " cos: " << cos(RADIAN(v1.angleWith(&v6))) << " dir: " << v1.directionXY(&v6) << std::endl;
    // std::cout << "angle between v1 and v7 (270): " << v1.angleWith(&v7) << " sin: " << sin(RADIAN(v1.angleWith(&v7))) << " cos: " << cos(RADIAN(v1.angleWith(&v7))) << " dir: " << v1.directionXY(&v7) << std::endl;
    // std::cout << "angle between v1 and v8 (315): " << v1.angleWith(&v8) << " sin: " << sin(RADIAN(v1.angleWith(&v8))) << " cos: " << cos(RADIAN(v1.angleWith(&v8))) << " dir: " << v1.directionXY(&v8) << std::endl;
}

void test_camera()
{
    // Camera c(0, 0, 0, 1, 1, 1, 90);
    // c.getScreen(10, 10);
}

void test_shapes()
{
    // Point *p;
    // Line *ln = new Line(0, -100, 0, 0, -1, 0);

    // Object *sp = new Sphere(100, 100, 100, 50);
    // p = sp->intersect(ln);
    // if(p){
    //     std::cout << *p << std::endl;
    //     delete(p);
    // } else {
    //     std::cout << "does not itersect" << std::endl;
    // }

    // Object *pl = new Plane(0, 5, 0, 0, 1, 0);
    // p = pl->intersect(ln);
    // std::cout << *p << std::endl;
    // if(p){
    //     std::cout << *p << std::endl;
    //     delete(p);
    // } else {
    //     std::cout << "does not itersect" << std::endl;
    // }

    // Object *qr = new Quadratic(1, 1, 1, 0, 0, 0, 0, 0, 0, -25); // circle of R = 5
    // p = qr->intersect(ln);
    // if(p){
    //     std::cout << *p << std::endl;
    //     delete(p);
    // } else {
    //     std::cout << "does not itersect" << std::endl;
    // }
}

void test_point_rotation_around_x()
{
    Point *res;
    Point p(0, 1, 1);
    std::cout << p << std::endl;

    res = p.rotateAroundX(90);
    std::cout << "Point after rotation of 90 degrees around x: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundX(180);
    std::cout << "Point after rotation of 180 degrees around x: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundX(270);
    std::cout << "Point after rotation of 270 degrees around x: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundX(360);
    std::cout << "Point after rotation of 360 degrees around x: " << *res << std::endl;
    delete(res);
}

void test_point_rotation_around_y()
{
    Point *res;
    Point p(1, 0, 1);
    std::cout << p << std::endl;

    res = p.rotateAroundY(90);
    std::cout << "Point after rotation of 90 degrees around y: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundY(180);
    std::cout << "Point after rotation of 180 degrees around y: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundY(270);
    std::cout << "Point after rotation of 270 degrees around y: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundY(360);
    std::cout << "Point after rotation of 360 degrees around y: " << *res << std::endl;
    delete(res);
}

void test_point_rotation_around_z()
{
    Point *res;
    Point p(1, 1, 0);
    std::cout << p << std::endl;

    res = p.rotateAroundZ(90);
    std::cout << "Point after rotation of 90 degrees around z: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundZ(180);
    std::cout << "Point after rotation of 180 degrees around z: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundZ(270);
    std::cout << "Point after rotation of 270 degrees around z: " << *res << std::endl;
    delete(res);
    res = p.rotateAroundZ(360);
    std::cout << "Point after rotation of 360 degrees around z: " << *res << std::endl;
    delete(res);
}

void test_point_rotation()
{
    // test_point_rotation_around_x();
    // test_point_rotation_around_y();
    // test_point_rotation_around_z();
}

void test_angle_plane_vector()
{
    // Plane p(0, 0, 0, 1, -1, 0);
    // Vector v(0, 0, 1);
    // std::cout << p.angleWith(&v) << std::endl;
}

void test()
{
    test_radian_degree();
    test_angle_between_vectors();
    test_camera();
    test_shapes();
    test_point_rotation();
    test_angle_plane_vector();
}
