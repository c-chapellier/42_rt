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
    std::cout << "config" << std::endl;
    this->config = parser.getConfig();
    std::cout << "cameras" << std::endl;
    this->cameras = parser.getCameras();
    std::cout << "objects" << std::endl;
    this->objects = parser.getObjects();
    std::cout << "lights" << std::endl;
    this->lights = parser.getLights();
    std::cout << "black objects" << std::endl;
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
    std::cout << "end init" << std::endl;
}

void Engine::applyLight(int threadNumber, std::vector< std::vector<Pixel *> > &pixels)
{
    for (auto const& light : this->lights)
    {
        for (int height = threadNumber; height < this->precision_height; height += this->nbrOfThreads)
        {
            for (int width = 0; width < this->precision_width; ++width)
            {
                if (pixels[height][width]->get_object() != NULL)
                {
                    Line l(*light->getP(), pixels[height][width]->get_location());
                    bool is_shined = true;
                    double dist_pxl_light = pixels[height][width]->get_location().distWith(*light->getP());

                    for (auto const& obj : this->objects)
                    {
                        Point *p = obj->intersect(l);
                            
                        if (p != NULL)
                        {
                            double dist_obj_light = p->distWith(*light->getP());

                            if (dist_obj_light + 0.0000000001 < dist_pxl_light)
                            {
                                is_shined = false;
                                break ;
                            }
                        }
                    }

                    if (is_shined)
                    {
                        double angle = RADIAN(pixels[height][width]->get_object()->angleWith(l));
                        
                        pixels[height][width]->getColor().add(light->getColor()->reduceOf(cos(angle)));         
                    }
                }
            }
        }
    }
}

void Engine::findObjects(int threadNumber, Camera *camera, std::vector< std::vector<Point> > &screen, std::vector< std::vector<Pixel *> > &pixels)
{
    for (auto const& obj : this->objects)
    {
        for (int height = threadNumber; height < this->precision_height; height += this->nbrOfThreads)
        {
            for (int width = 0; width < this->precision_width; ++width)
            {
                Line l(*camera->getP(), screen[height][width]);
                Point *p = obj->intersect(l);
                
                if (p != NULL && !this->blackObjectsContains(p))
                {
                    double dist = p->distWith(*camera->getP());
                    double angle = RADIAN(obj->angleWith(l));

                    Color color = obj->getColorAt(height, width, config->getHeight(), config->getWidth());
                    color = color.reduceOf(1 - exp(-dist / 1000));
                    color = color.reduceOf(cos(angle));
                    color = color.add(*this->config->getAmbientColor());

                    Color blended_color;

                    if (dist < pixels[height][width]->get_dist())
                        this->alphaBlending(blended_color, color, pixels[height][width]->getColor());
                    else
                        this->alphaBlending(blended_color, pixels[height][width]->getColor(), color);

                    pixels[height][width]->setColor(blended_color);

                    if (dist < pixels[height][width]->get_dist())
                    {
                        pixels[height][width]->setDist(dist);
                        pixels[height][width]->setLocation(*p);
                        pixels[height][width]->setObject(obj);
                    }
                }
            }
        }
    }
}

void Engine::applyPrecision(std::vector< std::vector<Pixel *> > &pixels)
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
                    r += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j]->getRed();
                    g += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j]->getGreen();
                    b += pixels[height * this->config->getPrecision() + i][width * this->config->getPrecision() + j]->getBlue();
                }
            }
            (*this->img)[height][width] = Pixel(r / pow(this->config->getPrecision(), 2), g / pow(this->config->getPrecision(), 2), b / pow(this->config->getPrecision(), 2), 255);
        }
    }
}

void Engine::threadedFindObjects(Camera *camera, std::vector< std::vector<Point> > &screen, std::vector< std::vector<Pixel *> > &pixels)
{
    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < this->nbrOfThreads; ++i)
        threads.push_back(std::thread(&Engine::findObjects, this, i, camera, std::ref(screen), std::ref(pixels)));
    
    for (auto &th : threads)
        th.join();
}

void Engine::threadedApplyLight(std::vector< std::vector<Pixel *> > &pixels)
{
    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < this->nbrOfThreads; ++i)
        threads.push_back(std::thread(&Engine::applyLight, this, i, std::ref(pixels)));
    
    for (auto &th : threads)
        th.join();
}

