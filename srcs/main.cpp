#include "header.hpp"
#include "loadingBar/LoadingBar.hpp"
#include "./../include/nlohmann/json.hpp"
#include <fstream>

// for convenience
using json = nlohmann::json;

std::list<Object *> polygone()
{
    // std::vector<Triangle*> triangles;
    // Point *a, *b, *c, *d, *e, *f;
    // a = new Point(0, 0, 50);
    // b = new Point(0, 20, 0);
    // c = new Point(0, -20, 0);
    // d = new Point(-30, 30, 0);
    // e = new Point(-30, -30, 0);
    // f = new Point(-30, 0, 20);
    // triangles.push_back(new Triangle(*a, *b, *c));
    // triangles.push_back(new Triangle(*a, *b, *e));
    // triangles.push_back(new Triangle(*a, *c, *d));
    // triangles.push_back(new Triangle(*a, *e, *b));
    // triangles.push_back(new Triangle(*f, *b, *c));
    // triangles.push_back(new Triangle(*f, *c, *d));
    // triangles.push_back(new Triangle(*f, *d, *e));
    // triangles.push_back(new Triangle(*f, *e, *b));

    std::vector<Triangle*> triangles;
    Point *a, *b, *c, *d, *e, *f;
    a = new Point(0, 0, 50);
    b = new Point(0, 20, 0);
    c = new Point(-20, 0, 0);
    d = new Point(0, -20, 0);
    e = new Point(20, 0, 0);
    f = new Point(0, 0, -50);
    triangles.push_back(new Triangle(*a, *b, *c));
    triangles.push_back(new Triangle(*a, *c, *d));
    triangles.push_back(new Triangle(*a, *d, *e));
    triangles.push_back(new Triangle(*a, *e, *b));
    triangles.push_back(new Triangle(*f, *b, *c));
    triangles.push_back(new Triangle(*f, *c, *d));
    triangles.push_back(new Triangle(*f, *d, *e));
    triangles.push_back(new Triangle(*f, *e, *b));

    std::list<Object *> objects;
    objects.push_back(new Polygone(triangles));
    // objects.push_back(new Polygone(points));
    return objects;
}

std::list<Object *> parse_objects(json &j)
{
    // https://tutorial.math.lamar.edu/classes/calciii/quadricsurfaces.aspx
    
    std::list<Object *> objects;

    for (auto const& obj : j["objects"]) {
        if (obj["name"] == "sphere") {
            // objects.push_back(new Sphere(
            //     obj["center"][0],
            //     obj["center"][1],
            //     obj["center"][2],
            //     obj["radius"],
            // ));
        } else if (obj["name"] == "cylinder") {
            objects.push_back(new Quadratic(1, 0, 1, 0, 0, 0, 0, 0, 0, obj["radius"]));
        } else if (obj["name"] == "cone") {
            objects.push_back(new Quadratic(1, 1, -1, 0, 0, 0, 0, 0, 0, 0));
        } else if (obj["name"] == "hyperboloid") {
            objects.push_back(new Quadratic(1, 1, -1, 0, 0, 0, 0, 0, 0, obj["radius"]));
        } else if (obj["name"] == "quadratic") {
            objects.push_back(new Quadratic(
                obj["coefficients"][0],
                obj["coefficients"][1],
                obj["coefficients"][2],
                obj["coefficients"][3],
                obj["coefficients"][4],
                obj["coefficients"][5],
                obj["coefficients"][6],
                obj["coefficients"][7],
                obj["coefficients"][8],
                obj["coefficients"][9]
            ));
        } else {
            throw "Object is not supported";
        }
    }
    return objects;
}

std::list<Camera *> parse_cameras(json &j)
{    
    std::list<Camera *> cameras;
    
    for (auto const& cam : j["cameras"]) {
        cameras.push_back(new Camera(
            cam["location"][0],
            cam["location"][1],
            cam["location"][2],
            cam["direction"][0],
            cam["direction"][1],
            cam["direction"][2],
            cam["aperture"]
        ));
    }
    return cameras;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    srand(time(NULL));

    // test();

    std::ifstream f(argv[1]);
    json j;
    f >> j;

    Window win(j["width"], j["height"]);
    LoadingBar loadingBar(win);

    Image img(j["width"], j["height"]);

    std::list<Camera *> cameras = parse_cameras(j);

    for (auto const& camera : cameras)
    {
        std::vector< std::vector<Point> > screen = camera->getScreen(j["width"], j["height"]);
        // std::list<Object *> objects = parse_objects(j);
        std::list<Object *> objects = polygone();

        for (auto const& obj : objects)
        {
            for (int i = 0; i < (int)screen.size(); ++i)
            {
                for (int j = 0; j < (int)screen[0].size(); ++j)
                {
                    Line l(*(camera->getP()), screen[i][j]);
                    Point *p = obj->intersect(&l);
                    
                    if (p)
                    {
                        double dist = p->distWith(*(camera->getP()));
                        double pourcentage = (dist / 150);
                        img.set_pixel(i, j, Pixel(obj->getColor()->reduceOf(pourcentage)));
                    }
                }
            }
        }
        win.load_image(img);
        loadingBar += 100 / cameras.size();
    }

    win.set_image();
    win.pause();
    return 0;
}
