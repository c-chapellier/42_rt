#include <fstream>

#include "../header.hpp"
#include "../loadingBar/LoadingBar.hpp"
#include "../../include/nlohmann/json.hpp"

class Engine
{
private:
    Config *config;
    std::list<Camera *> cameras;
    std::list<Object *> objects;
    std::list<Light *> lights;

    Image *img;
    Window *win;
    LoadingBar *loadingBar;

    int precision_height;
    int precision_width;

    void parse(std::string config_file);
    void init();
    void apply_light(std::vector< std::vector<Pixel> > &pixels);
    void applyBlur(std::vector< std::vector<Pixel> > &pixels);

    Color *alphaBlending(Color *c1, Color *c2);
    void getNewPixel(Object *obj, Line &l, Point *p, Camera *camera, Pixel *pixel);
    std::vector< std::vector<Pixel>> getPixels();

public:
    Engine(std::string config_file);
    ~Engine();

    void run();
};