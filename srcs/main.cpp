#include "header.hpp"
#include "loadingBar/LoadingBar.hpp"
#include "./../include/nlohmann/json.hpp"
#include <fstream>

// https://fr.wikipedia.org/wiki/Alpha_blending
Color *alphaBlending(Color *c1, Color *c2) {
    double r;
    double g;
    double b;
    double o;

    o = c1->getP() + (c2->getP() * (1.0 - c1->getP()));

    r = ((c1->getPR() * c1->getP()) + (c2->getPR() * c2->getP() * (1 - c1->getP()))) / o;
    g = ((c1->getPG() * c1->getP()) + (c2->getPG() * c2->getP() * (1 - c1->getP()))) / o;
    b = ((c1->getPB() * c1->getP()) + (c2->getPB() * c2->getP() * (1 - c1->getP()))) / o;

    // std::cout << c1->getP() << " " << c2->getP() << " " << (c2->getP() * (1.0 - c1->getP())) << " " << o << std::endl;
    // std::cout << *c1 << std::endl;
    // std::cout << *c2 << std::endl;

    return new Color((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(o * 255));
}

void getNewPixel(Config *config, Object *obj, Line &l, Point *p, Camera *camera, Pixel *pixel)
{
    double dist = p->distWith(*(camera->getP()));
    double angle = RADIAN(obj->angleWith(&l));

    Color *tmp = obj->getColor()
                    ->reduceOf(1 - exp(-dist / 1000))
                    ->reduceOf(cos(angle))
                    ->add(config->getAmbientColor());
    // std::cout << "colors:" << std::endl;
    // std::cout << *obj->getColor() << std::endl;
    Color *new_color = dist < pixel->get_dist() ? alphaBlending(tmp, pixel->getColor()) : alphaBlending(pixel->getColor(), tmp);
    // std::cout << *new_color << std::endl;
    pixel->setColor(new_color);
    if(dist < pixel->get_dist())
        pixel->setDist(dist);
    // delete(tmp);
    // delete(new_color);
}

std::vector< std::vector<Pixel>> getPixels(Config *config)
{
    int height = config->getHeight() * config->getPrecision();
    int width = config->getWidth() * config->getPrecision();
    std::vector< std::vector<Pixel>> pixels;
    pixels.resize(height, std::vector<Pixel>(width));

    for (int h = 0; h < height; ++h)
        for (int w = 0; w < width; ++w)
            pixels[h][w] = Pixel(0, 0, 0, 100, INFINITY);

    return pixels;
}

int wrapped_main(char *argv[])
{
    Parser parser(argv[1]);
    Config *config = parser.getConfig();
    std::list<Camera *> cameras = parser.getCameras();
    std::list<Object *> objects = parser.getObjects();
    std::list<Light *> lights = parser.getLights();

    Image img(config->getHeight(), config->getWidth());
    Window win(config->getHeight(), config->getWidth());
    LoadingBar loadingBar(win);

    int precision_height = config->getHeight() * config->getPrecision();
    int precision_width = config->getWidth() * config->getPrecision();

    for (auto const& camera : cameras)
    {
        std::vector< std::vector<Point> > screen = camera->getScreen(*config);
        std::vector< std::vector<Pixel>> pixels = getPixels(config);

        for (auto const& obj : objects)
        {
            for (int height = 0; height < precision_height; ++height)
            {
                for (int width = 0; width < precision_width; ++width)
                {
                    Line l(*(camera->getP()), screen[height][width]);
                    Point *p = obj->intersect(&l);
                    
                    if (p)
                    {
                        getNewPixel(config, obj, l, p, camera, &pixels[height][width]);
                        // double dist = p->distWith(*(camera->getP()));

                        // if (dist < pixels[height][width].get_dist())
                        // {
                        //     double angle = RADIAN(obj->angleWith(&l));
                        //     Pixel p(
                        //         obj->getColor()
                        //                 ->reduceOf(1 - exp(-dist / 1000))
                        //                 ->reduceOf(cos(angle))
                        //                 ->add(config->getAmbientColor()),
                        //         dist
                        //     );

                        //     // for (auto const& light : lights)
                        //     // {
                        //     //     if (light.shines(p))
                        //     //         p.add_light();
                        //     // }
                            
                        //     pixels[height][width] = p;
                        // }
                    }
                }
            }
            loadingBar += 100 / (cameras.size() * objects.size());
        }

        for (int height = 0; height < config->getHeight(); ++height){
            for (int width = 0; width < config->getWidth(); ++width){
                int r = 0;
                int g = 0;
                int b = 0;
                for(int i = 0; i < config->getPrecision(); ++i){
                    for(int j = 0; j < config->getPrecision(); ++j){
                        r += pixels[height * config->getPrecision() + i][width * config->getPrecision() + j].get_red();
                        g += pixels[height * config->getPrecision() + i][width * config->getPrecision() + j].get_green();
                        b += pixels[height * config->getPrecision() + i][width * config->getPrecision() + j].get_blue();
                    }
                }
                Pixel pix(r / pow(config->getPrecision(), 2), g / pow(config->getPrecision(), 2), b / pow(config->getPrecision(), 2), 255);
                img.set_pixel(height, width, pix);
            }
        }

        win.load_image(img);
        //loadingBar += 100 / cameras.size();
    }

    win.set_image();
    std::cout << "loaded" << std::endl;
    win.pause();
    return 0;
}

int main(int argc, char *argv[])
{
    int rc;

    srand(time(NULL));
    try
    {
        if (argc < 2)
            throw std::string("Usage: ") + argv[0] + " <config file>";
        rc = wrapped_main(argv); 
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