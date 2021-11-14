#include "Camera.hpp"

Camera::Camera(double px, double py, double pz, double vx, double vy, double vz, double a)
    : p(px, py, pz), v(vx, vy, vz), angle(a)
{
    if (vx == 0 && vy == 0 && vz == 0)
        throw "The camera vector can not be the null vector";
    if (a < 60 || a > 120)
        throw "Bad angle for camera";
}

Camera::Camera(const Point &p, const Vector &v, double a)
    : p(p), v(v), angle(a)
{
    if (v.getX() == 0 && v.getY() == 0 && v.getZ() == 0)
        throw "The camera vector can not be the null vector";
    if (a < 60 || a > 120)
        throw "Bad angle for camera";
}

Camera::~Camera()
{
}

Point Camera::getP() const
{
    return this->p;
}
Vector Camera::getV() const
{
    return this->v;
}

void Camera::setX(double x)
{
    this->p.setX(x);
}
void Camera::setY(double y)
{
    this->p.setY(y);
}
void Camera::setZ(double z)
{
    this->p.setZ(z);
}
void Camera::setV(double x, double y, double z)
{
    this->v.setX(x);
    this->v.setY(y);
    this->v.setZ(z);
}

// find the distance debtween the camera and the screen : d
// find the center of the screen as we look in the X direction
// find all the points of the screen center on X axis
// apply the rotation for the alpha angle (angle between X axis and camera vector)
// apply the rotation for the gama angle (angle between Z axis and camera vector)
// apply the translation (from the point of the camera)
std::vector< std::vector<Point> > Camera::getScreen(const Config &config) const
{
    int height = config.getHeight() * config.getPrecision();
    int width = config.getWidth() * config.getPrecision();

    // make all the points
    std::vector< std::vector<Point> > screen;
    screen.resize(height, std::vector<Point>(width));

    for (int z = 0; z < height; ++z)
    {
        for (int y = 0; y < width; ++y)
        {
            screen[z][y] = Point(
                (double)width / (2 * sin(RADIAN(this->angle / 2))),
                ((double)width / 2) - y,    //  + (80 * sin(RADIAN(z * 3)))
                ((double)height / 2) - z    //  + (80 * sin(RADIAN(y * 3)))
            );
        }
    }

    // vectors
    Vector x_axis(1, 0, 0);
    Vector projection_on_plane_xy(this->v.getX(), this->v.getY(), 0);
    Vector projection_on_plane_xz(this->v.getX(), 0, this->v.getZ());

    //plane
    Plane xy_plane(0, 0, 0, 0, 0, 1);

    // angles
    double alpha = 0, gama = 0;

    if (projection_on_plane_xy.getMagnitude() != 0)
    {
        // angle between the camera vector and X axis
        alpha = projection_on_plane_xy.angleWith(x_axis);
        // if right turn angle = one complete turn minus himself (trigonometric circle)
        alpha = projection_on_plane_xy.directionXY(x_axis) == CLOCK_WISE ? (360 - alpha) : (alpha);
    }

    // angle between the camera vector and Z axis
    gama = xy_plane.angleWith(this->v);
    // if right turn angle = one complete turn minus himself (trigonometric circle)

    for (int z = 0; z < height; ++z)
    {
        for (int y = 0; y < width; ++y)
        {
            Point new_point(screen[z][y]); // res

            // translation horizontal
            if (projection_on_plane_xy.getMagnitude() != 0 && alpha != 0)
                new_point = screen[z][y].rotateAroundZ(alpha);

            // translation vertical
            if (projection_on_plane_xz.getMagnitude() != 0 && gama != 0)
            {
                if (gama < 0)
                    gama = 360 + gama;

                new_point = new_point.applyVector(Vector(
                    new_point,
                    screen[z][y].rotateAroundY(gama).rotateAroundZ(alpha)
                ));
            }

            screen[z][y].setX(new_point.getX() + this->p.getX());
            screen[z][y].setY(new_point.getY() + this->p.getY());
            screen[z][y].setZ(new_point.getZ() + this->p.getZ());
        }
    }
    return screen;
}