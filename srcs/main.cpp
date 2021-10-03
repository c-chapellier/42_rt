#include "header.hpp"

void test()
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

    // Vector *v1 = new Vector(1, 0, 0); // + 0
    // Vector *v2 = new Vector(1, 1, 0); // + +
    // Vector *v3 = new Vector(0, 1, 0); // 0 +
    // Vector *v4 = new Vector(-1, 1, 0); // - +
    // Vector *v5 = new Vector(-1, 0, 0); // - 0
    // Vector *v6 = new Vector(-1, -1, 0); // - -
    // Vector *v7 = new Vector(0, -1, 0); // 0 -
    // Vector *v8 = new Vector(1, -1, 0); // + -

    // std::cout << "angle between v1 and v1 (0): " << v1->angleWith(v1) << " sin: " << sin(RADIAN(v1->angleWith(v1))) << " cos: " << cos(RADIAN(v1->angleWith(v1))) <<  " dir: " << v1->directionXY(v1) << std::endl;
    // std::cout << "angle between v1 and v2 (45): " << v1->angleWith(v2) << " sin: " << sin(RADIAN(v1->angleWith(v2))) << " cos: " << cos(RADIAN(v1->angleWith(v2))) << " dir: " << v1->directionXY(v2) << std::endl;
    // std::cout << "angle between v1 and v3 (90): " << v1->angleWith(v3) << " sin: " << sin(RADIAN(v1->angleWith(v3))) << " cos: " << cos(RADIAN(v1->angleWith(v3))) << " dir: " << v1->directionXY(v3) << std::endl;
    // std::cout << "angle between v1 and v4 (135): " << v1->angleWith(v4) << " sin: " << sin(RADIAN(v1->angleWith(v4))) << " cos: " << cos(RADIAN(v1->angleWith(v4))) << " dir: " << v1->directionXY(v4) << std::endl;
    // std::cout << "angle between v1 and v5 (180): " << v1->angleWith(v5) << " sin: " << sin(RADIAN(v1->angleWith(v5))) << " cos: " << cos(RADIAN(v1->angleWith(v5))) << " dir: " << v1->directionXY(v5) << std::endl;
    // std::cout << "angle between v1 and v6 (225): " << v1->angleWith(v6) << " sin: " << sin(RADIAN(v1->angleWith(v6))) << " cos: " << cos(RADIAN(v1->angleWith(v6))) << " dir: " << v1->directionXY(v6) << std::endl;
    // std::cout << "angle between v1 and v7 (270): " << v1->angleWith(v7) << " sin: " << sin(RADIAN(v1->angleWith(v7))) << " cos: " << cos(RADIAN(v1->angleWith(v7))) << " dir: " << v1->directionXY(v7) << std::endl;
    // std::cout << "angle between v1 and v8 (315): " << v1->angleWith(v8) << " sin: " << sin(RADIAN(v1->angleWith(v8))) << " cos: " << cos(RADIAN(v1->angleWith(v8))) << " dir: " << v1->directionXY(v8) << std::endl;

    // Camera c(0, 0, 0, 1, 1, 1, 90);
    // c.getScreen(10, 10);
}

int main(void)
{
    srand(time(NULL));

    test();

    Point *p;
    Line *ln = new Line(0, -100, 0, 0, -1, 0);

    Object *sp = new Sphere(0, 0, 100, 50);
    p = sp->intersect(ln);
    if(p){
        std::cout << *p << std::endl;
        delete(p);
    } else {
        std::cout << "does not itersect" << std::endl;
    }

    Object *pl = new Plane(0, 5, 0, 0, 1, 0);
    p = pl->intersect(ln);
    std::cout << *p << std::endl;
    if(p){
        std::cout << *p << std::endl;
        delete(p);
    } else {
        std::cout << "does not itersect" << std::endl;
    }

    Object *qr = new Quadratic(1, 1, 1, 0, 0, 0, 0, 0, 0, -25); // circle of R = 5
    p = qr->intersect(ln);
    if(p){
        std::cout << *p << std::endl;
        delete(p);
    } else {
        std::cout << "does not itersect" << std::endl;
    }

    // delete(sp);
    // delete(pl);
    // delete(qr);

    int size = 600;

    std::cout << "window" << std::endl;
    Window win(size, size);
    std::cout << "image" << std::endl;
    Image img(size, size);

    std::cout << "camera" << std::endl;
    Camera c(0, 0, 0, 0, 0, 100, 90);
    std::cout << "screen" << std::endl;
    std::vector< std::vector<Point> > screen = c.getScreen(size, size);

    std::cout << "intersect" << std::endl;
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            //std::cout << i << " " << j << std::endl;
            Line l(*c.getP(), screen[i][j]);
            //std::cout << l << std::endl;
            if(sp->intersect(&l)){
                // std::cout << "intersect" << std::endl;
                // std::cout << *sp->getColor() << std::endl;
                img.set_pixel(i, j, Pixel(sp->getColor()));
            }
        }
    }

    

    win.load_image("ok", img);
    win.set_image("ok");

    win.pause();
    return 0;
}
