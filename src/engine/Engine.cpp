#include "Engine.hpp"

/* * * * * * * * * * * * * * * * * * * * *

*       CONSTRUCTORS & DESTRUCTOR        *

* * * * * * * * * * * * * * * * * * * * */

Engine::Engine(std::string config_file)
    : current_pixel(0)
{
    std::cout << "init" << std::endl;
    std::cout << "max_nbr_of_threads = " << this->nbrOfThreads << std::endl;

    Parser parser(config_file);

    this->config = parser.getConfig();
    this->cameras = parser.getCameras();
    this->objects = parser.getObjects();
    this->lights = parser.getLights();
    this->black_objects = parser.getBlackObjects();

    this->img = new Image(this->config.getHeight(), this->config.getWidth());
    this->win = new Window(this->config.getHeight(), this->config.getWidth());
    this->loadingBar = new LoadingBar(this->win);

    this->precision_height = this->config.getHeight() * this->config.getPrecision();
    this->precision_width = this->config.getWidth() * this->config.getPrecision();

    std::cout << "end init" << std::endl;
}

Engine::~Engine()
{
    for (auto camera: this->cameras)
        delete camera;
    for (auto object: this->objects)
        delete object;
    for (auto light: this->lights)
        delete light;
    for (auto black_object: this->black_objects)
        delete black_object;

    delete this->img;
    delete this->win;
    delete this->loadingBar;
}

/* * * * * * * * * * * * * * * * * * * * *

*             ENGINE ROUTINE             *

* * * * * * * * * * * * * * * * * * * * */

void Engine::runVideo()
{
    std::cout << "run Video" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
  
    //this->loadingBar->add(10);

    for (auto const& camera : this->cameras)
    {
        double dist = abs(camera->getP().getX());
        int max = 360;
        for (int i = 0; i < max; ++i) {
            
            this->current_pixel = 0;
            double angle = i * (360.0 / (double)max);
            std::cout << angle << std::endl;
            double x = dist * cos(RADIAN(angle));
            double y = dist * sin(RADIAN(angle));
            camera->setX(x);
            camera->setY(y);
            camera->setV(-x, -y, 0);
            std::cout << camera->getP().getX() << " " << camera->getP().getY() << std::endl;
            std::vector< std::vector<Point> > screen = camera->getScreen();
            camera->update(config);
            std::vector< std::vector<Pixel> > pixels;
            pixels.resize(this->precision_height, std::vector<Pixel>(this->precision_width, Pixel(0, 0, 0, 0, INFINITY)));

            this->threadedFindObjects(*camera, screen, pixels);
            this->applyPerlinNoise(pixels);
            this->applyFilter(pixels);
            this->applyBlur(pixels);

            // std::cout << "apply3D" << std::endl;
            //this->apply3D(pixels);

            this->applyPrecision(pixels);

            //this->loadingBar->add(30 / this->cameras.size());

            this->win->load_image(this->img);
        }
        break;
    }

    std::cout << "set_image" << std::endl;
    this->win->set_image();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Loaded: " << duration.count() << " milliseconds" << std::endl;

    this->win->startVideo();
}

void Engine::run()
{
    std::cout << "run" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
  
    //this->loadingBar->add(10);

    for (auto const& camera : this->cameras)
    {
        camera->update(config);
        this->current_pixel = 0;
        std::vector< std::vector<Point> > screen = camera->getScreen();
        
        std::vector< std::vector<Pixel> > pixels;
        pixels.resize(this->precision_height, std::vector<Pixel>(this->precision_width, Pixel(0, 0, 0, 0, INFINITY)));

        std::cout << "findObjects" << std::endl;
        this->threadedFindObjects(*camera, screen, pixels);
        
        std::cout << "applyPerlinNoise" << std::endl;
        this->applyPerlinNoise(pixels);

        std::cout << "applyFilter" << std::endl;
        this->applyFilter(pixels);

        std::cout << "applyBlur" << std::endl;
        this->applyBlur(pixels);

        // std::cout << "apply3D" << std::endl;
        //this->apply3D(pixels);

        std::cout << "applyPrecision" << std::endl;
        this->applyPrecision(pixels);

        //this->loadingBar->add(30 / this->cameras.size());

        std::cout << "load_image" << std::endl;
        this->win->load_image(this->img);
        std::cout << "end load_image" << std::endl;
    }

    std::cout << "set_image" << std::endl;
    this->win->set_image();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Loaded: " << duration.count() << " milliseconds" << std::endl;

    this->win->pause();
}