void Engine::run()
{
    time_t starting_time = time(NULL);

    std::cout << "max_nbr_of_threads = " << this->nbrOfThreads << std::endl;

    this->init();

    this->loadingBar->add(10);

    for (auto const& camera : this->cameras)
    {
        std::vector< std::vector<Point> > screen = camera->getScreen(*config);
        std::vector< std::vector<Pixel *> > pixels = this->getPixels();
        
        std::cout << "findObjects" << std::endl;
        this->threadedFindObjects(camera, screen, pixels);
        this->loadingBar->add(30 / this->cameras.size());

        std::cout << "applyLight" << std::endl;
        this->threadedApplyLight(pixels);
        this->loadingBar->add(30 / this->cameras.size());

        std::cout << "applyPerlinNoise" << std::endl;
        this->applyPerlinNoise(pixels);

        std::cout << "applyFilter" << std::endl;
        this->applyFilter(pixels);
        // std::cout << "apply3D" << std::endl;
        //this->apply3D(pixels);
        std::cout << "applyBlur" << std::endl;
        this->applyBlur(pixels);
        std::cout << "applyPrecision" << std::endl;
        this->applyPrecision(pixels);

        this->loadingBar->add(30 / this->cameras.size());

        std::cout << "load_image" << std::endl;
        this->win->load_image(this->img);
        std::cout << "end load_image" << std::endl;
    }

    std::cout << "set_image" << std::endl;
    this->win->set_image();
    std::cout << "loaded in " << (time(NULL) - starting_time) << std::endl;
    this->win->pause();
}

// https://fr.wikipedia.org/wiki/Alpha_blending
void Engine::alphaBlending(Color &blended_color, const Color &c1, const Color &c2)
{
    double r, g, b, o;

    o = c1.getP() + (c2.getP() * (1.0 - c1.getP()));
    r = ((c1.getPR() * c1.getP()) + (c2.getPR() * c2.getP() * (1 - c1.getP()))) / o;
    g = ((c1.getPG() * c1.getP()) + (c2.getPG() * c2.getP() * (1 - c1.getP()))) / o;
    b = ((c1.getPB() * c1.getP()) + (c2.getPB() * c2.getP() * (1 - c1.getP()))) / o;

    blended_color.setR((int)(r * 255));
    blended_color.setG((int)(g * 255));
    blended_color.setB((int)(b * 255));
    blended_color.setO((int)(o * 255));
}

std::vector< std::vector<Pixel *>> Engine::getPixels()
{
    std::vector< std::vector<Pixel *> > pixels;
    pixels.resize(this->precision_height, std::vector<Pixel *>(this->precision_width));

    for (int h = 0; h < this->precision_height; ++h)
        for (int w = 0; w < this->precision_width; ++w)
            pixels[h][w] = new Pixel(0, 0, 0, 100, INFINITY);

    return pixels;
}

void Engine::apply3D(std::vector< std::vector<Pixel *> > &pixels)
{
    Color red(255, 0, 0, 100);
    Color cyan(0, 255, 255, 100);

    for (int h = 0; h < this->precision_height; ++h)
    {
        for (int w = 0; w < this->precision_width; ++w)
        {
            if (pixels[h][w]->get_object() != NULL)
            {
                Color color_3d;

                this->alphaBlending(color_3d, cyan, pixels[h][w]->getColor());

                pixels[h][w]->setColor(color_3d);
            }
        }
    }
}

