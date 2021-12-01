#include "Transform.hpp"

Transform::Transform()
    : alpha(45), beta(0), gama(0), translation(0, 0, 0), scaling(1, 1, 1), forward_matrix(4, 4), backward_matrix(4, 4)
{

}
Transform::~Transform() {}

void Transform::setAlpha(double alpha)
{
    this->alpha = alpha;
}
void Transform::setBeta(double beta)
{
    this->beta = beta;
}
void Transform::setGama(double gama)
{
    this->gama = gama;
}
void Transform::setTranslation(double x, double y, double z)
{
    this->translation.setX(x);
    this->translation.setY(y);
    this->translation.setZ(z);
}
void Transform::setScaling(double x, double y, double z)
{
    this->scaling.setX(x);
    this->scaling.setY(y);
    this->scaling.setZ(z);
}

void Transform::updateMatrices()
{
    Matrix m_trans(4, 4);
    m_trans.unit();
    m_trans[3][0] = translation.getX();
    m_trans[3][1] = translation.getY();
    m_trans[3][2] = translation.getZ();

    Matrix m_scale(4, 4);
    m_scale.unit();
    m_scale[0][0] = scaling.getX();
    m_scale[1][1] = scaling.getY();
    m_scale[2][2] = scaling.getZ();

    Matrix m_rotate_x(4, 4);
    m_rotate_x.unit();
    m_rotate_x[1][1] = cos(RADIAN(alpha));
    m_rotate_x[2][1] = -sin(RADIAN(alpha));
    m_rotate_x[1][2] = sin(RADIAN(alpha));
    m_rotate_x[2][2] = cos(RADIAN(alpha));

    Matrix m_rotate_y(4, 4);
    m_rotate_y.unit();
    m_rotate_y[0][0] = cos(RADIAN(beta));
    m_rotate_y[2][0] = sin(RADIAN(beta));
    m_rotate_y[0][2] = -sin(RADIAN(beta));
    m_rotate_y[2][2] = cos(RADIAN(beta));

    Matrix m_rotate_z(4, 4);
    m_rotate_z.unit();
    m_rotate_z[0][0] = cos(RADIAN(gama));
    m_rotate_z[1][0] = -sin(RADIAN(gama));
    m_rotate_z[0][1] = sin(RADIAN(gama));
    m_rotate_z[1][1] = cos(RADIAN(gama));

    forward_matrix = m_trans * m_scale * m_rotate_z * m_rotate_y * m_rotate_x;
    backward_matrix = forward_matrix;
    backward_matrix.inverse();
}

Matrix &Transform::getForwardMatrix()
{
    return this->forward_matrix;
}
Matrix Transform::getForwardMatrix() const
{
    return this->forward_matrix;
}
Matrix &Transform::getBackwardMatrix()
{
    return this->backward_matrix;
}
Matrix Transform::getBackwardMatrix() const
{
    return this->backward_matrix;
}

Vector Transform::apply(const Vector &v, int type) const
{
    return Vector(apply(*v.getP1(), type), apply(*v.getP2(), type));
}
Point Transform::apply(const Point &p, int type) const
{
    Matrix m_p1(1, 4);
    m_p1[0][0] = p.getX();
    m_p1[0][1] = p.getY();
    m_p1[0][2] = p.getZ();
    m_p1[0][3] = 1;

    Matrix m1(1, 4);
    if(type == FORWARD) {
        m1 = this->forward_matrix * m_p1;
    } else {
        m1 = this->backward_matrix * m_p1;
    }

    return Point(m1[0][0], m1[0][1], m1[0][2]);
}