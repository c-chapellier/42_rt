#include "Engine.hpp"

Engine::Engine(std::string config_file)
{
    this->parse(config_file);
    this->loadingBar = NULL;
}

Engine::~Engine()
{

}

void Engine::parse(std::string config_file)
{
    Parser parser(config_file);

    this->config = parser.getConfig();
    this->cameras = parser.getCameras();
    this->objects = parser.getObjects();
    this->lights = parser.getLights();
}

void Engine::init()
{
    this->img = new Image(this->config->getHeight(), this->config->getWidth());
    this->win = new Window(this->config->getHeight(), this->config->getWidth());
    this->loadingBar = new LoadingBar(*this->win);

    this->precision_height = this->config->getHeight() * this->config->getPrecision();
    this->precision_width = this->config->getWidth() * this->config->getPrecision();
}

void Engine::applyBlur(std::vector< std::vector<Pixel> > &pixels)
{
    if(this->config->getBlur()->getP() == 0)
        return;
    for (int height = 0; height < this->precision_height; ++height)
    {
        for (int width = 0; width < this->precision_width; ++width)
        {
            pixels[height][width].setColor(alphaBlending(this->config->getBlur(), pixels[height][width].getColor()));
        }
    }
}

void Engine::apply_light(std::vector< std::vector<Pixel> > &pixels)
{
    Color *light_color = new Color(255, 255, 255, 255);

    for (auto const& light : this->lights)
    {
        for (int height = 0; height < this->precision_height; ++height)
        {
            for (int width = 0; width < this->precision_width; ++width)
            {
                if (pixels[height][width].get_object() != NULL)
                {
                    Line l(*(light->getP()), *(pixels[height][width].get_location()));
                    bool is_shined = true;
                    double dist_pxl_light = pixels[height][width].get_location()->distWith(*(light->getP()));

                    for (auto const& obj : this->objects)
                    {
                        Point *p = obj->intersect(&l);
                            
                        if (p)
                        {
                            double dist_obj_light = p->distWith(*(light->getP()));

                            if (dist_obj_light + 0.0000000001 < dist_pxl_light)
                            {
                                is_shined = false;
                            }
                        }
                    }

                    if (is_shined)
                    {
                        Color *shined_color = new Color(*(pixels[height][width].getColor()));

                        Object *obj = pixels[height][width].get_object();

                        double angle = RADIAN(obj->angleWith(&l));

                        shined_color->add(light_color->reduceOf(cos(angle)));

                        pixels[height][width].setColor(shined_color);        
                    }
                }
            }
        }
        this->loadingBar += 50 / (this->cameras.size() * this->objects.size());
    }
}

void Engine::run()
{
    this->init();

    for (auto const& camera : this->cameras)
    {
        std::vector< std::vector<Point> > screen = camera->getScreen(*config);
        std::vector< std::vector<Pixel> > pixels = this->getPixels();

        for (auto const& obj : this->objects)
        {
            for (int height = 0; height < this->precision_height; ++height)
            {
                for (int width = 0; width < this->precision_width; ++width)
                {
                    Line l(*(camera->getP()), screen[height][width]);
                    Point *p = obj->intersect(&l);
                    
                    if (p)
                    {
                        this->getNewPixel(obj, l, p, camera, &pixels[height][width]);
                    }
                }
            }
            this->loadingBar += 50 / (this->cameras.size() * this->objects.size());
        }

        this->apply_light(pixels);
        this->applyBlur(pixels);

        for (int height = 0; height < this->config->getHeight(); ++height){
            for (int width = 0; width < this->config->getWidth(); ++width){
                int r = 0;
                int g = 0;
                int b = 0;
                for(int i = 0; i < this->config->getPrecision(); ++i){
                    for(int j = 0; j < this->config->getPrecision(); ++j){
                        r += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j].get_red();
                        g += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j].get_green();
                        b += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j].get_blue();
                    }
                }
                Pixel pix(r / pow(this->config->getPrecision(), 2), g / pow(this->config->getPrecision(), 2), b / pow(this->config->getPrecision(), 2), 255);
                this->img->set_pixel(height, width, pix);
            }
        }

        this->win->load_image(*this->img);
        // this->loadingBar += 100 / cameras.size();
    }

    this->win->set_image();
    std::cout << "loaded" << std::endl;
    this->win->pause();
}

// https://fr.wikipedia.org/wiki/Alpha_blending
Color *Engine::alphaBlending(Color *c1, Color *c2) {
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

void Engine::getNewPixel(Object *obj, Line &l, Point *p, Camera *camera, Pixel *pixel)
{
    double dist = p->distWith(*(camera->getP()));
    double angle = RADIAN(obj->angleWith(&l));

    Color *tmp = obj->getColor()
                    ->reduceOf(1 - exp(-dist / 1000))
                    ->reduceOf(cos(angle))
                    ->add(this->config->getAmbientColor());

    Color *new_color = dist < pixel->get_dist() ? alphaBlending(tmp, pixel->getColor()) : alphaBlending(pixel->getColor(), tmp);
    pixel->setColor(new_color);

    if (dist < pixel->get_dist())
    {
        pixel->setDist(dist);
        pixel->setLocation(new Point(*p));
        pixel->setObject(obj);
    }
}

std::vector< std::vector<Pixel>> Engine::getPixels()
{
    int height = this->config->getHeight() * this->config->getPrecision();
    int width = this->config->getWidth() * this->config->getPrecision();
    std::vector< std::vector<Pixel>> pixels;
    pixels.resize(height, std::vector<Pixel>(width));

    for (int h = 0; h < height; ++h)
        for (int w = 0; w < width; ++w)
            pixels[h][w] = Pixel(0, 0, 0, 100, INFINITY);

    return pixels;
}
