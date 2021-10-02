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
    // make all the points
    std::vector< std::vector<Point> > screen;
    screen.resize(height, std::vector<Point>(width));
    for (int z = 0; z < height; ++z){
        for (int y = 0; y < width; ++y){
            Point p(double(width / 2) / sin(RADIAN(this->angle / 2)), (double)(y - (double)(width / 2)), - z + double(height / 2));
            screen[z][y] = p;
            std::cout << screen[z][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;std::cout << std::endl;

    // calc
    Vector *x_axis = new Vector(1, 0, 0); // X axis
    Vector *z_axis = new Vector(0, 0, 1); // Z axis

    // angle between the camera vector and X axis
    double alpha = this->v->angleWith(x_axis);
    // if right turn angle = one complete turn minus himself (trigonometric circle)
    alpha = this->v->directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
    // angle between the camera vector and Z axis
    double gama = 90 - this->v->angleWith(z_axis);
    // ???
    gama = this->v->directionXZ(z_axis) == CLOCK_WISE ? (360 - gama) : (gama);


    for (int z = 0; z < height; ++z) {
        for (int y = 0; y < width; ++y) {
            std::cout << std::endl << "Point: " << screen[z][y] << std::endl;
            Point *new_point; // res

            // create a new point on Z axis at heigh of the current point
            Point *ooz = new Point(0, 0, - z + double(height / 2));
            // create a vector from the previous point to current point
            Vector *p_ooz = new Vector(*ooz, screen[z][y]);
            // get the distance between the current point and point on Z axis (R of polar coordinates)
            double dist = screen[z][y].distWith(*ooz);
            // get the angle between the previous vector and X axis (α of polar coordinates)
            double beta = p_ooz->angleWith(x_axis);
            // if right turn angle = one complete turn minus himself (trigonometric circle)
            beta = p_ooz->directionXY(x_axis) == CLOCK_WISE ? (360 - beta) : (beta);
            // the final angle is the current angle + X axis rotation
            // ex: (50 120 = > 170) : (50 320 => 370 => 10) : (320 350 => 670 => 310)
            double new_angle = beta + alpha;
            
            
            // new coordinates
            double new_x = cos(RADIAN(new_angle)) * dist;
            double new_y = sin(RADIAN(new_angle)) * dist; // reverse the sin because the repere X Y is invert of trigonometric circle
            double new_z = screen[z][y].getZ();

            std::cout << "dist: " << dist << std::endl;
            std::cout << "alpha: " << alpha << std::endl;
            std::cout << "beta: " << beta << std::endl;
            std::cout << "clock_wise: " << p_ooz->directionXY(x_axis) << std::endl;
            std::cout << "new_angle: " << new_angle << std::endl;
            std::cout << "sin: " << sin(RADIAN(new_angle)) << std::endl;
            std::cout << "cos: " << cos(RADIAN(new_angle)) << std::endl;
            std::cout << "x: " << new_x << " y: " << new_y << " z: " << new_z << std::endl;

            // create a vector from the current point to the new point
            Vector v1(screen[z][y], new_x, new_y, new_z);
            // apply this vector to the current point
            new_point = screen[z][y].applyVector(&v1);

            std::cout << "actual point: " << screen[z][y] << std::endl;
            std::cout << "v1: " << v1 << std::endl;
            std::cout << "new point: " << *new_point << std::endl;

            Point *oyo = new Point(0, y - double(width / 2), 0);
            Vector *p_oyo = new Vector(*oyo, screen[z][y]);
            dist = screen[z][y].distWith(*oyo); // dist
            beta = p_oyo->angleWith(x_axis);
            beta = p_oyo->directionXZ(x_axis) == CLOCK_WISE ? (beta) : (360 - beta);
            new_angle = beta + gama;

            // new coordinates
            new_x = cos(RADIAN(new_angle)) * dist;
            new_y = screen[z][y].getY();
            new_z = sin(RADIAN(new_angle)) * dist;

            std::cout << "dist: " << dist << std::endl;
            std::cout << "gama: " << gama << std::endl;
            std::cout << "beta: " << beta << std::endl;
            std::cout << "clock_wise: " << p_oyo->directionXZ(x_axis) << std::endl;
            std::cout << "new_angle: " << new_angle << std::endl;
            std::cout << "sin: " << sin(RADIAN(new_angle)) << std::endl;
            std::cout << "cos: " << cos(RADIAN(new_angle)) << std::endl;
            std::cout << "x: " << new_x << " y: " << new_y << " z: " << new_z << std::endl;

            Vector v2(screen[z][y], new_x, new_y, new_z);
            new_point = new_point->applyVector(&v2);

            std::cout << "actual point: " << screen[z][y] << std::endl;
            std::cout << "v2: " << v2 << std::endl;
            std::cout << "new point: " << *new_point << std::endl;
            
            screen[z][y].setX(new_point->getX() + this->p->getX());
            screen[z][y].setY(new_point->getY() + this->p->getY());
            screen[z][y].setZ(new_point->getZ() + this->p->getZ());
            //break;
        }
        //break;
    }
    for (int z = 0; z < height; ++z){
        for (int y = 0; y < width; ++y){
            std::cout << screen[z][y] << " ";
        }
        std::cout << std::endl;
    }
}