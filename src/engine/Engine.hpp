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

    std::vector<std::vector<Vector*>> GRADIENT;
    void initGradient();
    float interpolate(float a0, float a1, float w);
    float dotGridGradient(int ix, int iy, float x, float y);
    float perlin(float x, float y);

    void parse(std::string config_file);
    void init();
    void threadedFindObjects(Camera *camera, std::vector< std::vector<Point> > &screen, std::vector< std::vector<Pixel *> > &pixels);
    void findObjects(int threadNumber, Camera *camera, std::vector< std::vector<Point> > &screen, std::vector< std::vector<Pixel *> > &pixels);
    void threadedApplyLight(std::vector< std::vector<Pixel *> > &pixels);
    void applyLight(int threadNumber, std::vector< std::vector<Pixel *> > &pixels);
    void applyBlur(std::vector< std::vector<Pixel *> > &pixels);
    void apply3D(std::vector< std::vector<Pixel *> > &pixels);
    void applyFilter(std::vector< std::vector<Pixel *> > &pixels);
    void applyPrecision(std::vector< std::vector<Pixel *> > &pixels);
    void applyPerlinNoise(std::vector< std::vector<Pixel *> > &pixels);

    bool blackObjectsContains(Point *p);

    void alphaBlending(Color &blended_color, const Color &c1, const Color &c2);
    void getNewPixel(Object *obj, Line &l, Point *p, Camera *camera, Pixel *pixel, int height, int width);
    std::vector< std::vector<Pixel *> > getPixels();

public:
    Engine(std::string config_file);
    ~Engine();

    void run();
};