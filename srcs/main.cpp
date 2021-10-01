#include "header.hpp"

int main(void)
{
    srand(time(NULL));

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

    Camera c(0, 0, 0, 1, 0, 0, 90);
    c.getScreen(10, 10);
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