void Engine::threadedFindObjects(const Camera &camera, std::vector< std::vector<Point> > &screen, std::vector< std::vector<Pixel> > &pixels)
{
    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < this->nbrOfThreads; ++i)
        threads.push_back(std::thread(&Engine::findObjects, this, camera.getP(), std::ref(screen), std::ref(pixels)));
    
    // std::cout << "manageLoadingBar" << std::endl;
    // this->manageLoadingBar();
    // std::cout << "end manageLoadingBar" << std::endl;

    for (auto &th : threads)
        th.join();

}

void Engine::findObjects(const Point &cam, std::vector< std::vector<Point> > &screen, std::vector< std::vector<Pixel> > &pixels)
{
    int height, width;

    while (getNextPixel(height, width))
    {
        if (height >= this->precision_height || width >= this->precision_width)
            continue;
        Line ray(cam, screen[height][width]);
        std::vector<Intersection> intersections = getIntersections(ray);

        intersections = sortIntersections(intersections, intersections.size());
        drawPixel(intersections, pixels[height][width], height, width, ray);
    }
}

std::vector<Intersection> Engine::getIntersections(const Line &ray) const
{
    std::vector<Intersection> intersections;

    for (auto const& obj : this->objects)
    {
        std::vector<Intersection> tmp = obj->intersect(ray);
        for (unsigned long i = 0; i < tmp.size(); ++i) {
            if(!blackObjectsContains(tmp[i].getP()))
                intersections.push_back(tmp[i]);
        }
    }
    return intersections;
}

// bubble sort : average O(n²)
std::vector<Intersection> Engine::sortIntersections(std::vector<Intersection> intersections, int size)
{
    for (int i = 0; i < size - 1; ++i) { 
        bool swapped = false;
        for (int j = 0; j < size - i - 1; ++j) {
            if (intersections[j].getDist() > intersections[j+1].getDist()) {
                Intersection tmp = intersections[j];
                intersections[j] = intersections[j + 1];
                intersections[j + 1] = tmp;
                swapped = true;
            }
        }
        if(!swapped)
            break;
    }
    return intersections;
}

void Engine::drawPixel(std::vector<Intersection> intersections, Pixel &pixel, int height, int width, Line &ray)
{
    Color c = pixel.getColor();
    for (unsigned long i = 0; i < intersections.size(); ++i) {
        Color tmp = getColor(intersections[i], height, width, ray, 1);
        c = alphaBlending(c, tmp);
        if (c.getO() == 255)
            break;
    }
    pixel.setColor(c);
}

