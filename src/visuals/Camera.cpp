#include "Camera.hpp"

Camera::Camera(double cx, double cy, double cz, double dx, double dy, double dz, double ux, double uy, double uz, double a)
    : coordinates(cx, cy, cz), direction(dx, dy, dz), up(ux, uy, uz), angle(a), U(1, 1, 1), V(1, 1, 1), screenCenter(0, 0, 0), height(0), width(0)
{
    if (dx == 0 && dy == 0 && dz == 0)
        throw "The camera vector can not be the null vector";
    if (ux == 0 && uy == 0 && uz == 0)
        throw "The camera vector can not be the null vector";
    if (a < 60 || a > 120)
        throw "Bad angle for camera";
}

Camera::~Camera()
{
}

Point Camera::getP() const
{
    return this->coordinates;
}
Vector Camera::getV() const
{
    return this->direction;
}

void Camera::setX(double x)
{
    this->coordinates.setX(x);
}
void Camera::setY(double y)
{
    this->coordinates.setY(y);
}
void Camera::setZ(double z)
{
    this->coordinates.setZ(z);
}
void Camera::setV(double x, double y, double z)
{
    this->direction.setX(x);
    this->direction.setY(y);
    this->direction.setZ(z);
}

void Camera::update(const Config &config)
{
    this->direction.normalize();
    this->U = Vector::crossProduct(this->up, this->direction);
    this->U.normalize();
    this->V = Vector::crossProduct(this->U, this->direction);
    this->V.normalize();

    this->height = config.getHeight() * config.getPrecision();
    this->width = config.getWidth() * config.getPrecision();

    this->U = this->U * this->width;
    this->V = this->V * this->height;
    double L = width / tan(RADIAN(angle / 2));
    this->screenCenter = this->coordinates + (this->direction * L);
}

Point Camera::getPoint(double h, double w) const
{
    Point tmp = this->screenCenter + (this->U * w);
    Point res = tmp + (this->V * h);
    return res;
}

std::vector< std::vector<Point> > Camera::getScreen() const
{
    // make all the points
    std::vector< std::vector<Point> > screen;
    screen.resize(height, std::vector<Point>(width));

    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            screen[h][w] = getPoint((h - (height / 2)) / (double)height, (w - (width / 2)) / (double)width);
        }
    }
    return screen;
}

// find the distance debtween the camera and the screen : d
// find the center of the screen as we look in the X direction
// find all the points of the screen center on X axis
// apply the rotation for the alpha angle (angle between X axis and camera vector)
// apply the rotation for the gama angle (angle between Z axis and camera vector)
// apply the translation (from the point of the camera)
// std::vector< std::vector<Point> > Camera::getScreen(const Config &config) const
// {
//     int height = config.getHeight() * config.getPrecision();
//     int width = config.getWidth() * config.getPrecision();

//     // make all the points
//     std::vector< std::vector<Point> > screen;
//     screen.resize(height, std::vector<Point>(width));

//     for (int z = 0; z < height; ++z)
//     {
//         for (int y = 0; y < width; ++y)
//         {
//             screen[z][y] = Point(
//                 (double)width / (2 * sin(RADIAN(this->angle / 2))),
//                 ((double)width / 2) - y,    //  + (80 * sin(RADIAN(z * 3)))
//                 ((double)height / 2) - z    //  + (80 * sin(RADIAN(y * 3)))
//             );
//         }
//     }

//     // vectors
//     Vector x_axis(1, 0, 0);
//     Vector projection_on_plane_xy(this->v.getX(), this->v.getY(), 0);
//     Vector projection_on_plane_xz(this->v.getX(), 0, this->v.getZ());

//     //plane
//     Plane xy_plane(0, 0, 0, 0, 0, 1);

//     // angles
//     double alpha = 0, gama = 0;

//     if (projection_on_plane_xy.getMagnitude() != 0)
//     {
//         // angle between the camera vector and X axis
//         alpha = projection_on_plane_xy.angleWith(x_axis);
//         // if right turn angle = one complete turn minus himself (trigonometric circle)
//         alpha = projection_on_plane_xy.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
//     }

//     // angle between the camera vector and Z axis
//     gama = xy_plane.angleWith(this->v);
//     // if right turn angle = one complete turn minus himself (trigonometric circle)

//     for (int z = 0; z < height; ++z)
//     {
//         for (int y = 0; y < width; ++y)
//         {
//             Point new_point(screen[z][y]); // res

//             // translation horizontal
//             if (projection_on_plane_xy.getMagnitude() != 0 && alpha != 0)
//                 new_point = screen[z][y].rotateAroundZ(alpha);

//             // translation vertical
//             if (projection_on_plane_xz.getMagnitude() != 0 && gama != 0)
//             {
//                 if (gama < 0)
//                     gama = 360 + gama;

//                 new_point = new_point.applyVector(Vector(
//                     new_point,
//                     screen[z][y].rotateAroundY(gama).rotateAroundZ(alpha)
//                 ));
//             }

//             screen[z][y].setX(new_point.getX() + this->p.getX());
//             screen[z][y].setY(new_point.getY() + this->p.getY());
//             screen[z][y].setZ(new_point.getZ() + this->p.getZ());
//         }
//     }
//     return screen;
// }