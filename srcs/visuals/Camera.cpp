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
    double gama = this->v->angleWith(z_axis);

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
            Vector *v1_tmp = new Vector(*ooz, screen[z][y]);

            Point *oyo = new Point(0, y - double(width / 2), 0);
            Vector *v2_tmp = new Vector(*oyo, screen[z][y]);

            // polar coordinates for x y axis
            double dist1 = screen[z][y].distWith(*ooz); // dist 
            double alpha1 = v1_tmp->angleWith(x_axis) + alpha; // angle
            double dist2 = screen[z][y].distWith(*oyo); // dist 
            double gama1 = v2_tmp->angleWith(x_axis) + (90 - gama); // angle
            // new coordinates
            double new_x = sin(RADIAN(alpha1)) * dist1;
            double new_y = cos(RADIAN(alpha1)) * dist1;
            double new_z = screen[z][y].getZ();

            Vector v1(screen[z][y], new_x, new_y, new_z);
            new_point = screen[z][y].applyVector(&v1);

            // new coordinates
            new_x = cos(RADIAN(gama1)) * dist2;
            new_y = screen[z][y].getY();
            new_z = sin(RADIAN(gama1)) * dist2;

            Vector v2(screen[z][y], new_x, new_y, new_z);
            new_point = new_point->applyVector(&v2);
            
            screen[z][y].setX(new_point->getX() + this->p->getX());
            screen[z][y].setY(new_point->getY() + this->p->getY());
            screen[z][y].setZ(new_point->getZ() + this->p->getZ());
        }
    }
    for (int z = 0; z < height; ++z){
        for (int y = 0; y < width; ++y){
            std::cout << screen[z][y] << " ";
        }
        std::cout << std::endl;
    }
}