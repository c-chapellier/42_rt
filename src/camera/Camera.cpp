#include "Camera.hpp"

Camera::Camera(Vec3 coordinates, Vec3 direction, Vec3 up, double angle, int height, int width)
    : coordinates(coordinates), direction(direction), up(up), angle(angle), height(height), width(width)
{
    if (this->direction.is_null_vector()) throw "The camera vector can not be the null vector";
    if (this->up.is_null_vector()) throw "The camera vector can not be the null vector";
    if (this->angle < 60 || this->angle > 120) throw "Bad angle for camera";

    this->direction = this->direction.unit_vector();
    this->up = this->up.unit_vector();

    this->u = cross(this->up, this->direction).unit_vector();
    this->v = -cross(this->u, this->direction).unit_vector();

    this->u = this->u * this->width;
    this->v = this->v * this->height;

    this->screenCenter = this->coordinates + (this->direction * width / tan(DEGREE_TO_RADIAN(angle / 2)));
}

void Camera::getRays(std::vector< std::vector<Ray> > &rays) const
{
    double h2 = height / 2;
    double w2 = width / 2;
    Vec3 v_height = this->v / height;
    Vec3 u_width = this->u / width;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            rays[i][j] = Ray(
                this->coordinates,
                this->screenCenter
                    + v_height * (i - h2)
                    + u_width * (j - w2)
            );
        }
    }
}