Color Engine::getColor(Intersection &inter, int height, int width, Line &ray, int index)
{
    Color c;
    if (inter.getObj()->getReflexion() != 0) {
        if (index >= this->config.getMaxReflection())
            c = inter.getObj()->getColorAt(height, width, this->precision_height, this->precision_width, inter.getP());
        else {
            // find the new vector
            Line reflected_ray = inter.getObj()->getReflectedRayAt(inter, ray);
            // find all intersections
            std::vector<Intersection> new_intersections = getIntersections(reflected_ray);
            // sort all intersections
            new_intersections = sortIntersections(new_intersections, new_intersections.size());
            // get color
            for (unsigned long i = 0; i < new_intersections.size(); ++i) {
                Color tmp = getColor(new_intersections[i], height, width, reflected_ray, index + 1);
                c = alphaBlending(c, tmp);
                if (c.getO() == 255)
                    break;
            }
            if(new_intersections.size() != 0)
                c = getReflectedColor(
                    inter.getObj()->getColorAt(height, width, this->precision_height, this->precision_width, inter.getP()), 
                    c, 
                    (double)inter.getObj()->getReflexion() / 100.0);
            if(new_intersections.size() == 0)
                c = inter.getObj()->getColorAt(height, width, this->precision_height, this->precision_width, inter.getP());
        } 
    } else {
        c = inter.getObj()->getColorAt(height, width, this->precision_height, this->precision_width, inter.getP());
    }
    // apply lights
    applyLights(inter, c);
    double angle = RADIAN(inter.getObj()->angleWithAt(ray, inter));
    c = c.add(this->config.getAmbientColor()).reduceOf(cos(angle) / 1.1);
    return c;
}

Color Engine::getReflectedColor(const Color &c1, const Color &c2, double factor) const
{
    return Color(
        c1.getR() + (int)((double)((double)c2.getR() - (double)c1.getR()) * factor),
        c1.getG() + (int)((double)((double)c2.getG() - (double)c1.getG()) * factor),
        c1.getB() + (int)((double)((double)c2.getB() - (double)c1.getB()) * factor),
        c1.getO()
    );
}

void Engine::applyLights(Intersection &inter, Color &color)
{
    for (auto const& light : this->lights)
    {
        Line ray(light->getP(), inter.getP());
        double dist = inter.getP().distWith(light->getP());

        std::vector<Intersection> intersections;
        for (auto const& obj : this->objects)
        {
            std::vector<Intersection> tmp = obj->intersect(ray);
            for(unsigned long k = 0; k < tmp.size(); ++k) {
                if(!blackObjectsContains(tmp[k].getP()) && tmp[k].getDist() < dist)
                    intersections.push_back(tmp[k]);
            }
        }

        double dist_min = INFINITY;
        //double opacity = 0;

        for (unsigned int i = 0; i < intersections.size(); ++i) {
            if (intersections[i].getDist() < dist_min) {
                dist_min = intersections[i].getDist();
                break;
            }
        }

        if (dist_min != INFINITY)
        {
            double obj_light_angle = RADIAN(inter.getObj()->angleWithAt(ray, inter));
                                
            color = color.add(light->getColor().reduceOf(cos(obj_light_angle) / 1.1));
        }
    }
}

bool Engine::getNextPixel(int &height, int &width)
{
    if (this->current_pixel >= this->precision_height * this->precision_width)
        return false;

    this->get_pixel_mtx.lock();

    height = this->current_pixel / this->precision_width;
    width = this->current_pixel % this->precision_width;
    ++this->current_pixel;

    this->get_pixel_mtx.unlock();

    return true;
}

bool Engine::blackObjectsContains(const Point &p) const
{
    for (auto const& obj : this->black_objects)
        if (obj->contains(p))
            return true;
    return false;
}

void Engine::manageLoadingBar()
{
    int a, b = 0;
    int total_pixels = this->precision_height * this->precision_width;

    int sleeping_time = 500;

    do
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleeping_time));

        a = (60. * ((double)this->current_pixel / total_pixels)) - b;

        auto start = std::chrono::high_resolution_clock::now();
        this->loadingBar->add(a / this->cameras.size());
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;
  
        b += a;
        sleeping_time += sleeping_time < 3000 ? 500 : 0;
    }
    while (this->current_pixel < total_pixels);

    a = (60. * ((double)this->current_pixel / total_pixels)) - b;
    this->loadingBar->add(a / this->cameras.size());
    b += a;
}

/* * * * * * * * * * * * * * * * * * * * *

*              END FILTERS               *

* * * * * * * * * * * * * * * * * * * * */

