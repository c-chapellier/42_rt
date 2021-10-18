#include "Camera.hpp"

Camera::Camera(double px, double py, double pz, double vx, double vy, double vz, double a)
{
    if(vx == 0 && vy == 0 && vz == 0)
        throw "The camera vector can not be the null vector";
    this->p = new Point(px, py, pz);
    this->v = new Vector(vx, vy, vz);
    if (a < 60 || a > 120)
        throw "Bad angle for camera";
    this->angle = a;
}
Camera::Camera(Point p, Vector v, double a)
{
    if(v.getX() == 0 && v.getY() == 0 && v.getZ() == 0)
        throw "The camera vector can not be the null vector";
    this->p = new Point(p);
    this->v = new Vector(v);
    if (a < 60 || a > 120)
        throw "Bad angle for camera";
    this->angle = a;
}
Camera::~Camera()
{
    delete(this->p);
    delete(this->v);
}

Point *Camera::getP()
{
    return this->p;
}
Vector *Camera::getV()
{
    return this->v;
}

// find the distance debtween the camera and the screen : d
// find the center of the screen as we look in the X direction
// find all the points of the screen center on X axis
// apply the rotation for the alpha angle (angle between X axis and camera vector)
// apply the rotation for the gama angle (angle between Z axis and camera vector)
// apply the translation (from the point of the camera)
std::vector< std::vector<Point> > Camera::getScreen(Config &config)
{
    int height = config.getHeight() * config.getPrecision();
    int width = config.getWidth() * config.getPrecision();
    // make all the points
    std::vector< std::vector<Point> > screen;
    screen.resize(height, std::vector<Point>(width));
    for (int z = 0; z < height; ++z){
        for (int y = 0; y < width; ++y){
            Point p(
                double(width / 2) / sin(RADIAN(this->angle / 2)),
                (double)((double)(width / 2) - y), //  + (80 * sin(RADIAN(z * 3)))
                (double)(height / 2) - z); //  + (80 * sin(RADIAN(y * 3)))
            screen[z][y] = p;
        }
    }

    // vectors
    Vector *x_axis = new Vector(1, 0, 0);
    Vector *projection_on_plane_xy = new Vector(this->v->getX(), this->v->getY(), 0);
    Vector *projection_on_plane_xz = new Vector(this->v->getX(), 0, this->v->getZ());

    //plane
    Plane *xy_plane = new Plane(0, 0, 0, 0, 0, 1);

    // angles
    double alpha = 0, gama = 0;

    if(projection_on_plane_xy->getMagnitude() != 0){
        // angle between the camera vector and X axis
        alpha = projection_on_plane_xy->angleWith(x_axis);
        // if right turn angle = one complete turn minus himself (trigonometric circle)
        alpha = projection_on_plane_xy->directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
    }
    // angle between the camera vector and Z axis
    gama = xy_plane->angleWith(this->v);
    // if right turn angle = one complete turn minus himself (trigonometric circle)

    for (int z = 0; z < height; ++z) {
        for (int y = 0; y < width; ++y) {
            Point *tmp1;
            Point *new_point = new Point(screen[z][y]); // res

            // translation horizontal
            if(projection_on_plane_xy->getMagnitude() != 0 && alpha != 0) {
                new_point = screen[z][y].rotateAroundZ(alpha);
            }

            // translation vertical
            if(projection_on_plane_xz->getMagnitude() != 0 && gama != 0) {
                if(gama < 0)
                    gama = 360 + gama;
                Point *tmp = screen[z][y].rotateAroundY(gama);
                tmp1 = tmp->rotateAroundZ(alpha);

                Vector v2(*new_point, *tmp1);
                new_point = new_point->applyVector(&v2);
            }

            screen[z][y].setX(new_point->getX() + this->p->getX());
            screen[z][y].setY(new_point->getY() + this->p->getY());
            screen[z][y].setZ(new_point->getZ() + this->p->getZ());
        }
    }
    return screen;
}