// https://dyclassroom.com/image-processing-project/how-to-convert-a-color-image-into-sepia-image
void Engine::applyFilter(std::vector< std::vector<Pixel *> > &pixels)
{
    if (this->config->getFilter() == "None") {
        return ;
    } else if (this->config->getFilter() == "Sepia") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w]->get_object() != NULL){
                    double tr = 0.393 * (double)pixels[h][w]->getColor().getR() + 0.769 * (double)pixels[h][w]->getColor().getG() + 0.189 * (double)pixels[h][w]->getColor().getB();
                    double tg = 0.349 * (double)pixels[h][w]->getColor().getR() + 0.686 * (double)pixels[h][w]->getColor().getG() + 0.168 * (double)pixels[h][w]->getColor().getB();
                    double tb = 0.272 * (double)pixels[h][w]->getColor().getR() + 0.534 * (double)pixels[h][w]->getColor().getG() + 0.131 * (double)pixels[h][w]->getColor().getB();
                    pixels[h][w]->setColor(Color((int)tr, (int)tg, (int)tb));
                }
            }
        }
    } else if (this->config->getFilter() == "AverageGrayscale") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w]->get_object() != NULL){
                    double t = ((double)pixels[h][w]->getColor().getR() + (double)pixels[h][w]->getColor().getG() + (double)pixels[h][w]->getColor().getB()) / 3.0;
                    pixels[h][w]->setColor(Color((int)t, (int)t, (int)t));
                }
            }
        }
    } else if (this->config->getFilter() == "WeightedGrayscale") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w]->get_object() != NULL){
                    double t = 0.299 * (double)pixels[h][w]->getColor().getR() + 0.587 * (double)pixels[h][w]->getColor().getG() + 0.114 * (double)pixels[h][w]->getColor().getB();
                    pixels[h][w]->setColor(Color((int)t, (int)t, (int)t));
                }
            }
        }
    } else if (this->config->getFilter() == "Invert") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w]->get_object() != NULL){
                    double tr = 255 - pixels[h][w]->getColor().getR();
                    double tg = 255 - pixels[h][w]->getColor().getG();
                    double tb = 255 - pixels[h][w]->getColor().getB();
                    pixels[h][w]->setColor(Color((int)tr, (int)tg, (int)tb));
                }
            }
        }
    }
}

void Engine::applyBlur(std::vector< std::vector<Pixel *> > &pixels)
{
    if (this->config->getBlur() == 0)
        return;
    
    std::vector< std::vector<Color> > colors; 
    for (int height = 0; height < this->precision_height; ++height)
    {
        std::vector<Color> tmp;
        for (int width = 0; width < this->precision_width; ++width)
        {
            int r = 0, g = 0, b = 0, s = 0;

            for (int i = height - config->getBlur(); i < height + config->getBlur(); ++i)
            {
                for (int j = width - config->getBlur(); j < width + config->getBlur(); ++j)
                {
                    if (i >=0 && i < config->getHeight() && j >= 0 && j < config->getWidth())
                    {
                        r += pixels[i][j]->getRed();
                        g += pixels[i][j]->getGreen();
                        b += pixels[i][j]->getBlue();
                        ++s;
                    }
                }
            }
            tmp.push_back(Color(r / s, g / s, b / s));
        }
        colors.push_back(tmp);
    }
    for (int h = 0; h < this->precision_height; ++h){
        for (int w = 0; w < this->precision_width; ++w){
            pixels[h][w]->setColor(colors[h][w]);
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

float Engine::interpolate(float a0, float a1, float w) {
    return ((1.0 - w) * a0) + (w * a1);
}

float Engine::dotGridGradient(int ix, int iy, float x, float y) {
    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx * this->GRADIENT[iy][ix]->getX()) + (dy * this->GRADIENT[iy][ix]->getY());
}

float Engine::perlin(float x, float y) {
    int x0 = floor(x);
    int x1 = x0 + 1;
    int y0 = floor(y);
    int y1 = y0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0, n1, ix0, ix1, value;
    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);
    value = interpolate(ix0, ix1, sy);
    return abs(value);
}

void Engine::initGradient() {
    for(int h = 0; h < this->precision_height + 1; ++h){
        std::vector<Vector*> tmp;
        for (int w = 0; w < this->precision_width + 1; ++w){
            double x = (double)(rand() % 100) / 100.0f;
            double y = 1.0 - pow(x, 2);
            x = rand() % 2 == 0 ? (x) : (-x);
            y = rand() % 2 == 0 ? (y) : (-y);
            tmp.push_back(new Vector(x, y, 0));
        }
        this->GRADIENT.push_back(tmp);
    }
}

void Engine::applyPerlinNoise(std::vector< std::vector<Pixel *> > &pixels) {
    if(config->getPerlinNoise() == false)
        return ;
    std::vector<std::vector<double>> res;

    this->initGradient();
    for(int h = 0; h < this->precision_height; ++h){
        std::vector<double> tmp;
        for (int w = 0; w < this->precision_width; ++w){
            tmp.push_back(this->perlin(w + 0.5, h + 0.5));
        }
        res.push_back(tmp);
    }
    for(int h = 0; h < this->precision_height; ++h){
        std::vector<double> tmp;
        for (int w = 0; w < this->precision_width; ++w){
            if(pixels[h][w]->get_object() != NULL) {
                pixels[h][w]->setColor(pixels[h][w]->getColor().reduceOf((1 - res[h][w]) / 3.0));
            }
        }
        res.push_back(tmp);
    }
}