// https://dyclassroom.com/image-processing-project/how-to-convert-a-color-image-into-sepia-image
void Engine::applyFilter(std::vector< std::vector<Pixel> > &pixels)
{
    if (this->config.getFilter() == "None") {
        return ;
    } else if (this->config.getFilter() == "Sepia") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w].getObject() != NULL){
                    double tr = 0.393 * (double)pixels[h][w].getColor().getR() + 0.769 * (double)pixels[h][w].getColor().getG() + 0.189 * (double)pixels[h][w].getColor().getB();
                    double tg = 0.349 * (double)pixels[h][w].getColor().getR() + 0.686 * (double)pixels[h][w].getColor().getG() + 0.168 * (double)pixels[h][w].getColor().getB();
                    double tb = 0.272 * (double)pixels[h][w].getColor().getR() + 0.534 * (double)pixels[h][w].getColor().getG() + 0.131 * (double)pixels[h][w].getColor().getB();
                    pixels[h][w].setColor(Color((int)tr, (int)tg, (int)tb));
                }
            }
        }
    } else if (this->config.getFilter() == "AverageGrayscale") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w].getObject() != NULL){
                    double t = ((double)pixels[h][w].getColor().getR() + (double)pixels[h][w].getColor().getG() + (double)pixels[h][w].getColor().getB()) / 3.0;
                    pixels[h][w].setColor(Color((int)t, (int)t, (int)t));
                }
            }
        }
    } else if (this->config.getFilter() == "WeightedGrayscale") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w].getObject() != NULL){
                    double t = 0.299 * (double)pixels[h][w].getColor().getR() + 0.587 * (double)pixels[h][w].getColor().getG() + 0.114 * (double)pixels[h][w].getColor().getB();
                    pixels[h][w].setColor(Color((int)t, (int)t, (int)t));
                }
            }
        }
    } else if (this->config.getFilter() == "Invert") {
        for (int h = 0; h < this->precision_height; ++h){
            for (int w = 0; w < this->precision_width; ++w){
                if(pixels[h][w].getObject() != NULL){
                    double tr = 255 - pixels[h][w].getColor().getR();
                    double tg = 255 - pixels[h][w].getColor().getG();
                    double tb = 255 - pixels[h][w].getColor().getB();
                    pixels[h][w].setColor(Color((int)tr, (int)tg, (int)tb));
                }
            }
        }
    }
}

void Engine::applyBlur(std::vector< std::vector<Pixel> > &pixels)
{
    if (this->config.getBlur() == 0)
        return;
    
    std::vector< std::vector<Color> > colors; 
    for (int height = 0; height < this->precision_height; ++height)
    {
        std::vector<Color> tmp;
        for (int width = 0; width < this->precision_width; ++width)
        {
            int r = 0, g = 0, b = 0, s = 0;

            for (int i = height - this->config.getBlur(); i < height + this->config.getBlur(); ++i)
            {
                for (int j = width - this->config.getBlur(); j < width + this->config.getBlur(); ++j)
                {
                    if (i >=0 && i < this->config.getHeight() && j >= 0 && j < this->config.getWidth())
                    {
                        r += pixels[i][j].getRed();
                        g += pixels[i][j].getGreen();
                        b += pixels[i][j].getBlue();
                        ++s;
                    }
                }
            }
            tmp.push_back(Color(r / s, g / s, b / s));
        }
        colors.push_back(tmp);
    }
    for (int h = 0; h < this->precision_height; ++h) {
        for (int w = 0; w < this->precision_width; ++w) {
            pixels[h][w].setColor(colors[h][w]);
        }
    }
}

void Engine::apply3D(std::vector< std::vector<Pixel> > &pixels)
{
    Color red(255, 0, 0, 100);
    Color cyan(0, 255, 255, 100);

    for (int h = 0; h < this->precision_height; ++h)
        for (int w = 0; w < this->precision_width; ++w)
            if (pixels[h][w].getObject() != NULL)
                pixels[h][w].setColor(this->alphaBlending(cyan, pixels[h][w].getColor()));
}

