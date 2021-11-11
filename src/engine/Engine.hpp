#pragma once

#include "../header.hpp"

class Engine
{
    private:
        Config config;
        std::list<Camera *> cameras;
        std::list<Object *> objects;
        std::list<Light *> lights;
        std::list<BlackObject *> black_objects;

        Image *img;
        Window *win;
        LoadingBar *loadingBar;

        int precision_height;
        int precision_width;

        int current_pixel;
        std::mutex get_pixel_mtx;

        int maxReflexion = 2;

        // const unsigned int nbrOfThreads = 1;
        const unsigned int nbrOfThreads = std::thread::hardware_concurrency();

        std::vector< std::vector<Vector> > GRADIENT;

        void threadedFindObjects(const Camera &camera, std::vector< std::vector<Point> > &screen, std::vector< std::vector<Pixel> > &pixels);
        bool getNextPixel(int &height, int &width);
        void findObjects(const Camera &camera, std::vector< std::vector<Point> > &screen, std::vector< std::vector<Pixel> > &pixels);
        void applyPerlinNoise(std::vector< std::vector<Pixel> > &pixels);
        void applyFilter(std::vector< std::vector<Pixel> > &pixels);
        void apply3D(std::vector< std::vector<Pixel> > &pixels);
        void applyBlur(std::vector< std::vector<Pixel> > &pixels);
        void applyPrecision(std::vector< std::vector<Pixel> > &pixels);

        static Color alphaBlending(const Color &c1, const Color &c2);
        bool blackObjectsContains(const Point &p) const;
        void initGradient();
        float interpolate(float a0, float a1, float w);
        float dotGridGradient(int ix, int iy, float x, float y);
        float perlin(float x, float y);

        void manageLoadingBar();

        std::vector<Intersection> getIntersections(Line ray);
        std::vector<Intersection> sortIntersections(std::vector<Intersection> intersections, int size);
        void drawPixel(std::vector<Intersection> intersections, Pixel &pixel, int height, int width, Line &ray);
        Color getColor(Intersection &inter, int height, int width, Line &ray, int index);
        void applyLights(Intersection &inter, Color &color);

    public:
        Engine(std::string config_file);
        ~Engine();

        void run();
};