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

    std::cout << "parse" << std::endl;
    this->config = parser.getConfig();
    this->cameras = parser.getCameras();
    this->objects = parser.getObjects();
    this->lights = parser.getLights();
    this->black_objects = parser.getBlackObjects();
}

void Engine::init()
{
    std::cout << "init" << std::endl;
    this->img = new Image(this->config->getHeight(), this->config->getWidth());
    this->win = new Window(this->config->getHeight(), this->config->getWidth());
    this->loadingBar = new LoadingBar(this->win);

    this->precision_height = this->config->getHeight() * this->config->getPrecision();
    this->precision_width = this->config->getWidth() * this->config->getPrecision();
}

void Engine::applyLight(int threadNumber, std::vector< std::vector<Pixel> > *pixels)
{
    Color *light_color = new Color(255, 255, 255, 255);

    for (auto const& light : this->lights)
    {
        for (int height = threadNumber; height < this->precision_height; height += this->nbrOfThreads)
        {
            for (int width = 0; width < this->precision_width; ++width)
            {
                if ((*pixels)[height][width].get_object() != NULL)
                {
                    Line l(*(light->getP()), *((*pixels)[height][width].get_location()));
                    bool is_shined = true;
                    double dist_pxl_light = (*pixels)[height][width].get_location()->distWith(*(light->getP()));

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
                        Color *shined_color = new Color(*((*pixels)[height][width].getColor()));

                        Object *obj = (*pixels)[height][width].get_object();

                        double angle = RADIAN(obj->angleWith(&l));

                        shined_color->add(light_color->reduceOf(cos(angle)));

                        (*pixels)[height][width].setColor(shined_color);        
                    }
                }
            }
        }
        // this->loadingBar += 50 / (this->cameras.size() * this->objects.size());
    }
}

void Engine::findObjects(int threadNumber, Camera *camera, std::vector< std::vector<Point> > *screen, std::vector< std::vector<Pixel> > *pixels)
{
    for (auto const& obj : this->objects)
    {
        for (int height = threadNumber; height < this->precision_height; height += this->nbrOfThreads)
        {
            for (int width = 0; width < this->precision_width; ++width)
            {
                Line l(*(camera->getP()), (*screen)[height][width]);
                Point *p = obj->intersect(&l);
                
                if (p && !blackObjectsContains(p))
                {
                    this->getNewPixel(obj, l, p, camera, &(*pixels)[height][width], height, width);
                }
            }
        }
        // this->loadingBar += 50 / (this->cameras.size() * this->objects.size());
    }
}

void Engine::applyPrecision(std::vector< std::vector<Pixel> > &pixels)
{
    for (int height = 0; height < this->config->getHeight(); ++height)
    {
        for (int width = 0; width < this->config->getWidth(); ++width)
        {
            int r = 0, g = 0, b = 0;
            
            for (int i = 0; i < this->config->getPrecision(); ++i)
            {
                for (int j = 0; j < this->config->getPrecision(); ++j)
                {
                    r += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j].getRed();
                    g += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j].getGreen();
                    b += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j].getBlue();
                }
            }
            Pixel pix(r / pow(this->config->getPrecision(), 2), g / pow(this->config->getPrecision(), 2), b / pow(this->config->getPrecision(), 2), 255);
            this->img->set_pixel(height, width, pix);
        }
    }
}