void Engine::applyPrecision(std::vector< std::vector<Pixel> > &pixels)
{
    for (int height = 0; height < this->config.getHeight(); ++height)
    {
        for (int width = 0; width < this->config.getWidth(); ++width)
        {
            int r = 0, g = 0, b = 0;
            
            for (int i = 0; i < this->config.getPrecision(); ++i)
            {
                for (int j = 0; j < this->config.getPrecision(); ++j)
                {
                    r += pixels[height * this->config.getPrecision() + i][width * this->config.getPrecision() + j].getRed();
                    g += pixels[height * this->config.getPrecision() + i][width * this->config.getPrecision() + j].getGreen();
                    b += pixels[height * this->config.getPrecision() + i][width * this->config.getPrecision() + j].getBlue();
                }
            }
            (*this->img)[height][width] = Pixel(r / pow(this->config.getPrecision(), 2), g / pow(this->config.getPrecision(), 2), b / pow(this->config.getPrecision(), 2), 255);
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * *

*             COLOR BLENDING             *

* * * * * * * * * * * * * * * * * * * * */

// https://fr.wikipedia.org/wiki/Alpha_blending
Color Engine::alphaBlending(const Color &c1, const Color &c2)
{
    double r, g, b, o;

    o = c1.getP() + (c2.getP() * (1.0 - c1.getP()));
    r = ((c1.getPR() * c1.getP()) + (c2.getPR() * c2.getP() * (1 - c1.getP()))) / o;
    g = ((c1.getPG() * c1.getP()) + (c2.getPG() * c2.getP() * (1 - c1.getP()))) / o;
    b = ((c1.getPB() * c1.getP()) + (c2.getPB() * c2.getP() * (1 - c1.getP()))) / o;

    return Color((int)(r * 255), (int)(g * 255), (int)(b * 255), (int)(o * 255));
}

/* * * * * * * * * * * * * * * * * * * * *

*             PERLIN NOISE               *

* * * * * * * * * * * * * * * * * * * * */

float Engine::interpolate(float a0, float a1, float w)
{
    return ((1.0 - w) * a0) + (w * a1);
}

float Engine::dotGridGradient(int ix, int iy, float x, float y)
{
    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx * this->GRADIENT[iy][ix].getX()) + (dy * this->GRADIENT[iy][ix].getY());
}

float Engine::perlin(float x, float y)
{
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

void Engine::initGradient()
{
    for (int h = 0; h < this->precision_height + 1; ++h)
    {
        std::vector<Vector> tmp;
        for (int w = 0; w < this->precision_width + 1; ++w)
        {
            double x = (double)(rand() % 100) / 100.0f;
            double y = 1.0 - pow(x, 2);
            x = rand() % 2 == 0 ? (x) : (-x);
            y = rand() % 2 == 0 ? (y) : (-y);
            tmp.push_back(Vector(x, y, 0));
        }
        this->GRADIENT.push_back(tmp);
    }
}

void Engine::applyPerlinNoise(std::vector< std::vector<Pixel> > &pixels)
{
    if (this->config.getPerlinNoise() == false)
        return ;

    std::vector<std::vector<double>> res;

    this->initGradient();
    for(int h = 0; h < this->precision_height; ++h)
    {
        std::vector<double> tmp;
        for (int w = 0; w < this->precision_width; ++w)
            tmp.push_back(this->perlin(w + 0.5, h + 0.5));
        res.push_back(tmp);
    }
    
    for (int h = 0; h < this->precision_height; ++h)
    {
        std::vector<double> tmp;

        for (int w = 0; w < this->precision_width; ++w)
            if (pixels[h][w].getObject() != NULL)
                pixels[h][w].setColor(pixels[h][w].getColor().reduceOf((1 - res[h][w]) / 3.0));

        res.push_back(tmp);
    }
}