#include "header.hpp"
#include "loadingBar/LoadingBar.hpp"
#include "./../include/nlohmann/json.hpp"
#include <fstream>

std::list<Object *> polygone()
{
    std::list<Object *> objects;
    Point p0(0, 0, 0);
    Point p1(80, -20, -60);
    Point p2(80, 50, -50);
    Point p3(80, -50, 50);
    Point p4(80, 50, 50);
    Point p5(0, 0, -50);
    // objects.push_back(PolygoneFactory::createPolygone("Cube", p1, 50, 20, 0, 0));
    // objects.push_back(PolygoneFactory::createPolygone("Cube", p2, 50, 20, 0, 0));
    // objects.push_back(PolygoneFactory::createPolygone("Cube", p3, 50, 20, 0, 0));
    // objects.push_back(PolygoneFactory::createPolygone("Cube", p4, 50, 20, 0, 0));
    // objects.push_back(PolygoneFactory::createPolygone("2N-edron", p1, 3, 50, 40, 0));
    // objects.push_back(PolygoneFactory::createPolygone("Parallelepiped", p1, 50, 100, 100, 0));
    // objects.push_back(PolygoneFactory::createPolygone("Diamond", p1, 20, 70, 30, 50));
    // objects.push_back(PolygoneFactory::createPolygone("MobiusTape", p1, 60, 20, 40, 0));
    // objects.push_back(PolygoneFactory::createPolygone("Spiral", p1, 60, 20, 40, 4));
    // objects.push_back(PolygoneFactory::createPolygone("Tower", p5, 40, 20, 8, 6));
    objects.push_back(PolygoneFactory::createPolygone("Torus", p1, 60, 10, 100, 100));
    return objects;
}

int wrapped_main(int argc, char *argv[])
{
    if (argc < 2)
        throw std::string("Usage: ") + argv[0] + " <config file>";

    Parser parser(argv[1]);
    Config *config = parser.getConfig();
    std::list<Camera *> cameras = parser.getCameras();
    std::list<Object *> objects = parser.getObjects();

    srand(time(NULL));


    Window win(config->getHeight(), config->getWidth());
    LoadingBar loadingBar(win);

    Image img(config->getHeight(), config->getWidth());

    for (auto const& camera : cameras)
    {
        std::vector< std::vector<Point> > screen = camera->getScreen(config->getHeight(), config->getWidth());

        for (auto const& obj : objects)
        {
            for (int height = 0; height < (int)screen.size(); ++height)
            {
                for (int width = 0; width < (int)screen[0].size(); ++width)
                {
                    Line l(*(camera->getP()), screen[height][width]);
                    Point *p = obj->intersect(&l);
                    
                    if (p)
                    {
                        double dist = p->distWith(*(camera->getP()));
                        double angle = RADIAN(obj->angleWith(&l));
                        Pixel p(
                            obj->getColor()
                                    ->reduceOf(1 - exp(-dist / 1000))
                                    ->reduceOf(cos(angle))
                                    ->add(config->getAmbientColor())
                        );
                        img.set_pixel(height, width, p);
                    }
                }
            }
        }
        win.load_image(img);
        loadingBar += 100 / cameras.size();
    }

    win.set_image();
    std::cout << "loaded" << std::endl;
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