void Engine::run()
{
    time_t starting_time = time(NULL);

    std::cout << "max_nbr_of_threads = " << this->nbrOfThreads << std::endl;

    this->init();

    for (auto const& camera : this->cameras)
    {
        std::vector< std::vector<Point> > screen = camera->getScreen(*config);
        std::vector< std::vector<Pixel> > pixels = this->getPixels();

        std::vector<std::thread> threads;
        
        std::cout << "findObjects" << std::endl;
        for (unsigned int i = 0; i < this->nbrOfThreads; ++i)
            threads.push_back(std::thread(&Engine::findObjects, this, i, camera, &screen, &pixels));
        
        for (auto &th : threads)
            th.join();

        threads.clear();
    
        std::cout << "applyLight" << std::endl;
        for (unsigned int i = 0; i < this->nbrOfThreads; ++i)
            threads.push_back(std::thread(&Engine::applyLight, this, i, &pixels));
        
        for (auto &th : threads)
            th.join();

        std::cout << "others" << std::endl;
        this->applyFilter(pixels);
        //this->apply3D(pixels);
        this->applyBlur(pixels);
        this->applyPrecision(pixels);

        this->win->load_image(*this->img);
    }

    this->win->set_image();
    std::cout << "loaded in " << (time(NULL) - starting_time) << std::endl;
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

    return new Color((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(o * 255));
}

void Engine::getNewPixel(Object *obj, Line &l, Point *p, Camera *camera, Pixel *pixel, int height, int width)
{
    double dist = p->distWith(*(camera->getP()));
    double angle = RADIAN(obj->angleWith(&l));

    Color *tmp = obj->getColorAt(height, width, config->getHeight(), config->getWidth())
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
    std::vector< std::vector<Pixel>> pixels;
    pixels.resize(this->precision_height, std::vector<Pixel>(this->precision_width));

    for (int h = 0; h < this->precision_height; ++h)
        for (int w = 0; w < this->precision_width; ++w)
            pixels[h][w] = Pixel(0, 0, 0, 100, INFINITY);

    return pixels;
}

void Engine::apply3D(std::vector< std::vector<Pixel> > &pixels)
{
    Color red(255, 0, 0, 100);
    Color cyan(0, 255, 255, 100);

    for (int h = 0; h < this->precision_height; ++h){
        for (int w = 0; w < this->precision_width; ++w){
            if(pixels[h][w].get_object() != NULL)
                pixels[h][w].setColor(alphaBlending(&cyan, pixels[h][w].getColor()));
        }
    }
}

// https://dyclassroom.com/image-processing-project/how-to-convert-a-color-image-into-sepia-image
void Engine::applyFilter(std::vector< std::vector<Pixel> > &pixels)
{
    if (this->config->getFilter() == "None") {
        return ;
    } else if (this->config->getFilter() == "Sepia") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w].get_object() != NULL){
                    double tr = 0.393 * (double)pixels[h][w].getColor()->getR() + 0.769 * (double)pixels[h][w].getColor()->getG() + 0.189 * (double)pixels[h][w].getColor()->getB();
                    double tg = 0.349 * (double)pixels[h][w].getColor()->getR() + 0.686 * (double)pixels[h][w].getColor()->getG() + 0.168 * (double)pixels[h][w].getColor()->getB();
                    double tb = 0.272 * (double)pixels[h][w].getColor()->getR() + 0.534 * (double)pixels[h][w].getColor()->getG() + 0.131 * (double)pixels[h][w].getColor()->getB();
                    pixels[h][w].setColor(new Color((int)tr, (int)tg, (int)tb));
                }
            }
        }
    } else if (this->config->getFilter() == "AverageGrayscale") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w].get_object() != NULL){
                    double t = ((double)pixels[h][w].getColor()->getR() + (double)pixels[h][w].getColor()->getG() + (double)pixels[h][w].getColor()->getB()) / 3.0;
                    pixels[h][w].setColor(new Color((int)t, (int)t, (int)t));
                }
            }
        }
    } else if (this->config->getFilter() == "WeightedGrayscale") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w].get_object() != NULL){
                    double t = 0.299 * (double)pixels[h][w].getColor()->getR() + 0.587 * (double)pixels[h][w].getColor()->getG() + 0.114 * (double)pixels[h][w].getColor()->getB();
                    pixels[h][w].setColor(new Color((int)t, (int)t, (int)t));
                }
            }
        }
    } else if (this->config->getFilter() == "Invert") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w].get_object() != NULL){
                    double tr = 255 - pixels[h][w].getColor()->getR();
                    double tg = 255 - pixels[h][w].getColor()->getG();
                    double tb = 255 - pixels[h][w].getColor()->getB();
                    pixels[h][w].setColor(new Color((int)tr, (int)tg, (int)tb));
                }
            }
        }
    }
}

void Engine::applyBlur(std::vector< std::vector<Pixel> > &pixels)
{
    if(this->config->getBlur() == 0)
        return;
    
    std::vector<std::vector<Color*>> colors; 
    for (int height = 0; height < this->precision_height; ++height)
    {
        std::vector<Color*> tmp;
        for (int width = 0; width < this->precision_width; ++width)
        {
            int r = 0;
            int g = 0;
            int b = 0;
            int s = 0;
            for (int i = height - config->getBlur(); i < height + config->getBlur(); ++i){
                for (int j = width - config->getBlur(); j < width + config->getBlur(); ++j){
                    if(i >=0 && i < config->getHeight() && j >= 0 && j < config->getWidth()) {
                        r += pixels[i][j].getRed();
                        g += pixels[i][j].getGreen();
                        b += pixels[i][j].getBlue();
                        ++s;
                    }
                }
            }
            tmp.push_back(new Color(r / s, g / s, b / s));
        }
        colors.push_back(tmp);
    }
    for (int h = 0; h < this->precision_height; ++h){
        for (int w = 0; w < this->precision_width; ++w){
            pixels[h][w].setColor(colors[h][w]);
        }
    }
}

bool Engine::blackObjectsContains(Point *p)
{
    for (auto const& obj : this->black_objects){
        //std::cout << "blackObjectsContains" << std::endl;
        if(obj->contains(p)){
            //std::cout << "in" << std::endl;
            return true;
        }
    }
    return false;
}