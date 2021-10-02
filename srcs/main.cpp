#include "header.hpp"

void test()
{
    printf("%f\n", RADIAN(180));
    printf("%f\n", RADIAN(360));

    printf("%f\n", sin(RADIAN(0)));
    printf("%f\n", sin(RADIAN(30)));
    printf("%f\n", sin(RADIAN(45)));
    printf("%f\n", sin(RADIAN(60)));
    printf("%f\n", sin(RADIAN(90)));
    printf("%f\n", sin(RADIAN(180)));
    printf("%f\n", sin(RADIAN(270)));

    printf("%f\n", DEGREE(asin(sin(RADIAN(0)))));
    printf("%f\n", DEGREE(asin(sin(RADIAN(30)))));
    printf("%f\n", DEGREE(asin(sin(RADIAN(45)))));
    printf("%f\n", DEGREE(asin(sin(RADIAN(60)))));
    printf("%f\n", DEGREE(asin(sin(RADIAN(90)))));
    printf("%f\n", DEGREE(asin(sin(RADIAN(180)))));
    printf("%f\n", DEGREE(asin(sin(RADIAN(270)))));

    Vector *v1 = new Vector(1, 0, 0); // + 0
    Vector *v2 = new Vector(1, 1, 0); // + +
    Vector *v3 = new Vector(0, 1, 0); // 0 +
    Vector *v4 = new Vector(-1, 1, 0); // - +
    Vector *v5 = new Vector(-1, 0, 0); // - 0
    Vector *v6 = new Vector(-1, -1, 0); // - -
    Vector *v7 = new Vector(0, -1, 0); // 0 -
    Vector *v8 = new Vector(1, -1, 0); // + -

    std::cout << "angle between v1 and v1 (0): " << v1->angleWith(v1) << " sin: " << sin(RADIAN(v1->angleWith(v1))) << " cos: " << cos(RADIAN(v1->angleWith(v1))) <<  " dir: " << v1->directionXY(v1) << std::endl;
    std::cout << "angle between v1 and v2 (45): " << v1->angleWith(v2) << " sin: " << sin(RADIAN(v1->angleWith(v2))) << " cos: " << cos(RADIAN(v1->angleWith(v2))) << " dir: " << v1->directionXY(v2) << std::endl;
    std::cout << "angle between v1 and v3 (90): " << v1->angleWith(v3) << " sin: " << sin(RADIAN(v1->angleWith(v3))) << " cos: " << cos(RADIAN(v1->angleWith(v3))) << " dir: " << v1->directionXY(v3) << std::endl;
    std::cout << "angle between v1 and v4 (135): " << v1->angleWith(v4) << " sin: " << sin(RADIAN(v1->angleWith(v4))) << " cos: " << cos(RADIAN(v1->angleWith(v4))) << " dir: " << v1->directionXY(v4) << std::endl;
    std::cout << "angle between v1 and v5 (180): " << v1->angleWith(v5) << " sin: " << sin(RADIAN(v1->angleWith(v5))) << " cos: " << cos(RADIAN(v1->angleWith(v5))) << " dir: " << v1->directionXY(v5) << std::endl;
    std::cout << "angle between v1 and v6 (225): " << v1->angleWith(v6) << " sin: " << sin(RADIAN(v1->angleWith(v6))) << " cos: " << cos(RADIAN(v1->angleWith(v6))) << " dir: " << v1->directionXY(v6) << std::endl;
    std::cout << "angle between v1 and v7 (270): " << v1->angleWith(v7) << " sin: " << sin(RADIAN(v1->angleWith(v7))) << " cos: " << cos(RADIAN(v1->angleWith(v7))) << " dir: " << v1->directionXY(v7) << std::endl;
    std::cout << "angle between v1 and v8 (315): " << v1->angleWith(v8) << " sin: " << sin(RADIAN(v1->angleWith(v8))) << " cos: " << cos(RADIAN(v1->angleWith(v8))) << " dir: " << v1->directionXY(v8) << std::endl;

    Camera c(0, 0, 0, 0, 0, 1, 90);
    c.getScreen(10, 10);
}

int main(void)
{
    srand(time(NULL));

    test();

    
    Window win(600, 600);

    Pixel pxl(255, 0, 0, 255);

    std::vector< std::vector<Pixel> > pxls;
    pxls.resize(600, std::vector<Pixel>(600));

    for (int i = 0; i < 600; ++i)
        for (int j = 0; j < 600; ++j)
            pxls[i][j] = pxl;

    Image img(600, 600, pxls);

    Point *p;
    Line *ln = new Line(0, -100, 0, 0, -1, 0);

    Object *sp = new Sphere(0, 0, 0, 10);
    p = sp->intersect(ln);
    std::cout << *p << std::endl;
    if(p)
        delete(p);

    Object *pl = new Plane(0, 5, 0, 0, 1, 0);
    p = pl->intersect(ln);
    std::cout << *p << std::endl;
    if(p)
        delete(p);

    Object *qr = new Quadratic(1, 1, 1, 0, 0, 0, 0, 0, 0, -25); // circle of R = 5
    p = qr->intersect(ln);
    std::cout << *p << std::endl;
    if(p)
        delete(p);

    // delete(sp);
    // delete(pl);
    // delete(qr);

    win.load_image("ok", img);
    win.set_image("ok");

    win.pause();
    return 0;
}
