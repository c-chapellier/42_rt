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
    // objects.push_back(PolygoneFactory::createPolygone("Torus", p1, 60, 10, 100, 100));
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

    // Point p(100, 0, -200);
    // std::list<Object *> objects = ShapeFactory::createShape("DNA", p);

    srand(time(NULL));


    Window win(config->getHeight(), config->getWidth());
    LoadingBar loadingBar(win);

    Image img(config->getHeight(), config->getWidth());

    for (auto const& camera : cameras)
    {
        std::vector< std::vector<Point> > screen = camera->getScreen(config->getHeight(), config->getWidth(), config->getPrecision());
        std::vector< std::vector<Pixel> > pxl;
        pxl.resize(config->getHeight() * config->getPrecision(), std::vector<Pixel>(config->getWidth() * config->getPrecision()));
        for (int i = 0; i < config->getHeight() * config->getPrecision(); ++i)
            for (int j = 0; j < config->getWidth() * config->getPrecision(); ++j)
                pxl[i][j] = Pixel(0, 0, 0, 255);
        std::cout << "init" << std::endl;
        for (auto const& obj : objects)
        {
            for (int height = 0; height < config->getHeight() * config->getPrecision(); ++height)
            {
                for (int width = 0; width < config->getWidth() * config->getPrecision(); ++width)
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
                        //img.set_pixel(height, width, p);
                        pxl[height][width] = p;
                    }
                }
            }
        }
        std::cout << "middle point reached" << std::endl;
        for (int height = 0; height < config->getHeight(); ++height){
            for (int width = 0; width < config->getWidth(); ++width){
                int r = 0;
                int g = 0;
                int b = 0;
                for(int i = 0; i < config->getPrecision(); ++i){
                    for(int j = 0; j < config->getPrecision(); ++j){
                        //std::cout << i << j
                        r += pxl[height * config->getPrecision() + i][width * config->getPrecision() + j].get_red();
                        g += pxl[height * config->getPrecision() + i][width * config->getPrecision() + j].get_green();
                        b += pxl[height * config->getPrecision() + i][width * config->getPrecision() + j].get_blue();
                    }
                }
                Pixel pix(r / pow(config->getPrecision(), 2), g / pow(config->getPrecision(), 2), b / pow(config->getPrecision(), 2), 255);
                img.set_pixel(height, width, pix);
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
    catch (const std::string& e)
    {
        std::cerr << e << '\n';
    }
    catch (const char *e)
    {
        std::cerr << e << '\n';
    }
    // catch (...)
    // {
    //     std::cerr << "catch something else" << '\n';
    // }
    return rc;
}
