
#include "Transform.hpp"

Transform::Transform(const Vec3 &translation, const Vec3 &rotation, const Vec3 &scale)
{
    Matrix tr(
        { 1, 0, 0, translation[0] },
        { 0, 1, 0, translation[1] },
        { 0, 0, 1, translation[2] },
        { 0, 0, 0, 1 }
    );

    Matrix sc(
        { scale[0], 0,          0,          0 },
        { 0,        scale[1],   0,          0 },
        { 0,        0,          scale[2],   0 },
        { 0,        0,          0,          1 }
    );

    Matrix rx(
        { 1, 0,                 0,                  0 },
        { 0, cos(rotation[0]),  -sin(rotation[0]),  0 },
        { 0, sin(rotation[0]),  cos(rotation[0]),   0 },
        { 0, 0,                 0,                  1 }
    );

    Matrix ry(
        { cos(rotation[1]),     0, sin(rotation[1]),    0 },
        { 0,                    1, 0,                   0 },
        { -sin(rotation[1]),    0, cos(rotation[1]),    0 },
        { 0,                    0, 0,                   1 }
    );

    Matrix rz(
        { cos(rotation[2]),     -sin(rotation[2]),  0,  0 },
        { sin(rotation[2]),     cos(rotation[2]),   0,  0 },
        { 0,                    0,                  1,  0 },
        { 0,                    0,                  0,  1 }
    );
        
    this->a = tr * sc * rx * ry * rz;
    this->a_inverse = this->a.inverse();
}

Vec3 Transform::apply_forward(const Vec3 &p) const
{
    return this->a * p;
}

Ray Transform::apply_forward(const Ray &ray) const
{
    Vec3 origin = this->apply_forward(ray.origin());

    return Ray(origin, this->apply_forward(ray.end()));
}

Vec3 Transform::apply_backward(const Vec3 &p) const
{
    return this->a_inverse * p;
}

Ray Transform::apply_backward(const Ray &ray) const
{
    Vec3 origin = this->apply_backward(ray.origin());

    return Ray(origin, this->apply_backward(ray.end()));
}