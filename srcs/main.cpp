#include "header.hpp"
#include "loadingBar/LoadingBar.hpp"
#include "./../include/nlohmann/json.hpp"
#include <fstream>

// for convenience
using json = nlohmann::json;

std::list<Object *> polygone()
{
    std::list<Object *> objects;
    Point p(70, 0, -50);
    // objects.push_back(PolygoneFactory::createPolygone("Cube", p, 50, 20, 0, 0));
    //objects.push_back(PolygoneFactory::createPolygone("Octohedron", p, 50, 20, 0, 0));
    // objects.push_back(PolygoneFactory::createPolygone("Parallelepiped", p, 50, 100, 100, 0));
    // objects.push_back(PolygoneFactory::createPolygone("Diamond", p, 20, 70, 30, 50));
    objects.push_back(PolygoneFactory::createPolygone("Tape", p, 60, 20, 40, 0));
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

int wrapped_main(int argc, char *argv[])
{
    if (argc < 2)
        throw std::string("Usage: ") + argv[0] + " <config file>";

    srand(time(NULL));

    std::ifstream f(argv[1]);
    json j;
    f >> j;

    Window win(j["width"], j["height"]);
    LoadingBar loadingBar(win);

    Image img(j["width"], j["height"]);

    std::list<Camera *> cameras = parse_cameras(j);

    Color ambient_color(j["ambient"][0], j["ambient"][1], j["ambient"][2], j["ambient"][3]);

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
                        double angle = RADIAN(obj->angleWith(&l));
                        Pixel p(
                            obj->getColor()
                                    ->reduceOf(1 - exp(-dist / 1000))
                                    ->reduceOf(cos(angle))
                                    ->add(&ambient_color)
                        );
                        img.set_pixel(j, i, p);
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

int main(int argc, char *argv[])
{
    int rc;

    try
    {
        rc = wrapped_main(argc, argv); 
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    return rc;
}
