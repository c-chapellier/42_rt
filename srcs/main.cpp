#include "header.hpp"
#include "loadingBar/LoadingBar.hpp"
#include "./../include/nlohmann/json.hpp"
#include <fstream>

// std::list<Object *> polygone()
// {
//     std::list<Object *> objects;
//     Point p0(0, 0, 0);
//     Point p1(80, -20, -60);
//     Point p2(80, 50, -50);
//     Point p3(80, -50, 50);
//     Point p4(80, 50, 50);
//     Point p5(0, 0, -50);
//     // objects.push_back(PolygoneFactory::createPolygone("Cube", p1, 50, 20, 0, 0, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("Cube", p2, 50, 20, 0, 0, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("Cube", p3, 50, 20, 0, 0, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("Cube", p4, 50, 20, 0, 0, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("2N-edron", p1, 3, 50, 40, 0, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("Parallelepiped", p1, 50, 100, 100, 0, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("Diamond", p1, 20, 70, 30, 50, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("MobiusTape", p1, 60, 20, 40, 0, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("Spiral", p1, 60, 20, 40, 4, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("Tower", p5, 40, 20, 8, 6, 0, 0, 0));
//     // objects.push_back(PolygoneFactory::createPolygone("Torus", p1, 60, 10, 100, 100, 0, 0, 0));
//     return objects;
// }

// std::list<Object *> alpha()
// {
//     std::list<Object *> objects;
//     Point p0(0, 0, 0);
//     std::vector<Polygone *> tmp = AlphaFactory::createAlpha("iou", p0, 50, 25, 10);
//     for(int i = 0; i < (int)tmp.size(); ++i) {
//         objects.push_back(tmp[i]);
//     }
//     return objects;
// }

// void perlinNoise(int height, int width)
// {
//     std::vector<std::vector<Vector*>> vectors;
//     vectors.resize(height, std::vector<Vector*>(width));

//     for(int h = 0; h < height; ++h){
//         std::vector<Vector*> tmp;
//         for (int w = 0; w < width; ++w){
//             double x = (double)(rand() % 100) / 100;
//             double y = 1 - pow(x, 2);
//             x = rand() % 2 == 0 ? (x) : (-x);
//             y = rand() % 2 == 0 ? (y) : (-y);
//             tmp.push_back(new Vector(x, y, 0));
//         }
//         vectors.push_back(tmp);
//     }

//     int x = rand() % width - 1;
//     int y = rand() % height - 1;
//     Point p(x, y, 0);
//     Vector v1(x, y, 0, p);
//     Vector v2(x + 1, y, 0, p);
//     Vector v3(x + 1, y + 1, 0, p);
//     Vector v4(x, y + 1, 0, p);
//     double res1 = v1.scalarProduct(vectors[y][x]);
//     double res2 = v2.scalarProduct(vectors[y + 1][x]);
//     double res3 = v3.scalarProduct(vectors[y + 1][x + 1]);
//     double res4 = v4.scalarProduct(vectors[y][x + 1]);
// }

int wrapped_main(int argc, char *argv[])
{
    if (argc < 2)
        throw std::string("Usage: ") + argv[0] + " <config file>";

    Parser parser(argv[1]);
    Config *config = parser.getConfig();
    std::list<Camera *> cameras = parser.getCameras();
    std::list<Object *> objects = parser.getObjects();
    std::list<Light *> lights = parser.getLights();

    // Point p(100, 0, -200);
    // std::list<Object *> objects = ShapeFactory::createShape("DNA", p);

    //std::list<Object *> objects = alpha();


    srand(time(NULL));


    Window win(config->getHeight(), config->getWidth());
    LoadingBar loadingBar(win);

    Image img(config->getHeight(), config->getWidth());

    for (auto const& camera : cameras)
    {
        std::vector< std::vector<Point> > screen = camera->getScreen(config->getHeight(), config->getWidth(), config->getPrecision());

        std::vector< std::vector<Pixel> > pxls;
        pxls.resize(config->getHeight() * config->getPrecision(), std::vector<Pixel>(config->getWidth() * config->getPrecision()));
        for (int i = 0; i < config->getHeight() * config->getPrecision(); ++i)
            for (int j = 0; j < config->getWidth() * config->getPrecision(); ++j)
                pxls[i][j] = Pixel(0, 0, 0, 255, INFINITY);

        std::cout << "init" << std::endl;
        
        int i = 0;
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

                        if (dist < pxls[height][width].get_dist())
                        {
                            double angle = RADIAN(obj->angleWith(&l));
                            Pixel p(
                                obj->getColor() // ((height / 20) + (width / 20)) % 2
                                        ->reduceOf(1 - exp(-dist / 1000))
                                        ->reduceOf(cos(angle))
                                        ->add(config->getAmbientColor()),
                                dist
                            );

                            // for (auto const& light : lights)
                            // {
                            //     if (light.shines(p))
                            //         p.add_light();
                            // }
                            
                            pxls[height][width] = p;
                        }
                    }
                }
            }
            ++i;
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
                        r += pxls[height * config->getPrecision() + i][width * config->getPrecision() + j].get_red();
                        g += pxls[height * config->getPrecision() + i][width * config->getPrecision() + j].get_green();
                        b += pxls[height * config->getPrecision() + i][width * config->getPrecision() + j].get_blue();
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
