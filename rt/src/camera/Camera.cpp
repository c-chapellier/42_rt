#include "Camera.hpp"

Camera::Camera(Vec3 coordinates, Vec3 direction, Vec3 up, double angle, int height, int width)
    : coordinates(coordinates), h_2(height / 2), w_2(width / 2)
{
    if (direction.is_null_vector()) throw "The camera vector can not be the null vector";
    if (up.is_null_vector()) throw "The camera vector can not be the null vector";
    if (angle < 60 || angle > 120) throw "Bad angle for camera";

    direction = direction.unit_vector();
    up = up.unit_vector();

    this->u = -cross(up, direction).unit_vector();
    this->v = cross(this->u, direction).unit_vector();

    this->screenCenter = this->coordinates + (direction * width / tan(DEGREE_TO_RADIAN(angle / 2)));
}

Ray Camera::getRay(int i, int j) const
{
    return Ray(
        this->coordinates,
        this->coordinates
            + this->screenCenter
            + v * (i - h_2)
            + u * (j - w_2)
    );
}
