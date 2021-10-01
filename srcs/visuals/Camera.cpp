#include "Camera.hpp"

Camera::Camera(double px, double py, double pz, double vx, double vy, double vz, double a)
{
    this->p = new Point(px, py, pz);
    this->v = new Vector(vx, vy, vz);
    if (a < 60 || a > 120)
        throw "Bad angle for camera";
    this->angle = a;
}
Camera::Camera(Point p, Vector v, double a)
{
    this->p = new Point(p);
    this->v = new Vector(v);
    this->angle = a;
}
Camera::~Camera()
{
    delete(this->p);
    delete(this->v);
}

// find the distance debtween the camera and the screen : d
// find the center of the screen as we look in the X direction
// find all the points of the screen center on X axis
// apply the rotation for the alpha angle (angle between X axis and camera vector)
// apply the rotation for the gama angle (angle between Z axis and camera vector)
// apply the translation (from the point of the camera)
void Camera::getScreen(int width, int height)
{
    Vector *x_axis = new Vector(1, 0, 0);
    Vector *z_axis = new Vector(0, 0, 1);

    double alpha = this->v->angleWith(x_axis);
    double gama = 90 - this->v->angleWith(z_axis);

    double d = double(width / 2) / sin(RADIAN(this->angle / 2));

    std::vector< std::vector<Point> > screen;
    screen.resize(height, std::vector<Point>(width));

    for (int z = 0; z < height; ++z){
        for (int y = 0; y < width; ++y){
            Point p(d, (double)(y - (double)(width / 2)), - z + double(height / 2));
            screen[z][y] = p;
        }
    }

    for (int z = 0; z < height; ++z){
        for (int y = 0; y < width; ++y){
            std::cout << screen[z][y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;std::cout << std::endl;

    // center all the points for c
    for (int z = 0; z < height; ++z) {
        for (int y = 0; y < width; ++y) {
            Point *new_point;
            Point *ooz = new Point(0, 0, - z + double(height / 2));
            Point *oyo = new Point(0, y - double(width / 2), 0);

            Vector *p_ooz = new Vector(*ooz, screen[z][y]);
            Vector *p_oyo = new Vector(*oyo, screen[z][y]);
            double beta = p_ooz->angleWith(x_axis);
            double new_angle = beta - alpha;
            

            double dist1 = screen[z][y].distWith(*ooz); // dist
            double dist2 = screen[z][y].distWith(*oyo); // dist
            // new coordinates
            double new_x = cos(RADIAN(new_angle)) * dist1;
            double new_y = -sin(RADIAN(new_angle)) * dist1;
            double new_z = screen[z][y].getZ();
            std::cout << "dist1: " << dist1 << std::endl;
            std::cout << "alpha: " << alpha << std::endl;
            std::cout << "beta: " << beta << std::endl;
            std::cout << "new_angle: " << new_angle << std::endl;
            std::cout << "sin: " << sin(RADIAN(new_angle)) << std::endl;
            std::cout << "cos: " << cos(RADIAN(new_angle)) << std::endl;
            std::cout << "x: " << new_x << " y: " << new_y << " z: " << new_z << std::endl;

            Vector v1(screen[z][y], new_x, new_y, new_z);
            new_point = screen[z][y].applyVector(&v1);

            std::cout << "actual point: " << screen[z][y] << std::endl;
            std::cout << "v1: " << v1 << std::endl;
            std::cout << "new point: " << *new_point << std::endl;

            beta = p_oyo->angleWith(x_axis);
            new_angle = beta - gama;
            // new coordinates
            new_x = cos(RADIAN(new_angle)) * dist2;
            new_y = screen[z][y].getY();
            new_z = sin(RADIAN(new_angle)) * dist2;

            std::cout << "dist2: " << dist2 << std::endl;
            std::cout << "gama: " << gama << std::endl;
            std::cout << "beta: " << beta << std::endl;
            std::cout << "new_angle: " << new_angle << std::endl;
            std::cout << "sin: " << sin(RADIAN(new_angle)) << std::endl;
            std::cout << "cos: " << cos(RADIAN(new_angle)) << std::endl;
            std::cout << "x: " << new_x << " y: " << new_y << " z: " << new_z << std::endl;

            Vector v2(screen[z][y], new_x, new_y, new_z);
            new_point = new_point->applyVector(&v2);

            std::cout << "actual point: " << screen[z][y] << std::endl;
            std::cout << "v2: " << v2 << std::endl;
            std::cout << "new point: " << *new_point << std::endl;

            std::cout << *new_point << std::endl;
            
            screen[z][y].setX(new_point->getX() + this->p->getX());
            screen[z][y].setY(new_point->getY() + this->p->getY());
            screen[z][y].setZ(new_point->getZ() + this->p->getZ());
            break;
        }
        break;
    }
    for (int z = 0; z < height; ++z){
        for (int y = 0; y < width; ++y){
            std::cout << screen[z][y] << " ";
        }
        std::cout << std::endl;
    }
}