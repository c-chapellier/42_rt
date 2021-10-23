#pragma once

#include <fstream>

#include "../header.hpp"

class Engine
{
private:
    Config *config;
    std::list<Camera *> cameras;
    std::list<Object *> objects;
    std::list<Light *> lights;
    std::list<BlackObject *> black_objects;

    Image *img;
    Window *win;
    LoadingBar *loadingBar;

    int precision_height;
    int precision_width;

    const unsigned int nbrOfThreads = std::thread::hardware_concurrency();

    void parse(std::string config_file);
    void init();
    void findObjects(int threadNumber, Camera *camera, std::vector< std::vector<Point> > *screen, std::vector< std::vector<Pixel> > *pixels);
    void applyLight(int threadNumber, std::vector< std::vector<Pixel> > *pixels);
    void applyBlur(std::vector< std::vector<Pixel> > &pixels);
    void apply3D(std::vector< std::vector<Pixel> > &pixels);
    void applyFilter(std::vector< std::vector<Pixel> > &pixels);
    void applyPrecision(std::vector< std::vector<Pixel> > &pixels);

    bool blackObjectsContains(Point *p);

    Color *alphaBlending(Color *c1, Color *c2);
    void getNewPixel(Object *obj, Line &l, Point *p, Camera *camera, Pixel *pixel, int height, int width);
    std::vector< std::vector<Pixel>> getPixels();

public:
    Engine(std::string config_file);
    ~Engine();

    void run();
};